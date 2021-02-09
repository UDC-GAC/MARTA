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
            print(f"[MARTA DEBUG]: {msg}")

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
        suffix_file = suffix_file.split("/")[-1].replace(".c", "")
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
        return asm.parse_asm(f"asm_codes/{kname}{suffix_file}_{comp}.s")

    def define_papi_counters(self):
        papi_counter_file = "kernels/utilities/papi_counters.list"
        with open(papi_counter_file, "w") as f:
            for ctr in self.papi_counters:
                f.write("\"" + str(ctr) + "\",\n")

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
        except TypeError:
            flops_eval = flops
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
        flops_eval = "1"
        for pname in params.keys():
            try:
                param_val_parsed = int(params[pname])
            except ValueError:
                param_val_parsed = "\\\"" + params[pname] + "\\\""
            custom_flags += f" -D{pname}={param_val_parsed}"
            suffix_file += f"_{pname}{params[pname]}"
            flops_eval = self.flops.replace(pname, str(params[pname]))
            n = n + 1
        custom_flags += self.compiler_flags[compiler]
        local_common_flags = self.common_flags + custom_flags
        local_common_flags += f" -DNRUNS={self.nruns} "

        if "MACVETH=true" in kconfig:
            suffix_file += "_macveth"
            kconfig += " MVPATH=" + self.config_cfg["macveth_path_build"]
            kconfig += " MACVETH_FLAGS='" + \
                self.config_cfg["macveth_flags"] + "'"

        self.define_papi_counters()
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
        avg_time = {}
        tmp_dict.update(asm_cols)
        if asm_cols != {}:
            # Average papi counters
            if len(self.papi_counters) > 0:
                avg_papi_counters = Timing.measure_benchmark(
                    self.basename, self.papi_counters, self.exec_args, compiler, self.nexec)
                tmp_dict.update(avg_papi_counters)
            # Average time
            avg_time = Timing.measure_benchmark(
                self.basename, "time", self.exec_args, compiler, self.nexec)
            tmp_dict.update(avg_time)
        else:
            if quit_on_error:
                return None
            avg_time["time"] = 0
            tmp_dict.update(avg_time)

        tmp_dict.update(
            {
                "FLOPSs": Kernel.compute_flops(flops_eval, self.nruns, avg_time["time"]),
                "CFG": kconfig,
                "Compiler": compiler,
            }
        )
        return tmp_dict

    def __init__(self, cfg):
        # General configuration
        self.kernel = cfg["kernel"]["name"]
        self.descr = cfg["kernel"]["description"]
        self.path_kernel = cfg["kernel"]["path"]
        Kernel.debug = cfg["kernel"]["debug"]

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
        self.flops = self.config_cfg["flops"]

        # Execution arguments
        self.threshold_outliers = self.config_exec["threshold_outliers"]
        self.nexec = self.config_exec["nexec"]
        self.nruns = int(self.config_exec["nruns"])
        self.papi_counters = self.config_exec["papi_counters"]
        self.exec_args = self.config_exec["prefix"]
        self.basename = self.kernel
