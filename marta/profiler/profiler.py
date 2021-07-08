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
import pkg_resources
import pickle
import itertools as it
import multiprocessing as mp

from .benchmark import Benchmark
from .kernel import Kernel
from .project import Project
from .utils import custom_mp
from .timing import Timing
from datetime import datetime as dt
from tqdm import tqdm
from tqdm.auto import tqdm
from itertools import repeat


class Profiler:
    """
    Profiler class: helper class to set up experiments.
    """

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
            prog="marta_profiler",
            description="simple kernel profiler based on compilation files and a configuration file",
        )

        # If "version" or "dump" option, then positional is not needed
        required_input = 1
        if (
            ("-v" in list_args)
            or ("--version" in list_args)
            or ("-dump" in list_args)
            or ("--dump-config-file" in list_args)
            or ("--generate-project" in list_args)
            or ("project" in list_args)
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
            "--no-quit-on-error",
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

        subparsers = parser.add_subparsers(dest="subparser", help="sub-command help")
        parser_project = subparsers.add_parser(
            "project",
            aliases=["P", "proj"],
            help="generate a blank project in current folder, with minimal files in order to work properly",
        )
        parser_project.add_argument(
            "-n",
            "--name",
            help="name of the new project",
            required=False,
            default="marta_bench",
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
        :return: Returns a dict with all features or parameters properly expanded
        :rtype: dict
        """
        params_dict = {}
        for f in feature.keys():
            type_feature = feature[f]["type"]
            evaluate = feature[f].get("evaluate", True)
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
            else:
                params_values = [feature[f]]
            # This is useful for iterators, such as permutations, combinations...
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
            elif type_feature == "static":
                try:
                    params_dict[f] = list(params_values)
                except TypeError:
                    params_dict[f] = params_values
            else:
                raise TypeError
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
        __version__ = pkg_resources.require("marta")[0].version

        print(
            f"Micro ARchitectural Toolkit Analysis (MARTA) - Profiler v{__version__}\n",
            end="",
        )

    @staticmethod
    def dict_product(dicts: dict, kernel_cfg: list):
        """
        Generate the product of different dictionaries in a serializable
        fashion, since `dict_keys` is not serializable.

        >>> list(dict_product(dict(number=[1,2], character='ab')))
        [{'character': 'a', 'number': 1},
        {'character': 'a', 'number': 2},
        {'character': 'b', 'number': 1},
        {'character': 'b', 'number': 2}]
        """
        dicts.update({"KERNEL_CFG": kernel_cfg})
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
        if len(kernel.d_features) > 0:
            params_kernel = Profiler.eval_features(kernel.d_features)
        else:
            params_kernel = kernel.d_flags

        # Output configuration: default values
        config_output = cfg["kernel"].get("output", {})
        output_format = config_output.get("format", "csv")
        output_cols = config_output.get("columns", "all")
        generate_report = config_output.get("report", False)
        if self.args.output is None:
            fname = config_output.get("name", kernel.kernel)
            tstamp = dt.now().strftime("%d_%m_%y___%H_%M_%S")
            output_filename = f"{fname}_marta_profiler_{tstamp}.{output_format}"
        else:
            output_filename = self.args.output

        if type(output_cols) == str and output_cols == "all":
            if type(params_kernel) is dict:
                output_cols = list(params_kernel.keys())
            else:
                output_cols = []

        if type(output_cols) != list:
            print("output_cols parameter must be a list or 'all'")
            sys.exit(1)

        output_cols += ["compiler"]
        if kernel.papi_counters != None:
            output_cols += kernel.papi_counters

        niterations = 1
        if type(params_kernel) is dict:
            niterations = np.prod(
                [Profiler.comp_nvals(params_kernel[k]) for k in params_kernel]
            )
        else:
            niterations = len(params_kernel)

        niterations *= len(kernel.kernel_cfg)

        # Structure for storing results and ploting
        df = pd.DataFrame(columns=output_cols)

        # Silent compilation or not
        debug = ""
        if not kernel.comp_debug:
            debug = f" >> log/___tmp.stdout 2>> log/___tmp.stderr"

        if not self.args.quiet:
            # Print version if not quiet
            Profiler.print_version()

        # Execute command preceding compilation and execution process
        preamble = cfg["kernel"].get("preamble")
        if preamble != None and preamble.get("command") != None:
            try:
                os.system(f'{preamble.get("command")}')
            except Exception:
                print("[ERROR] Preamble command went wrong...")
                sys.exit(1)

        # Create folders if needed
        if not os.path.exists("asm_codes"):
            os.mkdir("asm_codes")
        if not os.path.exists("bin"):
            os.mkdir("bin")
        if not os.path.exists("tmp"):
            os.mkdir("tmp")
        if not os.path.exists("log"):
            os.mkdir("log")
        else:
            if os.path.exists("log/___tmp.stdout"):
                os.remove("log/___tmp.stdout")
            if os.path.exists("log/___tmp.stderr"):
                os.remove("log/___tmp.stderr")

        exit_on_error = not self.args.no_quit_on_error

        if kernel.nsteps > 1:
            print(f"Determining loop overhead...")
            loop_benchmark = Benchmark("profiler/src/loop_overhead.c")
            overhead_loop = loop_benchmark.compile_run_benchmark(
                flags="-O3 -DMARTA_RDTSC"
            )

        print(f"Compiling with {kernel.processes} processes")
        for compiler in kernel.compiler_flags:
            for compiler_flags in list(kernel.compiler_flags[compiler]):
                print(f"Compiler and flags: {compiler} {compiler_flags}")
                if type(params_kernel) is dict:
                    product = Profiler.dict_product(params_kernel, kernel.kernel_cfg)
                else:
                    product = params_kernel

                # Compilation process can be done in parallel if compilers are
                # thread-safe, so user must be aware of this, not the
                # profiler (passive-agressive comment :-P)
                if kernel.compilation_enabled:
                    Timing.start_timer("compilation")
                    with mp.Pool(processes=kernel.processes) as pool:
                        iterable = zip(
                            repeat(kernel),
                            product,
                            repeat(compiler),
                            repeat(compiler_flags),
                            repeat(debug),
                            repeat(exit_on_error),
                        )
                        if kernel.show_progress_bars:
                            pbar = tqdm(
                                pool.istarmap(Kernel.compile, iterable),
                                total=niterations,
                                desc="Compiling",
                            )
                            for output in pbar:
                                if not output:
                                    pool.terminate()
                                    pbar.clear()
                                    pbar.close()
                                    print("[ERROR] Compilation failed")
                                    return None
                        else:
                            print("Compiling...")
                            output = pool.starmap(Kernel.compile, iterable)
                            if not output:
                                print("[ERROR] Compilation failed")
                                pool.terminate()
                                sys.exit(1)
                    Timing.accm_timer("compilation")
                else:
                    print("[WARNING] Compilation process disabled!")

                # IMPORTANT NOTE:
                # This section could be parallel as well, if kernels
                # running are monolithic. Even though, you would have to
                # control properly CPU affinity and be aware if kernels are
                # cache sensitive or not. Thus, for simplicity, this is
                # still not parallel at all.
                # Moreover: I think this should not EVER be parallel
                if type(params_kernel) is dict:
                    product = Profiler.dict_product(params_kernel, kernel.kernel_cfg)
                else:
                    product = params_kernel
                if kernel.execution_enabled:
                    if kernel.show_progress_bars:
                        loop_iterator = tqdm(
                            product, desc="Executing", total=niterations
                        )
                    else:
                        loop_iterator = product
                        print("Executing...")
                    Timing.start_timer("execution")
                    for params_val in loop_iterator:
                        kern_exec = kernel.run(params_val, compiler, compiler_flags)
                        # There was an error, exit on error, save data first
                        if kern_exec == None:
                            kernel.save_results(
                                df, output_filename, output_format, generate_report
                            )
                            print("[ERROR] Execution failed, partial results saved")
                            return None
                        if type(kern_exec) == list:
                            for exec in kern_exec:
                                df = df.append(exec, ignore_index=True)
                        else:
                            df = df.append(kern_exec, ignore_index=True)
                    Timing.accm_timer("execution")
                else:
                    print("[WARNING] Execution process disabled!")
        # Storing results and generating report file
        Timing.save_total_time()
        if kernel.nsteps > 1:
            df["overhead_loop"] = overhead_loop
        kernel.save_results(df, output_filename, output_format, generate_report)

        finalize_actions = cfg["kernel"].get("finalize")
        if finalize_actions != None:
            # Cleaning directories
            if finalize_actions.get("clean_tmp_files", False):
                os.system(f"rm -Rf tmp/")
                os.system(f"rm -Rf log/")
            if finalize_actions.get("clean_bin_files", False):
                os.system(f"rm -Rf bin/")
            if finalize_actions.get("clean_asm_files", False):
                os.system(f"rm -Rf asm_codes/")
            if finalize_actions.get("command") != None:
                try:
                    os.system(f'{finalize_actions.get("command")}')
                except Exception:
                    print(f"[ERROR] Finalize command went wrong for {kernel.basename}")
        return 0

    def __init__(self, list_args):
        """
        Main function for profiler

        :param list_args: List of arguments, may be from the input `sys.argv`, or a
        "regular" string list
        :type list_args: list(str)
        """
        if (sys.version_info[0] < 3) or (
            sys.version_info[0] == 3 and sys.version_info[1] < 7
        ):
            print("MARTA must run with Python >=3.7")
            sys.exit(1)
        self.args = Profiler.parse_arguments(list_args)

        if self.args.dump_config_file:
            s = Project.dump_config_file()
            for line in s:
                print(line, end="")
            sys.exit(0)

        if self.args.subparser == "project":
            name = self.args.name
            code = Project.generate_new_project(name)
            if code != 0:
                print("Something went wrong...")
                sys.exit(code)
            print(f"Project generated in folder '{name}'!")
            sys.exit(0)

        if self.args.version:
            self.print_version()
            sys.exit(0)

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

        # For each kernel configuration
        for cfg in kernel_setup:
            if self.profiling_kernels(cfg) == None:
                print("Kernel failed...")

        sys.exit(0)
