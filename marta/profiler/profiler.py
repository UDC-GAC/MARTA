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
from kernel import Kernel
from utils import inv_dict
from tqdm import tqdm
from tqdm.auto import tqdm as tqdm_auto

# FIXME: change this at some point
__version__ = "0.0.0-alpha"

lang_equiv = {"c": ["gnu/c", "c", "cc"], "cpp": ["cpp", ""]}
lang_equiv_inverted = inv_dict(lang_equiv)


class Profiler:
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
            type_feature = feature[f]["type"]
            evaluate = feature[f]["evaluate"]
            if type(feature[f]["value"]) is str:
                try:
                    if evaluate:
                        tmp_eval = eval(feature[f]["value"])
                    else:
                        tmp_eval = feature[f]["value"]
                except NameError:
                    print(f"Evaluation of expression for {f} went wrong!")
                    sys.exit(1)
                if type_feature == "dynamic":
                    tmp_eval_copy = copy.deepcopy(tmp_eval)
                    for t in tmp_eval_copy:
                        size = len(t)
                        break
                    for i in range(size):
                        params_name += [f"{f}{str(i)}"]
                params_values += [tmp_eval]
            else:
                params_values += [feature[f]]
            if type_feature == "static":
                params_name += [f]
        return params_name, params_values

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
        params_name, params_values = Profiler.eval_features(kernel.feat)

        # Output configuration
        # file names
        output_cols = config_output["columns"]
        output_verbose = config_output["verbose"]
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
            output_cols = params_name.copy()
        if type(output_cols) is not list:
            print("output_cols parameter must be a list or 'all'")
            sys.exit(1)
        output_cols += ["FLOPSs", "Time", "CFG", "Compiler"]
        output_cols += kernel.papi_counters

        # Compute number of iterations
        params_values_copy = copy.deepcopy(params_values)
        try:
            niterations = len(list(*params_values_copy))
        except Exception:
            niterations = len(list(it.product(*params_values_copy)))

        niterations *= len(kernel.kernel_cfg) * len(kernel.compilers_list)

        # Structure for storing results and ploting
        df = pd.DataFrame(columns=output_cols)

        # Silent compilation or not
        silent = ""
        if kernel.comp_silent:
            silent = " > /dev/null 2> /dev/null"

        if not self.args.quiet:
            # Print version if not quiet
            Profiler.print_version()

        # Main loop with progress bar
        with tqdm(total=niterations) as pbar:
            for compiler in kernel.compilers_list:
                for kconfig in kernel.kernel_cfg:
                    backup_params_values = copy.deepcopy(params_values)
                    for params_values in it.product(backup_params_values):
                        print(params_values)
                        kern_exec = kernel.run(
                            kconfig, dict(zip(params_name, params_values)),
                            compiler, silent, self.args.quit_on_error)
                        # There was an error, exit on error, save data first
                        if kern_exec == None:
                            print("Saving file...")
                            kernel.save_results(df, output_filename)
                            sys.exit(1)
                        df = df.append(kern_exec, ignore_index=True)
                        pbar.update(1)
                    if cfg["kernel"]["clean_asm_files"]:
                        os.system("rm asm_codes/*")

        # Storing results and generating report file
        # TODO: add some spinner or something here
        kernel.save_results(df, output_filename)

        # Clean directory properly
        if cfg["kernel"]["clean_tmp_files"]:
            os.system(f"rm -Rf tmp bin")

    def __init__(self, list_args):
        """
        Main function for profiler

        :param list_args: List of arguments, may be from the input `sys.argv`, or a
        "regular" string list
        :type list_args: list(str)
        """
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
        os.system("mkdir -p asm_codes")
        os.system("mkdir -p bin")

        # For each kernel configuration
        for cfg in kernel_setup:
            self.profiling_kernels(cfg)

        # Quit with no error
        sys.exit(0)


if __name__ == "__main__":
    Profiler(sys.argv[1:])
