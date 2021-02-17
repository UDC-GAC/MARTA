#!/bin/python3
# -*- coding: utf-8 -*-
"""
.. module:: profiler
   :synopsis: This module enables measurements given a configuration file
.. moduleauthor:: Marcos Horro <marcos.horro@udc.es>
"""
import os
import copy
import sys
import yaml
import argparse
import pandas as pd
import numpy as np
import pickle
import itertools as it
from datetime import datetime as dt
from kernel import Kernel
# from kernel import __test_compile_process as comp_parallel
from tqdm import tqdm
from tqdm.auto import tqdm
import multiprocessing as mp
import custom_mp
from itertools import repeat as repit
from tqdm.contrib.concurrent import process_map  # or thread_map

__version__ = "0.0.0-alpha"


class Profiler:
    """
    Profiler class: helper class to set up experiments.
    """
    @staticmethod
    def dump_config_file():
        """
        Read config template line by line

        :return: List of strings with all lines
        :rtype: list(str)
        """
        config_file = "config_template"
        with open(config_file) as f:
            return f.readlines()

    @staticmethod
    def parse_arguments(list_args):
        """
        Parse CLI arguments

        :param list_args: List of arguments to parse
        :type list_args: list(str)
        :return: Arguments parsed
        :rtype: class:`argparse`
        """
        parser = argparse.ArgumentParser(
            prog="mprofiler",
            description="simple kernel profiler based on compilation files (Makefile) and a configuration file",
        )

        # If "version" or "dump" option, then positional is not needed
        required_input = 1
        if (
            ("-v" in list_args)
            or ("--version" in list_args)
            or ("-dump" in list_args)
            or ("--dump-config-file" in list_args)
        ):
            required_input = "?"

        # Positional argument
        required_named = parser.add_argument_group("required named arguments")
        required_named.add_argument(
            "input",
            metavar="input",
            type=str,
            nargs=required_input,
            help="input configuration file",
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

        optional_named.add_argument(
            "-dump",
            "--dump-config-file",
            action="store_true",
            help="dump a sample configuration file with all needed files for profiler to work properly",
            required=False,
        )

        optional_named.add_argument(
            "-G",
            "--generate-project",
            action="store_true",
            help="generate a blank project in current folder, with minimal files in order to work properly",
            required=False,
        )

        return parser.parse_args(list_args)

    @staticmethod
    def eval_features(feature):
        """
        Evaluate features from configuration file

        Example:

        "it.combinations(range(0,4),2)"

        This would generate a list of values such as: (0,1), (0,2), (0,3), (1,2), etc.

        :param feat: Dictionary of strings
        :type feat: dict
        :return: Retuns a dict with all features or parameters properly expanded
        :rtype: dict
        """
        params_dict = {}
        for f in feature.keys():
            type_feature = feature[f]["type"]
            evaluate = feature[f]["evaluate"]
            params_values = []
            if type(feature[f]["value"]) is str:
                try:
                    if evaluate:
                        params_values = eval(feature[f]["value"])
                    else:
                        params_values = feature[f]["value"]
                except NameError:
                    print(f"Evaluation of expression for {f} went wrong!")
                    sys.exit(1)
                if type_feature == "dynamic":
                    try:
                        size = len(params_values)
                    except TypeError:
                        tmp_eval_copy = copy.deepcopy(params_values)
                        for t in tmp_eval_copy:
                            size = len(t)
                            break
                    for i in range(size):
                        params_dict[f"{f}{str(i)}"] = [params_values]
            else:
                params_values = [feature[f]]
            if type_feature == "static":
                params_dict[f] = params_values
        return params_dict

    @staticmethod
    def comp_nvals(params_values):
        # Compute number of iterations
        if type(params_values) is list:
            return len(params_values)
        params_values_copy = copy.deepcopy(params_values)
        try:
            return len(list(*params_values_copy))
        except Exception:
            return len(list(it.product(*params_values_copy)))

    @staticmethod
    def print_version():
        """
        Print version and copyright message (if not quiet execution)
        """
        print(
            f"Micro ARchiTectural Analyzer (MARTA) - Profiler v{__version__}\n"
            f"(c) Colorado State University 2019-2021\n"
            f"(c) Universidade da Coruna 2020-2021\n",
            end="",
        )

    @staticmethod
    def dict_product(dicts):
        """
        Generate the product of different dictionaries in a serializable
        fashion, since `dict_keys` is not serializable.

        >>> list(dict_product(dict(number=[1,2], character='ab')))
        [{'character': 'a', 'number': 1},
        {'character': 'a', 'number': 2},
        {'character': 'b', 'number': 1},
        {'character': 'b', 'number': 2}]
        """
        return (pickle.dumps(dict(zip(dicts, x))) for x in it.product(*dicts.values()))

    def profiling_kernels(self, cfg):
        """
        Configuration file must have at least one kernel for performing profling

        :param args: Dictionary with all input arguments passed
        :type args: dict
        :param cfg: Dictionary with many
        :type cfg: dict
        """

        kernel = Kernel(cfg)
        config_output = cfg["kernel"]["output"]
        params_dict = Profiler.eval_features(kernel.feat)

        # Output configuration
        # file names
        output_cols = config_output["columns"]
        if self.args.output is None:
            tstamp = dt.now().strftime("%d_%m___%H_%M_%S")
            output_filename = "marta_profiler_"
            if config_output["name"] == "default":
                output_filename += f"{kernel.basename}_{tstamp}.csv"
            else:
                output_filename += f"{config_output['name']}_{tstamp}.csv"
        else:
            output_filename = self.args.output

        if output_cols == "all":
            output_cols = list(params_dict.keys())

        if type(output_cols) != list:
            print("output_cols parameter must be a list or 'all'")
            sys.exit(1)

        output_cols += ["CFG", "Compiler", "FLOPSs", "time"]
        output_cols += kernel.papi_counters

        niterations = np.prod([Profiler.comp_nvals(params_dict[k])
                               for k in params_dict])

        # Structure for storing results and ploting
        df = pd.DataFrame(columns=output_cols)

        # Silent compilation or not
        debug = ""
        if not kernel.comp_debug:
            debug = f" >> ___tmp.stdout 2>> ___tmp.stderr"

        if not self.args.quiet:
            # Print version if not quiet
            Profiler.print_version()

        # Execute command preceding compilation and execution process
        if cfg["kernel"]["preamble"]["command"] != "":
            try:
                os.system(f'{cfg["kernel"]["preamble"]["command"]}')
            except Exception:
                print("[ERROR] Preamble command went wrong...")
                sys.exit(1)

        print(f"Compiling with {kernel.processes} processes")
        for compiler in kernel.compilers_list:
            for kconfig in kernel.kernel_cfg:
                print(f"Compiler and flags: {compiler} {kconfig}")
                product = Profiler.dict_product(params_dict)

                # Compilation process can be done in parallel if compilers are
                # thread-safe, so user must be aware of this, not the
                # profiler (passive-agressive comment :-P)
                if kernel.compilation_enabled:
                    t0 = kernel.start_timer()
                    with mp.Pool(processes=kernel.processes) as pool:
                        iterable = zip(repit(kernel), repit(
                            kconfig), product, repit(compiler), repit(debug), repit(self.args.quit_on_error))
                        if kernel.show_progress_bars:
                            for output in tqdm(pool.istarmap(Kernel.compile,  iterable), total=niterations, desc="Compiling"):
                                if output == None:
                                    print("[ERROR] Compilation failed")
                                    pool.terminate()
                                    sys.exit(1)
                        else:
                            print("Compiling...")
                            output = pool.starmap(Kernel.compile,  iterable)
                            if output == None:
                                print("[ERROR] Compilation failed")
                                pool.terminate()
                                sys.exit(1)
                    kernel.accm_timer("compilation", t0)
                else:
                    print("[WARNING] Compilation process disabled!")

                # IMPORTANT NOTE:
                # This section could be parallel as well, if kernels
                # running are monolithic. Even though, you would have to
                # control properly CPU affinity and be aware if kernels are
                # cache sensitive or not. Thus, for simplicity, this is
                # still not parallel at all.
                product = Profiler.dict_product(params_dict)
                if kernel.execution_enabled:
                    if kernel.show_progress_bars:
                        loop_iterator = tqdm(
                            product, desc="Executing", total=niterations)
                    else:
                        loop_iterator = product
                        print("Executing...")
                    t0 = kernel.start_timer()
                    for params_val in loop_iterator:
                        kern_exec = kernel.run(kconfig, params_val, compiler)
                        # There was an error, exit on error, save data first
                        if kern_exec == None:
                            print("Saving file...")
                            kernel.save_results(df, output_filename)
                            sys.exit(1)
                        if type(kern_exec) == list:
                            for exec in kern_exec:
                                df = df.append(exec, ignore_index=True)
                        else:
                            df = df.append(kern_exec, ignore_index=True)
                    kernel.accm_timer("execution", t0)
                else:
                    print("[WARNING] Execution process disabled!")
        # Storing results and generating report file
        # TODO: add some spinner or something here
        kernel.save_results(df, output_filename)

        # Cleaning directories
        if cfg["kernel"]["finalize"]["clean_tmp_files"]:
            os.system(f"rm -Rf tmp/")
        if cfg["kernel"]["finalize"]["clean_bin_files"]:
            os.system(f"rm -Rf bin/")
        if cfg["kernel"]["finalize"]["clean_asm_files"]:
            os.system(f"rm -Rf asm/")
        if cfg["kernel"]["finalize"]["command"] != "":
            try:
                os.system(f'{cfg["kernel"]["finalize"]["command"]}')
            except Exception:
                print(
                    f"[ERROR] Finalize command went wrong for {kernel.basename}")

    def __init__(self, list_args):
        """
        Main function for profiler

        :param list_args: List of arguments, may be from the input `sys.argv`, or a
        "regular" string list
        :type list_args: list(str)
        """
        if (sys.version_info[0] < 3) or (sys.version_info[0] == 3 and sys.version_info[1] < 6):
            print("MARTA must run with Python >=3.6")
            sys.exit(1)
        self.args = Profiler.parse_arguments(list_args)

        if self.args.dump_config_file:
            s = Profiler.dump_config_file()
            for line in s:
                print(line, end="")
            sys.exit(0)

        if self.args.version:
            print(__version__)
            sys.exit(0)

        # parsing all the arguments from the configuration file
        try:
            from yaml import CLoader as Loader
        except ImportError:
            from yaml import Loader

        yml_config = self.args.input[0]
        try:
            with open(yml_config, "r") as ymlfile:
                kernel_setup = yaml.load(ymlfile, Loader=Loader)
        except FileNotFoundError:
            print("Configuration file not found")
            sys.exit(1)
        except Exception:
            print("Unknown error when opening configuration file.")
            print("Quitting...")
            sys.exit(1)

        # Create folders
        try:
            os.mkdir("asm_codes")
            os.mkdir("bin")
        except FileExistsError:
            pass

        # For each kernel configuration
        for cfg in kernel_setup:
            self.profiling_kernels(cfg)

        # Quit with no error
        sys.exit(0)


if __name__ == "__main__":
    Profiler(sys.argv[1:])
