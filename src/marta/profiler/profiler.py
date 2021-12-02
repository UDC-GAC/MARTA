# Copyright (c) Colorado State University. 2019-2021
# Copyright (c) Universidade da Coruña. 2019-2021
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# Author: Marcos Horro <marcos.horro@udc.es>
#
# -*- coding: utf-8 -*-

# Standard libraries
import os
import copy
import subprocess
import sys
from marta.profiler.config import check_correctness_file, get_kernel_config
import argparse
from argparse import RawTextHelpFormatter
import pickle
import itertools as it
import multiprocessing as mp
from typing import Iterable, Union
import glob

# Third-party libraries
import pandas as pd
import numpy as np
from tqdm import tqdm
from tqdm.auto import tqdm
from itertools import repeat

# Local imports
from marta import get_data
from marta.utils.marta_utilities import (
    perror,
    pwarning,
    pinfo,
    create_directories,
    marta_exit,
    get_version,
    print_version,
)
from marta.profiler.benchmark import Benchmark, BenchmarkError
from marta.profiler.kernel import Kernel
from marta.profiler.project import Project
from marta.profiler.timing import Timing
from marta.profiler.logger import Logger


class Profiler:
    """
    Profiler class: helper class to set up experiments.
    """

    @staticmethod
    def generate_parser():
        """
        Parse CLI arguments

        :param list_args: List of arguments to parse
        :type list_args: list(str)
        :return: Arguments parsed
        :rtype: class:`argparse`
        """
        parser = argparse.ArgumentParser(
            prog="marta_profiler",
            description="Micro-architectural profiler based on very simple configurations files.",
            formatter_class=RawTextHelpFormatter,
        )

        parser.add_argument(
            "--version", action="version", version=get_version("Profiler")
        )

        subparsers = parser.add_subparsers(
            title="subcommands", dest="cmd", help="additional help"
        )
        parser_project = subparsers.add_parser(
            "project",
            help="project help",
            aliases=["po"],
            description="project subcommand is meant to help with the configuration and generation of new projects MARTA-compliant.",
        )
        parser_project.add_argument(
            "-n", "--name", nargs=1, type=str, help="name of the new project",
        )
        parser_project.add_argument(
            "-u",
            "--microbenchmark",
            action="store_true",
            help="set new project as micro-benchmark",
        )
        parser_project.add_argument(
            "-c",
            "--check-config-file",
            type=str,
            nargs=1,
            help="quit if there is an error checking the configuration file",
        )
        parser_project.add_argument(
            "-dump",
            "--dump-config-file",
            action="store_true",
            help="dump a sample configuration file with all needed files for profiler to work properly",
        )
        parser_general = subparsers.add_parser(
            "profile",
            help="profile help",
            aliases=["perf"],
            description="MARTA requires an input file with the configuration parameters, but some of them can be overwritten at runtime, as described below.",
        )
        required_named = parser_general.add_argument_group("required named arguments")
        required_named.add_argument(
            "input",
            metavar="input",
            type=str,
            nargs=1,
            help="input configuration file",
        )

        # Optional arguments
        optional_named = parser_general.add_argument_group("optional named arguments")

        optional_named.add_argument(
            "-o",
            "--output",
            help="output results file name",
            required=False,
            default=None,
        )

        optional_named.add_argument(
            "-r",
            "--report",
            action="store_true",
            help="output report file name, with data regarding the machine, compilation flags, warnings, and errors",
            required=False,
        )

        optional_named.add_argument(
            "-d", "--debug", action="store_true", help="debug verbose", required=False
        )

        optional_named.add_argument(
            "-nsteps",
            "--iterations",
            type=int,
            default=-1,
            action="store",
            help="number of iterations",
            required=False,
        )

        optional_named.add_argument(
            "-nexec",
            "--executions",
            type=int,
            default=-1,
            action="store",
            help="number of executions",
            required=False,
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
            "-s",
            "--summary",
            nargs="+",
            action="append",
            help="print a summary at the end with the given dimensions of interest",
            required=False,
        )

        return parser

    @staticmethod
    def eval_features(feature: dict, path: str) -> dict:
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
            is_path = feature[f].get("path", False)
            params_values = []
            if isinstance(feature[f]["value"], str):
                try:
                    to_eval = feature[f]["value"]
                    if is_path:
                        if isinstance(to_eval, list):
                            new_list = []
                            for val in to_eval:
                                new_list.append(
                                    val.replace("[PATH]", f"{os.getcwd()}/{path}")
                                )
                            to_eval = new_list
                        elif isinstance(to_eval, str):
                            to_eval = to_eval.replace("[PATH]", f"{os.getcwd()}/{path}")
                    if evaluate:
                        params_values = eval(to_eval)
                    else:
                        params_values = to_eval

                except NameError:
                    perror(f"Evaluation of expression for {f} went wrong!")
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
    def comp_nvals(params_values: Union[list, Iterable]) -> int:
        """Computer the number of iterations of some iterables. This is for the
        tqdm progress bar

        :param params_values: Any type of iterable
        :type params_values: Union[list, Iterable]
        :return: Number of elements
        :rtype: int
        """
        if isinstance(params_values, list):
            return len(params_values)
        params_values_copy = copy.deepcopy(params_values)
        try:
            return len(list(*params_values_copy))
        except Exception:
            return len(list(it.product(*params_values_copy)))

    @staticmethod
    def dict_product(dicts: dict, kernel_cfg: list) -> bytes:
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

    def get_loop_overhead(self, kernel: Kernel, exit_on_error: bool) -> float:
        """Auxiliar function for getting the overhead of measuring in a loop.

        :param kernel: Kernel for getting values
        :type kernel: Kernel
        :param exit_on_error: Boolean value to exit if error found
        :type exit_on_error: bool
        :return: Overhead produced by the loop itself
        :rtype: float
        """
        if not kernel.execution_enabled or kernel.nsteps == 1:
            return 0
        try:
            loop_benchmark = Benchmark(
                get_data("profiler/src/loop_overhead.c"), temp=True
            )
            overhead_loop_tsc = loop_benchmark.compile_run_benchmark(
                flags=[
                    "-Ofast",
                    "-DMARTA_RDTSC",
                    f"-DTSTEPS={kernel.nsteps}",
                    f"-DMARTA_CPU_AFFINITY={kernel.cpu_affinity}",
                    f"-I{get_data('profiler/utilities/')}",
                    get_data("profiler/utilities/polybench.c"),
                ],
                nsteps=kernel.nsteps,
            )
            pinfo(f"Loop overhead: {overhead_loop_tsc} cycles (TSC)")
        except BenchmarkError:
            msg = "Loop overhead could not be computed."
            if exit_on_error:
                perror(f"{msg} Quitting.")
            else:
                pwarning(f"{msg} Skipping.")
        return overhead_loop_tsc

    @staticmethod
    def clean_previous_files() -> None:
        list_opt = glob.glob("/tmp/*.opt")
        if list_opt != []:
            for elem in list_opt:
                os.system(f"rm {elem}")

    def get_loop_overhead_instructions(self, kernel: Kernel) -> int:
        if kernel.nsteps == 1:
            return 0
        elif kernel.loop_type.lower() == "c":
            return 3
        elif kernel.loop_type.lower() == "asm":
            return 2
        else:
            return -1

    def profiling_kernels(self, cfg: dict) -> int:
        """
        Configuration file must have at least one kernel for performing profling

        :param args: Dictionary with all input arguments passed
        :type args: dict
        :param cfg: Dictionary with many
        :type cfg: dict
        """

        kernel = Kernel(cfg)
        if self.args.executions > -1:
            kernel.nexec = self.args.executions
        if self.args.iterations > -1:
            kernel.nsteps = self.args.iterations
        if len(kernel.d_features) > 0:
            params_kernel = Profiler.eval_features(
                kernel.d_features, kernel.get_kernel_path()
            )
        else:
            params_kernel = kernel.d_flags

        # Output configuration: default values
        output_cols = kernel.get_output_columns()
        generate_report = kernel.emit_report() | self.args.report
        output_filename = (
            kernel.get_output_filename()
            if self.args.output == None
            else self.args.output
        )
        if isinstance(output_cols, str) and output_cols == "all":
            if isinstance(params_kernel, dict):
                output_cols = list(params_kernel.keys())
            else:
                output_cols = []

        if not isinstance(output_cols, list):
            perror("'output_cols' parameter must be a list or 'all'")

        output_cols += ["compiler"]
        if kernel.papi_counters != None:
            output_cols += kernel.papi_counters

        niterations = 1
        if isinstance(params_kernel, dict):
            niterations = np.prod(
                [Profiler.comp_nvals(params_kernel[k]) for k in params_kernel]
            )
        else:
            niterations = len(params_kernel)

        niterations *= len(kernel.kernel_cfg)

        # Structure for storing results and ploting
        df = pd.DataFrame(columns=output_cols)

        # Silent compilation or not
        make_stdout = subprocess.STDOUT
        make_stderr = subprocess.STDOUT

        # if not kernel.comp_debug and not self.args.debug:
        if not kernel.comp_debug and not (self.args.debug):
            make_stdout = "/tmp/___marta_stdout.log"
            make_stderr = "/tmp/___marta_stderr.log"

        create_directories(root=kernel.get_kernel_path("/marta_profiler_data/"))
        exit_on_error = not self.args.no_quit_on_error
        overhead_loop_tsc = self.get_loop_overhead(kernel, exit_on_error)
        Profiler.clean_previous_files()

        pinfo(
            f"Compilation using {kernel.processes} processes. Number of executions = {kernel.nexec}, number of iterations (TSTEPS) = {kernel.nsteps}"
        )
        if kernel.macveth:
            text = f"MACVETH enabled: this could take longer."
            if not kernel.check_dump:
                text += "Use 'check_dump' option also for correctness."
            else:
                text += " Dumping values for assessing correctness."
            pinfo(text)
        for compiler in kernel.compiler_flags:
            for compiler_flags in list(kernel.compiler_flags[compiler]):
                pinfo(f"Compiler and flags: {compiler} {compiler_flags}")
                if isinstance(params_kernel, dict):
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
                            repeat(make_stdout),
                            repeat(make_stderr),
                            repeat(exit_on_error),
                        )
                        if kernel.show_progress_bars:
                            pbar = tqdm(
                                pool.istarmap(Kernel.compile, iterable),
                                total=niterations,
                                desc="Compiling",
                                position=0,
                            )
                            for output in pbar:
                                if not output:
                                    pool.terminate()
                                    pbar.clear()
                                    pbar.close()
                                    perror("Compilation failed")
                                    return None
                        else:
                            pinfo("Compiling...")
                            output = pool.starmap(Kernel.compile, iterable)
                            if not output:
                                pool.terminate()
                                perror("Compilation failed")
                    Timing.accm_timer("compilation")
                else:
                    pwarning("Compilation process disabled!")

                # IMPORTANT NOTE:
                # This section could be parallel as well, if kernels
                # running are monolithic. Even though, you would have to
                # control properly CPU affinity and be aware if kernels are
                # cache sensitive or not. Thus, for simplicity, this is
                # still not parallel at all.
                # Moreover: I think this should not EVER be parallel
                if isinstance(params_kernel, dict):
                    product = Profiler.dict_product(params_kernel, kernel.kernel_cfg)
                else:
                    product = params_kernel
                if kernel.execution_enabled:
                    if kernel.show_progress_bars:
                        loop_iterator = tqdm(
                            product, desc="Benchmark", total=niterations, leave=True,
                        )
                    else:
                        loop_iterator = product
                        pinfo("Executing...")
                    Timing.start_timer("execution")
                    for params_val in loop_iterator:
                        kern_exec = kernel.run(params_val, compiler, compiler_flags)
                        # There was an error, exit on error, save data first
                        if kern_exec == None:
                            kernel.save_results(df, output_filename, generate_report)
                            perror("Execution failed, partial results saved")
                            return None
                        if isinstance(kern_exec, list):
                            for exec in kern_exec:
                                df = df.append(exec, ignore_index=True)
                        else:
                            df = df.append(kern_exec, ignore_index=True)
                    Timing.accm_timer("execution")
                else:
                    pwarning("Execution process disabled!")
        # Storing results and generating report file
        Timing.save_total_time()
        df["overhead_instructions"] = self.get_loop_overhead_instructions(kernel)
        df["overhead_loop"] = overhead_loop_tsc
        kernel.save_results(df, output_filename, generate_report)
        if self.args.summary != None:
            kernel.print_summary(df, self.args.summary[0])
        kernel.finalize_actions()
        Logger.write_to_file(kernel.get_kernel_path("/marta_profiler_data/marta.log"))
        return 0

    def process_project_args(self):
        """Process arguments starting with project
        """
        if self.args.dump_config_file:
            for line in Project.dump_config_file("profiler/template.yml"):
                print(line, end="")
            marta_exit(0)

        if self.args.name is not None:
            project_name = self.args.name[0]
            code = Project.generate_new_project(project_name)
            if code != 0:
                perror("Something went wrong...", code)
            pinfo(
                f"Project generated in folder '{project_name}'. Configuration template in current file as '{project_name}_template.yml'"
            )
            marta_exit(0)

        # Sanity-checks
        if self.args.check_config_file:
            kernel_setup = get_kernel_config(self.args.check_config_file[0])
            if not check_correctness_file(kernel_setup):
                perror("Configuration file is not correct")
            else:
                pinfo(
                    "Configuration file structure is correct (compilation files might be wrong)"
                )
                marta_exit(0)

        self.parser.print_help(sys.stderr)
        marta_exit(1)

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
            perror("MARTA must run with Python >=3.7")
        project_subcmd_alias = ["project", "po"]
        profile_subcmd_alias = ["profile", "perf"]
        self.parser = Profiler.generate_parser()
        self.args = self.parser.parse_args(list_args)
        if (not self.args.cmd in [*profile_subcmd_alias, *project_subcmd_alias]) or (
            len(sys.argv) == 1 or len(list_args) == 0
        ):
            self.parser.print_help(sys.stderr)
            marta_exit(1)

        if self.args.cmd in project_subcmd_alias:
            self.process_project_args()

        kernel_setup = get_kernel_config(self.args.input[0])
        if not self.args.quiet:
            # Print version if not quiet
            print_version("Profiler")

        # For each kernel configuration
        for cfg in kernel_setup:
            if self.profiling_kernels(cfg) == None:
                perror("Kernel failed...", exit_on_error=False)

        marta_exit(0)
