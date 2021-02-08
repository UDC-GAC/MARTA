from report import Report
import pandas as pd
from asm_analyzer import ASMParser as asm
from timing import Timing
import os
import sys


class Kernel:
    debug = False

    @staticmethod
    def dprint(msg):
        if Kernel.debug:
            print(msg)

    def save_results(self, df, filename):
        """
        Save data as a pandas.DataFrame

        :param df:
        :type df: class:pandas.DataFrame
        :param common_flags: List of flags used for compilation
        :type common_flags: str
        :param exec_args: List of arguments to pass when executing benchmark
        :type exec_args: str
        :param nruns: Number of times to execute the kernel
        :type nruns: int
        :param nexec: Number of time to execute whole experiment
        :type nexec: int
        :param filename: Name of the output file
        :type filename: str
        """
        # storing results with metadata
        df = df.fillna(0.0)
        df.to_csv(filename, index=False)

        # saving all data to file
        report_filename = filename.replace(".csv", ".log")
        with open(report_filename, "w") as f:
            f.write(
                Report.generate_report(
                    [self.common_flags, self.exec_args, [
                        "runs and execs:", self.nruns, self.nexec]]
                )
            )

    @staticmethod
    def compile_parse_asm(
        kname, kpath, comp, common_flags, kconfig, suffix_file="", silent=""
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
            f" KERNEL_CONFIG='{kconfig}' "
            f" COMMON_FLAGS='{common_flags}'"
            f" SUFFIX_ASM='{suffix_file}'"
            f" {silent}"
        )
        Kernel.dprint(comp_str)
        ret = os.system(comp_str)

        if ret != 0:
            print(f"Error {str(ret)} compiling in {kpath}, quitting...")
            return {}
        return asm.parse_asm(f"asm_codes/{kname}{suffix_file}.s")

    @staticmethod
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

    def run(self, kconfig, params, compiler, silent,  quit_on_error=False):
        """[summary]

        Args:
            kconfig ([type]): [description]
            params ([type]): [description]
            compiler ([type]): [description]
            silent ([type]): [description]
            quit_on_error (bool, optional): [description]. Defaults to False.

        Returns:
            [type]: [description]
        """
        n = 0
        tmp_dict = params.copy()
        custom_flags = ""
        suffix_file = ""
        for pname in params.keys():
            custom_flags += f" -D{pname}={params[pname]}"
            suffix_file += f"_{pname}{params[pname]}"
            flops_eval = self.flops.replace(pname, params[pname])
            n = n + 1
        custom_flags += self.compiler_flags[compiler]
        local_common_flags = self.common_flags + custom_flags
        local_common_flags += f" -DNRUNS={self.nruns} "

        if "MACVETH=true" in kconfig:
            suffix_file += "_macveth"
            kconfig += " MVPATH=" + self.config_cfg["macveth_path_build"]
            kconfig += " MACVETH_FLAGS='" + \
                self.config_cfg["macveth_flags"] + "'"

        asm_cols = Kernel.compile_parse_asm(
            self.basename,
            self.path_kernel,
            compiler,
            local_common_flags,
            kconfig,
            suffix_file,
            silent,
        )

        avg_papi_counters = dict.fromkeys(self.papi_counters)
        if asm_cols != {}:
            # Average papi counters
            avg_papi_counters = Timing.measure_benchmark(
                self.basename, self.papi_counters, self.exec_args, self.nexec)
            # Average time
            avg_time = Timing.measure_benchmark(
                self.basename, "time", self.exec_args, self.nexec)
        else:
            if quit_on_error:
                return None
            avg_cycles = 0
            avg_time = 0

        tmp_dict.update(
            {
                "FLOPSs": Kernel.compute_flops(flops_eval, self.nruns, avg_time),
                "Time": avg_time,
                "CFG": kconfig,
                "Compiler": compiler,
            }
        )
        tmp_dict.update(avg_papi_counters)
        tmp_dict.update(asm_cols)
        return tmp_dict

    def __init__(self, cfg):
        # General configuration
        self.kernel = cfg["kernel"]["name"]
        self.main_file = cfg["kernel"]["main_src"]
        self.target_file = cfg["kernel"]["target_src"]
        self.descr = cfg["kernel"]["description"]
        self.path_kernel = cfg["kernel"]["path"]
        self.debug = cfg["kernel"]["debug"]

        # compilation:
        self.config_comp = cfg["kernel"]["compilation"]
        # configuration:
        self.config_cfg = cfg["kernel"]["configuration"]
        # execution:
        self.config_exec = cfg["kernel"]["execution"]

        # Compilation configuration
        self.compilers_list = self.config_comp["compiler_flags"].keys()
        self.common_flags = self.config_comp["common_flags"]
        self.compiler_flags = self.config_comp["compiler_flags"]
        self.comp_silent = self.config_comp["silent"]

        # Configuration
        self.kernel_cfg = self.config_cfg["kernel_cfg"]
        self.feat = self.config_cfg["features"]

        # Execution arguments
        self.threshold_outliers = self.config_exec["threshold_outliers"]
        self.nexec = self.config_exec["nexec"]
        self.nruns = int(self.config_exec["nruns"])
        self.papi_counters = self.config_exec["papi_counters"]
        self.flops = self.config_exec["flops"]
        self.exec_args = self.config_exec["prefix"]
        self.basename = self.target_file.split(".c")[0]
