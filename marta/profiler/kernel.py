#!/bin/python3
# Copyright 2021 Marcos Horro
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

# -*- coding: utf-8 -*-
from __future__ import annotations
from typing import Union
import os
import sys
import pickle
import pandas as pd
from .report import Report
from .asm_analyzer import ASMParserFactory
from .timing import Timing


class Kernel:
    debug = False

    def save_results(
        self,
        df: pd.DataFrame,
        filename: str,
        output_format="csv",
        generate_report=False,
    ) -> None:
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
        if output_format == "html":
            df.to_html(filename, index=False)
        elif output_format == "json":
            df.to_json(filename, index=False)
        else:
            df.to_csv(filename, index=False)

        if generate_report:
            report_filename = filename.replace(".csv", ".log")
            with open(report_filename, "w") as f:
                f.write(Report.generate_report(self))

    @staticmethod
    def compile_parse_asm(
        kpath,
        comp,
        compiler_flags,
        common_flags,
        kconfig,
        other_flags="",
        suffix_file="",
        debug="",
    ) -> bool:
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

        compiler_flags_suffix = compiler_flags.replace(" ", "_").replace("-", "")

        comp_str = (
            f"make -B -C {kpath} COMP={comp} COMP_FLAGS={compiler_flags_suffix} "
            f" KERNEL_CONFIG='{kconfig}' "
            f" COMMON_FLAGS='{common_flags}' "
            f" SUFFIX_ASM='{suffix_file}' "
            f" {other_flags} "
            f" {debug}"
        )
        ret = os.system(comp_str)

        if ret != 0:
            # os.system returns a 16-bit value: 8 LSB for the signal, 8 MSB for
            # the code
            exit_code = int(ret) >> 8
            exit_signal = int(ret) & 0xFF
            print(
                f"make exited with code '{str(exit_code)}' (signal '{exit_signal}') when compiling in {kpath}."
            )
            return False
        return True

    def define_papi_counters(self) -> None:
        """
        Define PAPI counters in a new file recognized by PolyBench/C
        """
        path = os.getcwd()
        if self.papi_counters_path != None:
            path = f"{path}/utilities/{self.papi_counters_path}"
        papi_counter_file = f"{path}/papi_counters.list"
        try:
            f = open(papi_counter_file, "w")
        except Exception:
            print("[FATAL ERROR] PAPI counters file could not have been set.")
            sys.exit(1)
        with f:
            for ctr in self.papi_counters:
                f.write('"' + str(ctr) + '",\n')

    @staticmethod
    def compute_flops(flops: float, avg_time: Union[float, int, str]) -> float:
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
            return 0.0

    @staticmethod
    def get_dict_from_d_flags(params) -> dict:
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
    def get_suffix_and_flags(kconfig, params) -> tuple[str, str]:
        custom_flags = ""
        suffix_file = ""
        custom_bin_name = None
        # Parsing parameters
        if type(params) is dict:
            for pname in params.keys():
                try:
                    param_val_parsed = int(params[pname])
                except ValueError:
                    # NOTE: for includes or other paths, \"string\" notation is
                    # needed, but this is not MARTA's responsibility.
                    param_val_parsed = '"' + params[pname] + '"'
                except TypeError:
                    print(params[pname])
                if pname != "ASM_NAME":
                    custom_flags += f" -D{pname}={param_val_parsed}"
                if pname == "BIN_NAME":
                    custom_bin_name = params[pname]
                suffix_file += f"_{pname}{params[pname]}"
            suffix_file = suffix_file.split("/")[-1].replace(".c", "")
        else:
            custom_flags = params
            for p in params.strip().replace("-", "").replace("D", "").split(" "):
                suffix_file += f"_{p}"
        # Parsing kconfig
        for kparam in kconfig.strip().replace("-", "").split(" "):
            if "BIN_NAME" in kparam:
                custom_bin_name = kparam.split("=")[1]
            suffix_file += f"_{kparam}"
        # Avoid very long names
        if custom_bin_name != None:
            suffix_file = custom_bin_name
        if len(suffix_file) > 256:
            print(
                "Error: too long binary name. Try '-DBIN_NAME=<suffix>' for each compilation case instead"
            )
            sys.exit(1)
        return suffix_file, custom_flags

    @staticmethod
    def get_asm_name(params) -> str:
        if not type(params) is dict:
            return ""
        # Parsing parameters
        for pname in params.keys():
            try:
                param_val_parsed = int(params[pname])
            except ValueError:
                # NOTE: for includes or other paths, \"string\" notation is
                # needed, but this is not MARTA's responsibility.
                param_val_parsed = '"' + params[pname] + '"'
            # FIXME:
            if pname == "ASM_NAME":
                return f" {pname}={param_val_parsed}"
        return ""

    def compile(
        self, product_params, compiler, compiler_flags, debug: bool, quit_on_error=False
    ) -> bool:
        # FIXME: refactor this garbage, please
        tmp = pickle.loads(product_params)
        kconfig = tmp["KERNEL_CFG"]
        del tmp["KERNEL_CFG"]
        params_dict = tmp
        suffix_file, custom_flags = Kernel.get_suffix_and_flags(kconfig, params_dict)

        custom_flags += compiler_flags
        local_common_flags = self.common_flags + custom_flags
        local_common_flags += f" -DNRUNS={self.nsteps} "
        if self.cpu_affinity != -1:
            local_common_flags += f" -DMARTA_CPU_AFFINITY={self.cpu_affinity} "

        # MARTA flags
        if self.init_data:
            local_common_flags += f" -DMARTA_INIT_DATA=1 "
        if self.intel_cache_flush:
            local_common_flags += (
                f" -DMARTA_INTEL_FLUSH_DATA=1 -DPOLYBENCH_NO_FLUSH_CACHE "
            )

        # MACVETH flags
        other_flags = Kernel.get_asm_name(params_dict) + " "
        if "MACVETH" in kconfig:
            kconfig = kconfig.replace("MACVETH", "")
            other_flags = " MACVETH=true "
            local_common_flags += " -DMACVETH=1 "
            other_flags += (
                " MVPATH=" + self.mvpath + " MACVETH_FLAGS='" + self.macveth_flags + "'"
            )
            if self.macveth_target != "":
                try:
                    macveth_target = (
                        tmp[self.macveth_target].replace(".c", "").replace(".spf", "")
                    )
                    other_flags += f" MACVETH_TARGET={macveth_target} "
                except KeyError:
                    print("Error: bad key for MACVETH target")
                    sys.exit(1)

        # MACVETH syntax flags
        other_flags += f" ASM_SYNTAX={self.asm_syntax} "

        if self.measure_time:
            other_flags += f" TIME=true "

        if self.measure_tsc:
            other_flags += f" TSC=true "

        if self.check_dump:
            other_flags += f" DUMP=true "

        if self.papi_counters != None:
            other_flags += f" PAPI=true "

        if not self.inlined:
            other_flags += f" KERNEL_INLINED=true "

        if self.kernel_compilation == "apart":
            other_flags += f" COMPILE_KERNEL=true "

        if self.asm_analysis:
            if self.kernel_compilation == "infile":
                other_flags += f" ASM_CODE_MAIN=true "
            else:
                other_flags += f" ASM_CODE_KERNEL=true "

        ret = Kernel.compile_parse_asm(
            self.path_kernel,
            compiler,
            compiler_flags,
            local_common_flags,
            kconfig,
            other_flags,
            suffix_file,
            debug,
        )
        if not ret and quit_on_error:
            return False
        return True

    def run(self, product_params, compiler: str, compiler_flags="") -> list:
        # FIXME: refactor this...
        tmp_dict = dict()
        if self.papi_counters != None:
            avg_papi_counters = dict.fromkeys(self.papi_counters)
        tmp = pickle.loads(product_params)
        kconfig = tmp["KERNEL_CFG"]
        del tmp["KERNEL_CFG"]
        params_dict = tmp
        name_bin, _ = Kernel.get_suffix_and_flags(kconfig, params_dict)
        name_bin = self.kernel + "_" + name_bin
        compiler_flags_suffix = compiler_flags.replace(" ", "_").replace("-", "")
        if self.asm_analysis:
            asm_dict = ASMParserFactory.parse_asm(
                self.asm_syntax,
                f"asm_codes/{name_bin}_{compiler}_{compiler_flags_suffix}.s",
            )
            tmp_dict.update(asm_dict)

        # Parse output from MACVETH to
        if "MACVETH" in kconfig:
            file_name = (
                "kernels/matrices/___" + name_bin.replace("matrices_", "") + ".log"
            )
            macveth_cols = ["Scop Vect.", "Scop Skipped"]
            macveth_info = dict(zip(macveth_cols, [0, 0]))
            with open(file_name) as f:
                for l in f.readlines():
                    if "Region vectorized" in l:
                        macveth_info["Scop Vect."] += 1
                    if "Skipping region" in l:
                        macveth_info["Scop Skipped"] += 1
                # os.system(f"rm {file_name}")
            tmp_dict.update(macveth_info)

        # Dump values: -DPOLYBENCH_DUMP_ARRAYS
        if self.check_dump:
            Timing.dump_values(name_bin, self.exec_args, compiler)

        # Average papi counters
        if self.papi_counters != None:
            avg_papi_counters, discarded_papi_values = Timing.measure_benchmark(
                name_bin,
                self.papi_counters,
                self.exec_args,
                compiler,
                compiler_flags,
                self.nexec,
                self.nsteps,
                self.threshold_outliers,
                self.mean_and_discard_outliers,
            )
            if type(avg_papi_counters) == type(None):
                return None
            if discarded_papi_values != -1:
                tmp_dict.update(avg_papi_counters)
                tmp_dict.update({"DiscardedPapiValues": discarded_papi_values})

        if self.measure_time:
            avg_time, discarded_time_values = Timing.measure_benchmark(
                name_bin,
                "time",
                self.exec_args,
                compiler,
                compiler_flags,
                self.nexec,
                self.nsteps,
                self.threshold_outliers,
                self.mean_and_discard_outliers,
            )
            if type(avg_time) == type(None):
                return None
            if discarded_time_values != -1:
                tmp_dict.update(avg_time)
                tmp_dict.update({"DiscardedTimeValues": discarded_time_values})

        if self.measure_tsc:
            avg_tsc, discarded_tsc_values = Timing.measure_benchmark(
                name_bin,
                "tsc",
                self.exec_args,
                compiler,
                compiler_flags,
                self.nexec,
                self.nsteps,
                self.threshold_outliers,
                self.mean_and_discard_outliers,
            )
            if type(avg_tsc) == type(None):
                return None
            if discarded_tsc_values != -1:
                tmp_dict.update(avg_tsc)
                tmp_dict.update({"DiscardedTscValues": discarded_tsc_values})
        if type(params_dict) is not list:
            tmp_dict.update(params_dict)
            for key in params_dict:
                self.flops = self.flops.replace(key, str(params_dict[key]))
        d = Kernel.get_dict_from_d_flags(kconfig)
        if len(d.keys()) > 0:
            tmp_dict.update(d)
        tmp_dict.update(
            {"CFG": kconfig, "Compiler": compiler, "compiler_flags": compiler_flags}
        )

        if self.mean_and_discard_outliers:
            if self.measure_time:
                tmp_dict.update(
                    {"FLOPSs": Kernel.compute_flops(self.flops, avg_time["time"])}
                )
            return tmp_dict
        list_rows = []
        for execution in range(self.nexec):
            new_dict = tmp_dict.copy()
            new_dict.update(
                {"FLOPSs": Kernel.compute_flops(self.flops, avg_time[execution])}
            )
            new_dict.update({"nexec": execution})
            if self.measure_tsc:
                new_dict.update({"tsc": avg_time[execution]})
            if self.measure_time:
                new_dict.update({"time": avg_time[execution]})
            if self.papi_counters != None:
                new_dict.update(
                    dict(zip(self.papi_counters, avg_papi_counters[execution]))
                )
            list_rows += [new_dict]
        return list_rows

    def __init__(self, cfg: dict) -> None:
        try:
            self.kernel = cfg["kernel"]["name"]
        except KeyError:
            print("'name' key is missing!")
            sys.exit(1)
        self.type = cfg["kernel"]["type"] if "type" in cfg["kernel"] else "regular"
        if self.type not in ["regular", "micro"]:
            print("Error: type of benchmarking must be 'regular' or 'micro'")
            sys.exit(1)
        self.descr = cfg["kernel"].get("description", "")
        self.path_kernel = cfg["kernel"].get("path", "./")
        self.show_progress_bars = cfg["kernel"].get("show_progress_bars", True)
        Kernel.debug = cfg["kernel"].get("debug", False)

        try:
            config_cfg = cfg["kernel"]["configuration"]
            config_exec = cfg["kernel"]["execution"]
        except KeyError:
            print(
                "Check your configuration file: 'configuration' and 'execution' keys could be missing..."
            )
            sys.exit(1)

        try:
            config_comp = cfg["kernel"]["compilation"]
        except KeyError:
            config_comp = {}
            print("[WARNING] No compilation options selected: using gcc with no flags")

        self.compilation_enabled = config_comp.get("enabled", True)
        try:
            self.processes = int(config_comp["processes"])
            if self.processes < 1:
                raise ValueError
            if self.processes > 16:
                print(
                    f"[WARNING] Careful with high degree of processes for compilation ({self.processes} processes set)"
                )
        except ValueError:
            print("[ERROR] processes must be an integer greater or equal to one")
            sys.exit(1)
        except KeyError:
            self.processes = 1
        self.compiler_flags = config_comp.get("compiler_flags", {"gcc": [""]})
        self.common_flags = config_comp.get("common_flags", "")
        self.kernel_compilation = config_comp.get("kernel_compilation_type", "infile")
        self.inlined = config_comp.get("kernel_inlined", False)
        self.asm_analysis = config_comp.get("asm_analysis", False)
        self.asm_syntax = config_comp.get("asm_syntax", "att")
        self.comp_debug = config_comp.get("debug", False)

        # Configuration
        self.kernel_cfg = config_cfg.get("kernel_cfg", [""])
        self.d_features = config_cfg.get("d_features", [])
        self.d_flags = config_cfg.get("d_flags", [])
        self.flops = config_cfg.get("flops", 1)
        self.macveth_path = config_cfg.get("macveth_path_buil", "''")
        self.macveth_flags = config_cfg.get("macveth_flags", "-misa=avx2")
        self.macveth_target = config_cfg.get("macveth_target", "")

        # Execution arguments
        self.intel_cache_flush = config_exec.get("intel_cache_flush", False)
        self.init_data = config_exec.get("init_data", False)
        self.check_dump = config_exec.get("check_dump", False)
        self.execution_enabled = config_exec.get("enabled", True)
        self.measure_time = config_exec.get("time", False)
        self.measure_tsc = config_exec.get("tsc", False)
        self.threshold_outliers = config_exec.get("threshold_outliers", 3)
        self.mean_and_discard_outliers = config_exec.get(
            "mean_and_discard_outliers", False
        )
        self.nexec = config_exec.get("nexec", 7)
        self.nsteps = config_exec.get("nsteps", 1000)
        self.cpu_affinity = config_exec.get("cpu_affinity", 0)
        self.papi_counters_path = config_exec.get("papi_counters_path")
        self.papi_counters = config_exec.get("papi_counters")
        if self.papi_counters != None:
            if type(self.papi_counters) != list:
                print("'papi_counters' must be a list of hardware events!")
                sys.exit(1)
            self.define_papi_counters()
        self.exec_args = config_exec.get("prefix", "")
