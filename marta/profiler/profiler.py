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
import timing
import asm_analyzer
import report
from tqdm import tqdm

__version__ = "0.0.1-alpha"

# some global variables, do not hate me


def save_results(df, common_flags, exec_args, nruns, nexec, filename, verbose):
    """
    Save data as a pandas.DataFrame

    :param filename: Full path output file
    :type filename: str
    :param verbose: Output includes machine information
    :type verbose: bool
    """
    # storing results with metadata
    df = df.fillna(0.0)
    df.to_csv(filename, index=False)

    # saving all data to file
    report_filename = filename.replace(".csv", ".log")
    with open(report_filename, "w") as f:
        f.write(
            report.generate_report(
                [common_flags, exec_args, ["runs and execs:", nruns, nexec]], verbose
            )
        )


def compile_parse_asm(
    kname, kpath, comp, common_flags, kconfig, custom_flags, suffix_file="", silent=""
):
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
        f"make -B -C {kpath} COMP={comp}"
        f" {kconfig} "
        f" COMMON_FLAGS='{common_flags}'"
        f" CUSTOM_FLAGS='{custom_flags}'"
        f" SUFFIX_ASM='{suffix_file}'"
        f" {silent}"
    )
    ret = os.system(comp_str)

    if ret != 0:
        print(f"Error {str(ret)} compiling in {kpath}, quiting...")
        return {}
    return asm_analyzer.parse_asm(f"asm_codes/{kname}{suffix_file}.s")


def eval_features(feature):
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
    for f in feature.keys():
        if type(feature[f]) is str:
            try:
                tmp_eval = eval(feature[f])
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
            params_values += [feature[f]]
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

    if avg_time > 0:
        return (flops_eval * nruns) / avg_time
    else:
        return 0


def run_kernel(
    kname,
    kconfig,
    p,
    flops,
    compiler,
    fixed_flags,
    common_flags,
    nruns,
    exec_args,
    nexec,
    config_cfg,
    silent,
    path_kernel,
):
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
        params = p[0]
        params = list(*params)
    except Exception:
        pass
    params_name = p[1]
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
        kconfig += " MVPATH=" + config_cfg["macveth_path_build"]
        kconfig += " MACVETH_FLAGS='" + config_cfg["macveth_flags"] + "'"

    asm_cols = compile_parse_asm(
        kname,
        path_kernel,
        compiler,
        local_common_flags,
        kconfig,
        custom_flags,
        suffix_file,
        silent,
    )

    if asm_cols != {}:
        # Average cycles
        avg_cycles = timing.time_benchmark(kname, "cyc", exec_args, nexec)
        # Average time
        avg_time = timing.time_benchmark(kname, "time", exec_args, nexec)
    else:
        if quit_on_error:
            return None
        avg_cycles = 0
        avg_time = 0

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
    required_named.add_argument(
        "input", metavar="input", type=str, nargs=1, help="input configuration file"
    )

    # Optional arguments
    optional_named = parser.add_argument_group("optional named arguments")

    optional_named.add_argument(
        "-o", "--output", help="output results file name", required=False
    )

    optional_named.add_argument(
        "-r",
        "--report",
        help="output report file name, with data regarding the machine, compilation flags, warnings, and errors",
        required=False,
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
    print(
        f"Micro ARchiTectural Analyzer (MARTA) - Profiler v{__version__}\n"
        f"(c) Colorado State University 2019-2020\n"
        f"(c) Universidade da Coruña 2020\n",
        end="",
    )


def profiling_kernel(cfg):
    """
    Configuration file must have at least one kernel for performing profling

    :param cfg: Dictionary with many
    :type cfg: dict
    """
    # General configuration
    kernel = cfg["kernel"]["name"]
    main_file = cfg["kernel"]["main_src"]
    target_file = cfg["kernel"]["target_src"]
    descr = cfg["kernel"]["description"]
    path_kernel = cfg["kernel"]["path"]
    debug = cfg["kernel"]["debug"]

    # compilation:
    config_comp = cfg["kernel"]["compilation"]
    # configuration:
    config_cfg = cfg["kernel"]["configuration"]
    # execution:
    config_exec = cfg["kernel"]["execution"]
    # output:
    config_output = cfg["kernel"]["output"]

    # Compilation configuration
    compilers_list = config_comp["compiler"]
    common_flags = config_comp["common_flags"]
    fixed_flags = config_comp["fixed_flags"]
    comp_silent = config_comp["silent"]

    # Configuration
    kernel_cfg = config_cfg["kernel_cfg"]
    feat = config_cfg["features"]

    # Execution arguments
    threshold_outliers = config_exec["threshold_outliers"]
    nexec = config_exec["nexec"]
    nruns = int(config_exec["nruns"])
    flops = config_exec["flops"]
    exec_args = config_exec["args"]
    basename = target_file.split(".c")[0]
    params_name, params_values = eval_features(feat)

    # Output configuration
    # file names
    output_cols = config_output["columns"]
    output_verbose = config_output["verbose"]
    if args.output is None:
        tstamp = dt.now().strftime("%d_%m___%H_%M_%S")
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

    # Main loop with progress bar
    with tqdm(total=niterations) as pbar:
        for compiler in compilers_list:
            for kconfig in kernel_cfg:
                backup_params_values = copy.deepcopy(params_values)
                for params in it.product(*backup_params_values):
                    pbar.update(1)
                    kern_exec = run_kernel(
                        basename,
                        kconfig,
                        [params, params_name],
                        flops,
                        compiler,
                        fixed_flags,
                        common_flags,
                        nruns,
                        exec_args,
                        nexec,
                        config_cfg,
                        silent,
                        path_kernel,
                    )
                    # There was an error, exit on error, save data first
                    if kern_exec == None:
                        print("Saving file...")
                        save_results(
                            df,
                            common_flags,
                            exec_args,
                            nruns,
                            nexec,
                            output_filename,
                            output_verbose,
                        )
                        sys.exit(1)
                    df = df.append(kern_exec, ignore_index=True)
                # Saving results
                save_results(
                    df,
                    common_flags,
                    exec_args,
                    nruns,
                    nexec,
                    output_filename,
                    output_verbose,
                )
                if cfg["kernel"]["clean_asm_files"]:
                    os.system("rm asm_codes/*")

    # Clean directory properly
    if cfg["kernel"]["clean_tmp_files"]:
        os.system(f"rm -Rf tmp bin")


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

    yml_config = args.input[0]
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
        profiling_kernel(cfg)

    # Quit with no error
    sys.exit(0)
