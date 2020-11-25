"""
.. module:: profiler
   :synopsis: This module enables measurements given a configuration file
.. moduleauthor:: Marcos Horro <marcos.horro@udc.es>
"""
# -*- coding: utf-8 -*-

import yaml
import argparse
import pandas as pd
import itertools as it
import os
import copy
from datetime import datetime as dt
import measurements
import asm_analyzer
from tqdm import tqdm


def csv_header(params, verbose):
    """
    Generate custom header for CSV file

    :param params: List of parameters to print in the file
    :type params: list
    :param verbose: If `True`, then outputs machine information
    :type verbose: bool
    :return: A string containing all data as a comment (all lines start with #)
    :rtype: str
    """
    if verbose:
        machine_file = "___tmp__machine_info.txt"
        os.system(f"uname -a > {machine_file}")
        os.system(f"lscpu >> {machine_file}")
        header = f"# BEGIN -- machine info\n"
        header = f"#\n"
        with open(machine_file, "r") as mf:
            for l in mf:
                header += f"# {l}"
        header += f"#\n"
        header += f"# END -- machine info\n"
        header += f"#\n"
        header += f"#\n"
        os.system(f"rm {machine_file}")
    header += f"# BEGIN -- parameters info\n"
    header += f"#\n"
    for p in params:
        if type(p) == dict:
            for k, v in p.items():
                header += f"# {str(k)}: {str(v)}\n"
        else:
            header += f"# {str(p)}\n"
    header += f"#\n"
    header += f"# END -- parameters info\n"
    header += f"#\n"
    return header


def save_df(df, output_filename, verbose):
    """
    Save data as a pandas.DataFrame

    :param df: Data to save
    :type df: class:`pandas.DataFrame`
    :param output_filename: Full path output file
    :type output_filename: str
    :param verbose: Output includes machine information
    :type verbose: bool
    """
    # storing results with metadata
    df = df.fillna(0.0)
    df.to_csv(output_filename, index=False)

    # saving all data to file
    with open(output_filename, "r+") as f:
        content = f.read()
        f.seek(0, 0)
        f.write(
            csv_header(
                [common_flags, exec_args, [
                    "runs and execs:", nruns, nexec]], verbose
            )
        )
        f.write(content)


def eval_features(feat):
    """
    Evaluate features from configuration file

    Example:

    "it.combinations(range(0,4),2)"

    This would generate a list of values such as: (0,1), (0,2), (0,3), (1,2), etc.

    :param feat: Dictionary of strings
    :type feat: dict
    :return: Retuns a tuple of lists with parameters names and their values
    :rtype: tuple
    """
    params_name = list()
    params_values = list()
    for f in feat.keys():
        if type(feat[f]) is str:
            try:
                tmp_eval = eval(feat[f])
            except NameError:
                print(f"Evaluation of expression for {f} went wrong!")
                exit(1)
            tmp_eval_copy = copy.deepcopy(tmp_eval)
            for t in tmp_eval_copy:
                size = len(t)
                break
            for i in range(size):
                params_name += [f"{f}{str(i)}"]
            params_values += [tmp_eval]
        else:
            params_name += [f]
            params_values += [feat[f]]
    return params_name, params_values


def parse_arguments():
    """
    Parse CLI arguments

    :return: Arguments parsed
    :rtype: class:`argparse`
    """
    parser = argparse.ArgumentParser(
        description="wrapper for preparing data given a csv"
    )
    required_named = parser.add_argument_group("required named arguments")
    required_named.add_argument(
        "-i", "--input", help="input file name", required=True)
    required_named.add_argument(
        "-d", "--debug", action="store_true", help="debug verbose", required=False
    )
    return parser.parse_args()


if __name__ == "__main__":
    #############################
    # Parsing CLI inputs
    #############################
    args = parse_arguments()

    #############################
    # Parsing all the arguments from the config.yml
    #############################
    try:
        from yaml import CLoader as Loader
    except ImportError:
        from yaml import Loader

    yml_config = args.input
    debug = args.debug
    with open(yml_config, "r") as ymlfile:
        kernel_setup = yaml.load(ymlfile, Loader=Loader)

    #############################
    # Create folders
    #############################
    os.system("mkdir -p asm_codes")
    os.system("mkdir -p bin")

    tmp_files = "-Rf tmp"

    #############################
    # For each kernel configuration
    #############################
    for cfg in kernel_setup:
        # General configuration
        kernel = cfg["kernel"]["name"]
        main_file = cfg["kernel"]["main_src"]
        target_file = cfg["kernel"]["target_src"]
        descr = cfg["kernel"]["descr"]
        path_kernel = cfg["kernel"]["path"]
        debug = cfg["kernel"]["debug"]

        config_comp = cfg["kernel"]["compilation"]
        config_exec = cfg["kernel"]["execution"]
        config_output = cfg["kernel"]["output"]

        # Compilation configuration
        compiler = config_comp["compiler"]
        kernel_cfg = config_comp["kernel_cfg"]
        feat = config_comp["features"]
        nexec = config_comp["nexec"]
        nruns = int(config_comp["nruns"])
        flops = config_comp["flops"]
        common_flags = config_comp["common_flags"]
        fixed_flags = config_comp["fixed_flags"]
        comp_silent = config_comp["silent"]

        # Execution arguments
        exec_args = config_exec["args"]
        basename = target_file.split(".c")[0]

        params_name, params_values = eval_features(feat)

        # Output configuration
        # file names
        tstamp = dt.now().strftime("%H_%M_%S__%m_%d")
        d = config_output["dir"] + "/"
        try:
            os.mkdir(f"{d}")
        except FileExistsError:
            pass
        output_filename = d
        if config_output["name"] == "":
            output_filename += f"profiler_{basename}_{tstamp}.csv"
        else:
            output_filename += f"profiler_{config_output['name']}_{tstamp}.csv"
        output_cols = config_output["columns"]
        output_verbose = config_output["verbose"]

        if output_cols == "all":
            output_cols = params_name.copy()
        if type(output_cols) is not list:
            print("output_cols parameter must be a list or 'all'")
            exit(1)
        output_cols += ["FLOPSs", "Cycles", "Time", "CFG"]

        # Compute number of iterations
        params_values_copy = copy.deepcopy(params_values)
        try:
            niterations = len(list(*params_values_copy))
        except Exception:
            niterations = len(
                list(it.product(*params_values_copy)))

        niterations *= len(kernel_cfg)

        # Structure for storing results and ploting
        df = pd.DataFrame(columns=output_cols)

        print("Microbenchmarking for " + kernel + " code...")
        with tqdm(total=niterations) as pbar:
            for kconfig in kernel_cfg:
                backup_params_values = copy.deepcopy(params_values)
                for params in it.product(*backup_params_values):
                    pbar.update(1)
                    try:
                        params = list(*params)
                    except Exception:
                        pass
                    n = 0
                    tmp_dict = {}
                    custom_flags = ""
                    suffix_file = ""
                    for p in params:
                        tmp_dict[params_name[n]] = p
                        custom_flags += f" -D{params_name[n]}={p}"
                        suffix_file += f"_{params_name[n]}{p}"
                        flops = flops.replace(params_name[n], str(p))
                        n = n + 1
                    custom_flags += fixed_flags
                    common_flags += custom_flags
                    silent = ""
                    if comp_silent:
                        silent = " > /dev/null 2> /dev/null"

                    if "MACVETH=true" in kconfig:
                        suffix_file += "_macveth"

                    # compilation
                    ret = os.system(
                        f"make -C {path_kernel} COMP={compiler}"
                        f" {kconfig} "
                        f" COMMON_FLAGS='{common_flags}'"
                        f" CUSTOM_FLAGS='{custom_flags}'"
                        f" SUFFIX_ASM='{suffix_file}'"
                        f" NRUNS={nruns} "
                        f" {silent}"
                    )
                    if (ret != 0):
                        print(
                            f"Error {str(ret)} compiling in {path_kernel}, quiting:")
                        print("Saving file...")
                        save_df(df, output_filename, output_verbose)
                        exit(1)
                    tmp_dict.update(
                        asm_analyzer.parse_asm(
                            f"asm_codes/{basename}{suffix_file}.s")
                    )

                    # Average cycles
                    avg_cycles = measurements.time_benchmark(
                        basename, "cyc", nexec, exec_args)
                    # Average time
                    avg_time = measurements.time_benchmark(
                        basename, "time", nexec, exec_args)
                    # FLOPS formula
                    try:
                        flops_eval = eval(flops)
                    except NameError:
                        print("FLOPS formula is not valid; please review it!")
                        exit(1)
                    flopss = (flops_eval * nruns) / avg_time
                    tmp_dict.update(
                        {
                            "FLOPSs": flopss,
                            "Cycles": avg_cycles,
                            "Time": avg_time,
                            "CFG": kconfig
                        }
                    )
                    # Apending results
                    df = df.append(tmp_dict, ignore_index=True)

                # Saving results
                save_df(df, output_filename, output_verbose)

    # Clean directory properly
    if tmp_files != "":
        os.system(f"rm {tmp_files}")
