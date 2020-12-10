#!/bin/python3
# -*- coding: utf-8 -*-
"""
.. module:: profiler
   :synopsis: This module enables measurements given a configuration file
.. moduleauthor:: Marcos Horro <marcos.horro@udc.es>
"""

import sys
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

VERSION_MAJOR = 0
VERSION_MINOR = 0
VERSION_PATCH = 1

errors = 0


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
    header = ""
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


def save_dataframe(df, filename, verbose):
    """
    Save data as a pandas.DataFrame

    :param df: Data to save
    :type df: class:`pandas.DataFrame`
    :param filename: Full path output file
    :type filename: str
    :param verbose: Output includes machine information
    :type verbose: bool
    """
    # storing results with metadata
    df = df.fillna(0.0)
    df.to_csv(filename, index=False)

    # saving all data to file
    with open(filename, "r+") as f:
        content = f.read()
        f.seek(0, 0)
        f.write(
            csv_header(
                [common_flags, exec_args, ["runs and execs:", nruns, nexec]], verbose
            )
        )
        f.write(content)


def compile_parse_asm(common_flags, custom_flags, suffix_file="", silent=""):
    """
    Compile benchmark according to a set of flags, suffixes and so

    :param common_flags: Flags which are common for all versions
    :type common_flags: str
    :param custom_flags: Flags which are target-dependent
    :type custom_flags: str
    :param suffix_file: Suffix
    :type suffix_file: str
    :param silent: Suffix for execution command in order to redirect output if any
    :type silent: str
    :return: Dictionary of ASM occurrences
    :rtype: dict
    """
    comp_str = (
        f"make -B -C {path_kernel} COMP={compiler}"
        f" {kconfig} "
        f" COMMON_FLAGS='{common_flags}'"
        f" CUSTOM_FLAGS='{custom_flags}'"
        f" SUFFIX_ASM='{suffix_file}'"
        f" {silent}"
    )
    ret = os.system(comp_str)

    if ret != 0:
        attempts = 3
        for i in range(attempts):
            if os.system(comp_str) == 0:
                break
        if i == (attempts - 1):
            print(f"Error {str(ret)} compiling in {path_kernel}, quiting...")
            if quit_on_error:
                print("Saving file...")
                save_dataframe(df, output_filename, output_verbose)
                sys.exit(1)
            else:
                print("Continue execution...")
                return {}
    return asm_analyzer.parse_asm(f"asm_codes/{basename}{suffix_file}.s")


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
                sys.exit(1)
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


def compute_flops(flops, nruns, avg_time):
    """
    Evaluate FLOPS expression provided by user as string and return a floating
    point value

    :param flops: Expression provided by user, e.g. "X/42", where "X" is a parameter
    :type flops: str
    :param nruns: Number of times to execute the kernel
    :type nruns: int
    :param avg_time: Average time to execute the kernel
    :type avg_time: float
    :return: Dynamic number of FLOPS
    :rtype: float
    """
    try:
        flops_eval = eval(flops)
    except NameError:
        print("FLOPS formula is not valid; please review it!")
        sys.exit(1)
    return (flops_eval * nruns) / avg_time


def run_kernel(kconfig, params):
    """
    Main block of the execution chain, where compilation and execution take place

    :param kconfig: Kernel configuration
    :type kconfig: str
    :param params: Parameters to use in the compilation and execution processes
    :type params: list
    :return: New row in form of dictionary
    :rtype: dict
    """
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
        flops_eval = flops.replace(params_name[n], str(p))
        n = n + 1
    custom_flags += fixed_flags
    local_common_flags = common_flags + custom_flags
    local_common_flags += f" -DNRUNS={nruns} "

    if "MACVETH=true" in kconfig:
        suffix_file += "_macveth"

    asm_cols = compile_parse_asm(local_common_flags, custom_flags, suffix_file, silent)

    if asm_cols != {}:
        # Average cycles
        avg_cycles = measurements.time_benchmark(basename, "cyc", nexec, exec_args)
        # Average time
        avg_time = measurements.time_benchmark(basename, "time", nexec, exec_args)
    else:
        errors += 1
        avg_cycles = -1
        avg_time = -1

    tmp_dict.update(
        {
            "FLOPSs": compute_flops(flops_eval, nruns, avg_time),
            "Cycles": avg_cycles,
            "Time": avg_time,
            "CFG": kconfig,
        }
    )
    tmp_dict.update(asm_cols)
    return tmp_dict


def check_errors():
    if errors > 0:
        print(f"There were {str(errors)} errors during execution...")
        sys.exit(1)


def parse_arguments():
    """
    Parse CLI arguments

    :return: Arguments parsed
    :rtype: class:`argparse`
    """
    parser = argparse.ArgumentParser(
        description="wrapper for preparing data given a csv"
    )

    # Mandatory arguments
    required_named = parser.add_argument_group("required named arguments")
    required_named.add_argument("-i", "--input", help="input file name", required=True)

    # Optional arguments
    optional_named = parser.add_argument_group("optional named arguments")

    optional_named.add_argument(
        "-o", "--output", help="output file name", required=False
    )

    optional_named.add_argument(
        "-d", "--debug", action="store_true", help="debug verbose", required=False
    )
    optional_named.add_argument(
        "-x",
        "--quit-on-error",
        action="store_true",
        help="quit if there is an error during compilation or execution of the kernel",
        required=False,
    )
    optional_named.add_argument(
        "-q", "--quiet", action="store_true", help="quiet execution", required=False
    )
    optional_named.add_argument(
        "-v",
        "--version",
        action="store_true",
        help="display version and quit",
        required=False,
    )
    return parser.parse_args()


def print_version():
    """
    Print version and copyright message (if not quiet execution)
    """
    version = f"{VERSION_MAJOR}.{VERSION_MINOR}.{VERSION_PATCH}"
    print(
        f"Micro ARchiTectural Analyzer (MARTA) - Profiler v{version}\n"
        f"(c) Colorado State University 2019-2020\n"
        f"(c) Universidade da Coruña 2020\n",
        end="",
    )


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
    quit_on_error = args.quit_on_error
    quiet_exec = args.quiet
    try:
        with open(yml_config, "r") as ymlfile:
            kernel_setup = yaml.load(ymlfile, Loader=Loader)
    except FileNotFoundError:
        print("Configuration file not found")
        sys.exit(1)
    except Exception:
        print("Unknown error... quitting")
        sys.exit(1)

    #############################
    # Create folders
    #############################
    os.system("mkdir -p asm_codes")
    os.system("mkdir -p bin")

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
        output_cols = config_output["columns"]
        output_verbose = config_output["verbose"]
        if args.output is None:
            tstamp = dt.now().strftime("%H_%M_%S__%m_%d")
            output_filename = "marta_profiler_"
            if config_output["name"] == "":
                output_filename += f"{basename}_{tstamp}.csv"
            else:
                output_filename += f"{config_output['name']}_{tstamp}.csv"
        else:
            output_filename = args.output
        if output_cols == "all":
            output_cols = params_name.copy()
        if type(output_cols) is not list:
            print("output_cols parameter must be a list or 'all'")
            sys.exit(1)
        output_cols += ["FLOPSs", "Cycles", "Time", "CFG"]

        # Compute number of iterations
        params_values_copy = copy.deepcopy(params_values)
        try:
            niterations = len(list(*params_values_copy))
        except Exception:
            niterations = len(list(it.product(*params_values_copy)))

        niterations *= len(kernel_cfg)

        # Structure for storing results and ploting
        df = pd.DataFrame(columns=output_cols)

        # Silent compilation or not
        silent = ""
        if comp_silent:
            silent = " > /dev/null 2> /dev/null"

        # Print version if not quiet
        print_version()

        # Main loop
        with tqdm(total=niterations) as pbar:
            for kconfig in kernel_cfg:
                backup_params_values = copy.deepcopy(params_values)
                for params in it.product(*backup_params_values):
                    pbar.update(1)
                    df = df.append(run_kernel(kconfig, params), ignore_index=True)
                # Saving results
                save_dataframe(df, output_filename, output_verbose)
                if cfg["kernel"]["clean_asm_files"]:
                    os.system("rm asm_codes/*")

        # Clean directory properly
        if cfg["kernel"]["clean_tmp_files"]:
            os.system(f"rm -Rf tmp bin")

        # TODO: Check if any errors in compilation, execution or anything...
        check_errors()

        # Quit with no error
        sys.exit(0)
