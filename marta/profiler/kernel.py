#!/bin/python3
# -*- coding: utf-8 -*-
import os
import sys
import time
import pickle
from report import Report
from asm_analyzer import ASMParserFactory
from timing import Timing


class Kernel:
    debug = False
    total_time = time.time()
    compilation_time = 0
    execution_time = 0

    @staticmethod
    def start_timer():
        return time.time()

    def accm_timer(self, timer_type, t0):
        if timer_type == "compilation":
            self.compilation_time += time.time() - t0
        else:
            self.execution_time += time.time() - t0

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
        df = df.fillna(-1)
        df.to_csv(filename, index=False)

        # saving all data to file
        self.total_time = time.time() - self.total_time
        report_filename = filename.replace(".csv", ".log")
        with open(report_filename, "w") as f:
            f.write(Report.generate_report(self))

    @staticmethod
    def compile_parse_asm(
        kpath, comp, common_flags, kconfig, other_flags="", suffix_file="", debug="",
    ):
        """
        Compile benchmark according to a set of flags, suffixes and so

        :param common_flags: Flags which are common for all versions
        :type common_flags: str
        :param custom_flags: Flags which are target-dependent
        :type custom_flags: str
        :param suffix_file: Suffix
        :type suffix_file: str
        :param debug: Suffix for execution command in order to redirect output if any
        :type debug: str
        :return: Dictionary of ASM occurrences
        :rtype: dict
        """

        # Check if options in kernel config string:
        tok = kconfig.split(" ")
        for t in tok:
            if "-D" in t:
                kconfig = kconfig.replace(t, "")
                common_flags += f" {t} "
                continue
            if "=" in t:
                kconfig = kconfig.replace(t, "")
                other_flags += f" {t} "

        comp_str = (
            f"make -B -C {kpath} COMP={comp}"
            f" KERNEL_CONFIG='{kconfig}' "
            f" COMMON_FLAGS='{common_flags}' "
            f" SUFFIX_ASM='{suffix_file}' "
            f" {other_flags} "
            f" {debug}"
        )
        ret = os.system(comp_str)

        if ret != 0:
            print(f"Error {str(ret)} compiling in {kpath}, quitting...")
            return False
        return True

    def define_papi_counters(self):
        """
        Define PAPI counters in a new file recognized by PolyBench/C
        """
        papi_counter_file = "kernels/utilities/papi_counters.list"
        try:
            f = open(papi_counter_file, "w")
        except Exception:
            print("[FATAL ERROR] PAPI counters file could not have been set.")
            sys.exit(1)
        with f:
            for ctr in self.papi_counters:
                f.write('"' + str(ctr) + '",\n')

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
            return (flops_eval) / avg_time
        else:
            return 0

    @staticmethod
    def get_dict_from_d_flags(params):
        d = {}
        for tok in params.strip().split(" "):
            tmp = tok.split("=")
            key = tmp[0].replace("-D", "")
            if len(tmp) == 1:
                value = 1
            else:
                value = tmp[1]
            d.update({key: value})
        return d

    @staticmethod
    def get_suffix_and_flags(kconfig, params):
        custom_flags = ""
        suffix_file = ""
        # Parsing parameters
        if type(params) is dict:
            for pname in params.keys():
                try:
                    param_val_parsed = int(params[pname])
                except ValueError:
                    # NOTE: for includes or other paths, \"string\" notation is
                    # needed, but this is not MARTA's responsibility.
                    param_val_parsed = '"' + params[pname] + '"'
                # FIXME:
                if pname != "ASM_NAME":
                    custom_flags += f" -D{pname}={param_val_parsed}"
                suffix_file += f"_{pname}{params[pname]}"
            suffix_file = suffix_file.split("/")[-1].replace(".c", "")
        else:
            custom_flags = params
            for p in params.strip().replace("-", "").replace("D", "").split(" "):
                suffix_file += f"_{p}"
        # Parsing kconfig
        for kparam in kconfig.strip().replace("-", "").split(" "):
            suffix_file += f"_{kparam}"
        # Avoid very long names
        if len(suffix_file) > 200:
            suffix_file = suffix_file[:200]
        return suffix_file, custom_flags

    @staticmethod
    def get_asm_name(params):
        if not type(params) is dict:
            return ""
        # Parsing parameters
        for pname in params.keys():
            try:
                param_val_parsed = int(params[pname])
            except ValueError:
                # NOTE: for includes or other paths, \"string\" notation is
                # needed, but this is not MARTA's reponsability.
                param_val_parsed = '"' + params[pname] + '"'
            # FIXME:
            if pname == "ASM_NAME":
                return f" {pname}={param_val_parsed}"
        return ""

    def compile(self, product_params, compiler, debug, quit_on_error=False):
        tmp = pickle.loads(product_params)
        kconfig = tmp["KERNEL_CFG"]
        del tmp["KERNEL_CFG"]
        params_dict = tmp
        suffix_file, custom_flags = Kernel.get_suffix_and_flags(kconfig, params_dict)

        custom_flags += self.compiler_flags[compiler]
        local_common_flags = self.common_flags + custom_flags
        local_common_flags += f" -DNRUNS={self.nsteps} "
        if self.cpu_affinity != -1:
            local_common_flags += f" -DMARTA_CPU_AFFINITY={self.cpu_affinity} "

        # MACVETH flags
        other_flags = Kernel.get_asm_name(params_dict) + " "
        if "MACVETH" in kconfig:
            kconfig = kconfig.replace("MACVETH", "")
            other_flags = " MACVETH=true "
            suffix_file += "_macveth"
            other_flags += (
                " MVPATH=" + self.mvpath + " MACVETH_FLAGS='" + self.macveth_flags + "'"
            )
        # MACVETH syntax flags
        other_flags += f" ASM_SYNTAX={self.asm_syntax} "

        if self.measure_time:
            other_flags += f" TIME=true "

        if self.measure_tsc:
            other_flags += f" TSC=true "

        if len(self.papi_counters) > 0:
            other_flags += f" PAPI=true "

        if not self.inlined:
            other_flags += f" COMPILE_KERNEL=true "

        if self.asm_analysis:
            other_flags += f" ASM_CODE=true "

        ret = Kernel.compile_parse_asm(
            self.path_kernel,
            compiler,
            local_common_flags,
            kconfig,
            other_flags,
            suffix_file,
            debug,
        )
        if not ret and quit_on_error:
            return None
        return []

    def run(self, product_params, compiler):
        tmp_dict = {}
        avg_papi_counters = dict.fromkeys(self.papi_counters)
        tmp = pickle.loads(product_params)
        kconfig = tmp["KERNEL_CFG"]
        del tmp["KERNEL_CFG"]
        params_dict = tmp
        name_bin, _ = Kernel.get_suffix_and_flags(kconfig, params_dict)
        name_bin = self.basename + "_" + name_bin
        if self.asm_analysis:
            asm_dict = ASMParserFactory.parse_asm(
                self.asm_syntax, f"asm_codes/{name_bin}_{compiler}.s"
            )
            tmp_dict.update(asm_dict)

        # Average papi counters
        if len(self.papi_counters) > 0:
            avg_papi_counters, discarded_papi_values = Timing.measure_benchmark(
                name_bin,
                self.papi_counters,
                self.exec_args,
                compiler,
                self.nexec,
                self.nsteps,
                self.threshold_outliers,
                self.mean_and_discard_outliers,
            )
            if discarded_papi_values != -1:
                tmp_dict.update(avg_papi_counters)
                tmp_dict.update({"DiscardedPapiValues": discarded_papi_values})

        if self.measure_time:
            avg_time, discarded_time_values = Timing.measure_benchmark(
                name_bin,
                "time",
                self.exec_args,
                compiler,
                self.nexec,
                self.nsteps,
                self.threshold_outliers,
                self.mean_and_discard_outliers,
            )
            if len(avg_time) == 0:
                print("[ERROR] Something went wrong... Quitting...")
                sys.exit(1)
            if discarded_time_values != -1:
                tmp_dict.update(avg_time)
                tmp_dict.update({"DiscardedTimeValues": discarded_time_values})

        if self.measure_tsc:
            avg_tsc, discarded_tsc_values = Timing.measure_benchmark(
                name_bin,
                "tsc",
                self.exec_args,
                compiler,
                self.nexec,
                self.nsteps,
                self.threshold_outliers,
                self.mean_and_discard_outliers,
            )
            if len(avg_tsc) == 0:
                print("[ERROR] Something went wrong... Quitting...")
                sys.exit(1)
            if discarded_tsc_values != -1:
                tmp_dict.update(avg_tsc)
                tmp_dict.update({"DiscardedTscValues": discarded_tsc_values})
        if type(params_dict) is not list:
            tmp_dict.update(params_dict)
        d = Kernel.get_dict_from_d_flags(kconfig)
        if len(d.keys()) > 0:
            tmp_dict.update(d)
        tmp_dict.update(
            {"CFG": kconfig, "Compiler": compiler,}
        )
        if self.mean_and_discard_outliers:
            if self.measure_time:
                tmp_dict.update(
                    {
                        "FLOPSs": Kernel.compute_flops(
                            self.flops, self.nsteps, avg_time["time"]
                        )
                    }
                )
            return tmp_dict
        list_rows = []
        for execution in range(self.nexec):
            new_dict = tmp_dict.copy()
            new_dict.update(
                {
                    "FLOPSs": Kernel.compute_flops(
                        self.flops, self.nsteps, avg_time[execution]
                    )
                }
            )
            new_dict.update({"nexec": execution})
            if self.measure_tsc:
                new_dict.update({"tsc": avg_time[execution]})
            if self.measure_time:
                new_dict.update({"time": avg_time[execution]})
            if len(self.papi_counters) > 0:
                new_dict.update(
                    dict(zip(self.papi_counters, avg_papi_counters[execution]))
                )
            list_rows += [new_dict]
        return list_rows

    def __init__(self, cfg):
        self.kernel = cfg["kernel"]["name"]
        self.descr = cfg["kernel"]["description"]
        self.path_kernel = cfg["kernel"]["path"]
        self.show_progress_bars = cfg["kernel"]["show_progress_bars"]
        Kernel.debug = cfg["kernel"]["debug"]

        config_comp = cfg["kernel"]["compilation"]
        config_cfg = cfg["kernel"]["configuration"]
        config_exec = cfg["kernel"]["execution"]

        self.compilation_enabled = config_comp["enabled"]
        try:
            self.processes = int(config_comp["processes"])
            if self.processes < 1:
                raise ValueError
            if self.processes > 16:
                print("[WARNING] Careful with high degree of processes for compilation")
        except ValueError:
            print("[ERROR] processes must be an integer greater or equal to one")
            sys.exit(1)
        except KeyError:
            self.processes = 1
        self.compilers_list = list(config_comp["compiler_flags"].keys())
        self.common_flags = config_comp["common_flags"]
        self.compiler_flags = config_comp["compiler_flags"]
        self.inlined = (
            True
            if not "inlined_kernel" in config_comp
            else config_comp["inlined_kernel"]
        )
        self.asm_analysis = (
            config_comp["asm_analysis"] if "asm_analysis" in config_comp else False
        )
        self.asm_syntax = (
            "att" if "asm_syntax" in config_comp else config_comp["asm_syntax"]
        )
        self.comp_debug = config_comp["debug"]

        # Configuration
        self.kernel_cfg = config_cfg["kernel_cfg"]
        self.d_features = (
            [] if not "d_features" in config_cfg else config_cfg["d_features"]
        )
        self.d_flags = [] if not "d_flags" in config_cfg else config_cfg["d_flags"]
        self.flops = config_cfg["flops"]
        try:
            self.mvpath = config_cfg["macveth_path_build"]
        except KeyError:
            self.mvpath = ""
        try:
            self.macveth_flags = config_cfg["macveth_flags"]
        except KeyError:
            self.macveth_flags = ""

        # Execution arguments
        self.execution_enabled = config_exec["enabled"]
        self.measure_time = False if not "time" in config_exec else config_exec["time"]
        self.measure_tsc = False if not "tsc" in config_exec else config_exec["tsc"]
        self.threshold_outliers = config_exec["threshold_outliers"]
        self.mean_and_discard_outliers = config_exec["mean_and_discard_outliers"]
        self.nexec = config_exec["nexec"]
        self.nsteps = int(config_exec["nsteps"])
        self.cpu_affinity = int(config_exec["cpu_affinity"])
        self.papi_counters = config_exec["papi_counters"]
        if len(self.papi_counters) > 0:
            self.define_papi_counters()
        self.exec_args = config_exec["prefix"]
        self.basename = self.kernel
