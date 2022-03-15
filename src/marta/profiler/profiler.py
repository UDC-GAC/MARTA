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
import argparse
import itertools as it
import logging
import multiprocessing as mp
import sys

# Third-party libraries
import pandas as pd
from tqdm import tqdm
from tqdm.auto import tqdm

# Local imports
from marta import get_data
from marta.profiler.benchmark import Benchmark, BenchmarkError
from marta.profiler.config import check_correctness_file, get_kernel_config
from marta.profiler.d_features import dict_product
from marta.profiler.kernel import Kernel
from marta.profiler.logger import Logger
from marta.profiler.macveth import _pinfo_macveth
from marta.profiler.project import Project
from marta.profiler.timing import Timing
from marta.utils.marta_utilities import (
    clean_previous_files,
    create_directories,
    dump_config_file,
    get_version,
    marta_exit,
    perror,
    pinfo,
    print_version,
    pwarning,
)


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
            description="Productivity-aware framework for micro-architectural profiling and performance characterization",
            formatter_class=argparse.RawTextHelpFormatter,
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
            "-d", "--debug", action="store_true", help="debug verbose", required=False,
        )

        optional_named.add_argument(
            "-log",
            "--loglevel",
            type=str,
            default="warning",
            choices=["debug", "info", "warning", "error", "critical"],
            help="log level",
            required=False,
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
            "-q",
            "--quiet",
            action="store_true",
            help="quiet execution",
            required=False,
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
            pinfo(f"Loop overhead: {overhead_loop_tsc} cycles (RDTSC)")
        except BenchmarkError:
            msg = "Loop overhead could not be computed."
            if exit_on_error:
                perror(f"{msg} Quitting.")
            else:
                pwarning(f"{msg} Skipping.")
        return overhead_loop_tsc

    def get_loop_overhead_instructions(self, kernel: Kernel) -> int:
        if kernel.nsteps == 1:
            return 0
        elif kernel.loop_type.lower() == "c" or kernel.loop_type.lower() == "asm":
            return 1
        else:
            return -1

    def process_kernel_parameters(self, cfg: dict) -> Kernel:
        """Process all kernel parameters, both from the configuration file and
           CLI. CLI parameters have priority

        :param cfg: parameters provided in the configuration file
        :type cfg: dict
        :return: the whole kernel configuration
        :rtype: Kernel
        """
        kernel = Kernel(cfg)
        if self.args.executions > -1:
            kernel.nexec = self.args.executions
        if self.args.iterations > -1:
            kernel.nsteps = self.args.iterations
        kernel.generate_report = kernel.emit_report() | self.args.report
        kernel.debug |= self.args.debug
        return kernel

    def profiling_kernels(self, cfg: dict) -> int:
        """
        Configuration file must have at least one kernel for performing profling

        :param args: Dictionary with all input arguments passed
        :type args: dict
        :param cfg: Dictionary with many
        :type cfg: dict
        """
        kernel = self.process_kernel_parameters(cfg)

        # Output configuration: default values
        output_cols = kernel.get_output_columns()
        output_filename = (
            kernel.get_output_filename()
            if self.args.output is None
            else self.args.output
        )
        if isinstance(output_cols, str) and output_cols == "all":
            output_cols = list(kernel.params.keys())

        if not isinstance(output_cols, list):
            perror("'output_cols' parameter must be a list or 'all'")

        output_cols += ["compiler"]
        if kernel.papi_counters != None:
            output_cols += kernel.papi_counters

        product = dict_product(kernel.params, kernel.kernel_cfg)
        # niterations = len([i for i in product]) * len(kernel.kernel_cfg)
        niterations = len([i for i in product])
        create_directories(root=kernel.get_kernel_path("/marta_profiler_data/"))
        exit_on_error = not self.args.no_quit_on_error
        overhead_loop_tsc = self.get_loop_overhead(kernel, exit_on_error)
        clean_previous_files()

        pinfo(
            f"Compilation using {kernel.processes} processes. Number of executions = {kernel.nexec}, number of iterations (TSTEPS) = {kernel.nsteps}"
        )
        _pinfo_macveth(kernel)
        # Structure for storing results and ploting
        df = pd.DataFrame(columns=output_cols)
        for compiler in kernel.compiler_flags:
            for compiler_flags in list(kernel.compiler_flags[compiler]):
                pinfo(f"Compiler and flags: {compiler} {compiler_flags}")
                product = dict_product(kernel.params, kernel.kernel_cfg)
                if kernel.compilation_enabled:
                    Timing.start_timer("compilation")
                    with mp.Pool(processes=kernel.processes) as pool:
                        iterable = zip(
                            it.repeat(kernel),
                            product,
                            it.repeat(compiler),
                            it.repeat(compiler_flags),
                            it.repeat(exit_on_error),
                        )
                        if kernel.show_progress_bars:
                            pbar = tqdm(
                                pool.istarmap(Kernel.compile, iterable),
                                total=niterations,
                                desc="Compiling ",
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

                product = dict_product(kernel.params, kernel.kernel_cfg)
                if kernel.execution_enabled:
                    if kernel.show_progress_bars:
                        loop_iterator = tqdm(
                            product, desc="Benchmark ", total=niterations, leave=True,
                        )
                    else:
                        loop_iterator = product
                        pinfo("Executing...")
                    Timing.start_timer("execution")
                    for params_val in loop_iterator:
                        kern_exec = kernel.run(params_val, compiler, compiler_flags)
                        # There was an error, exit on error, save data first
                        if kern_exec is None:
                            kernel.save_results(df, output_filename)
                            perror("Execution failed, partial results saved")
                            return None
                        if not isinstance(kern_exec, list): kern_exec = [kern_exec]
                        df = pd.concat( [df, pd.DataFrame.from_records( kern_exec )], ignore_index = True )
                    Timing.accm_timer("execution")
                else:
                    pwarning("Execution process disabled!")
        # Storing results and generating report file
        Timing.save_total_time()
        df["oh_loop_ins"] = self.get_loop_overhead_instructions(kernel)
        df["oh_loop_tsc"] = overhead_loop_tsc
        df = kernel.save_results(df, output_filename)
        if self.args.summary != None:
            kernel.print_summary(df, self.args.summary[0])
        Logger.write_to_file(kernel.get_kernel_path("/marta_profiler_data/marta.log"))
        pinfo(f"Results saved to '{output_filename}'")
        kernel.finalize_actions()
        return 0

    def process_project_args(self):
        """Process arguments starting with project
        """
        if self.args.dump_config_file:
            for line in dump_config_file("profiler/template.yml"):
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

    def config_logger(self):
        loglevel = getattr(logging, self.args.loglevel.upper(), None)
        if not isinstance(loglevel, int):
            loglevel = logging.DEBUG
        logging.basicConfig(
            filename="/tmp/__marta_logger.log",
            level=loglevel,
            format="%(asctime)s:[%(levelname)s]:%(name)s:%(message)s",
            datefmt="%d-%m-%Y %I:%M:%S %p",
            filemode="w",
        )
        import marta.utils.marta_utilities as mu

        mu._quiet_msg = False
        if hasattr(self.args, "quiet"):
            mu._quiet_msg = self.args.quiet

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

        self.config_logger()
        # For each kernel configuration
        for cfg in kernel_setup:
            if self.profiling_kernels(cfg) is None:
                perror("Kernel failed...", exit_on_error=False)

        marta_exit(0)
