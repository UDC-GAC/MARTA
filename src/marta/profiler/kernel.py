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

# Standard library
from __future__ import annotations
from math import ceil, floor
from datetime import datetime as dt
import difflib
import filecmp
import os
import pickle
import re
import shutil
from typing import Union

# Third-party libraries
import pandas as pd

# Local imports
from marta.profiler.asm_analyzer import ASMParserFactory
from marta.profiler.compile import (
    compile_makefile,
    get_asm_name,
    get_dict_from_d_flags,
    get_suffix_and_flags,
    vector_report_analysis,
    gen_asm_bench,
)
from marta.profiler.d_features import eval_features
from marta.profiler.report import Report
from marta.profiler.timing import Timing
from marta.profiler.static_code_analyzer import StaticCodeAnalyzer
from marta.profiler.config import parse_kernel_options, get_metadata, get_derived
from marta.profiler.system_config import SystemConfig
from marta.utils.marta_utilities import perror, pwarning, pinfo, marta_exit


class Kernel:
    def _generate_report(self, verbose=True) -> str:
        """Generate report based on the details of the execution

        :param verbose: Verbose mode to display machine information, defaults to True
        :type verbose: bool, optional
        :return: Text file for output
        :rtype: str
        """
        content = f"#" * 80 + "\n"
        content += f"#            MARTA file report: {self.kernel}\n"
        content += f"#" * 80 + "\n"
        if verbose:
            content += f"\n# -- MACHINE INFO\n"
            content += Report.get_machine_info()

        content += f"\n# -- TIME ELAPSED : {Timing.to_seconds(Timing.total_time)}\n"
        content += f"\t- Total Compilation time: {Timing.to_seconds(Timing.compilation_time)}\n"
        content += (
            f"\t- Total Execution time: {Timing.to_seconds(Timing.execution_time)}\n"
        )
        content += f"\n# -- EXPERIMENT PARAMETERS\n"
        content += f"- Kernel name: {self.kernel}\n"
        content += f"- Description: {self.descr}\n"
        content += f"- Compilers used:\n"
        for compiler in self.compiler_flags:
            content += f"\t{compiler} -> {self.compiler_flags[compiler]}\n"
        content += f"- Kernel configurations: {self.kernel_cfg}\n"
        content += f"- FLOPS: {self.flops}\n"
        content += f"- Loop iterations: {self.nsteps}\n"
        content += f"- Number of repetitions: {self.nexec}\n"
        content += f"- CPU affinity (if any): {self.cpu_affinity}\n"
        if self.papi_counters != None:
            content += f"- Hardware counters used:\n"
            for l in self.papi_counters:
                content += f"\t{l}\n"

        # Get compilation flags and so
        content += f"\n# -- COMPILATION (stdout)\n"
        try:
            with open("log/___tmp.stdout", "r") as f:
                for l in f.readlines():
                    content += l
            os.remove("log/___tmp.stdout")
        except FileNotFoundError:
            content += "stdout was redirected manually.\n"

        # Generate errors
        content += f"\n# -- WARNINGS/ERRORS (stderr)\n"
        try:
            with open("log/___tmp.stderr", "r") as f:
                for l in f.readlines():
                    content += l
            os.remove("log/___tmp.stderr")
        except FileNotFoundError:
            content += "stderr was redirected manually.\n"

        return content

    def print_summary(self, df: pd.DataFrame, dimensions: list = []):
        print("\n--------------")
        loop_unroll = ""
        if hasattr(self, "asm_unroll"):
            loop_unroll = f", loop_unroll = {self.asm_unroll}"
        print(
            f"MARTA summary [type = {self.bench_type}, no. exec. = {self.nexec}, tsteps = {self.nsteps}{loop_unroll}]\n"
        )
        line = ""
        headers = ""
        d = []
        if "all" in dimensions or len(dimensions) == 0:
            dimensions = df.columns
        if "PAPI_COUNTERS" in dimensions:
            idx = dimensions.index("PAPI_COUNTERS")
            if self.papi_counters != None and isinstance(self.papi_counters, list):
                dimensions.extend(self.papi_counters)
            del dimensions[idx]
        for i in range(len(dimensions)):
            if dimensions[i] not in df.columns:
                d.append(i)
        for i in d[::-1]:
            del dimensions[i]

        del d

        results = df[dimensions].values
        max_size = (
            df[dimensions]
            .applymap(
                lambda x: len(f"{x:.5f}") if isinstance(x, float) else len(str(x))
            )
            .max()
        )

        for i in range(len(dimensions)):
            max_size[i] = max(max_size[i], len(dimensions[i]))
            d = (max_size[i] - len(dimensions[i])) / 2
            lspace = max(floor(d), 0)
            rspace = max(ceil(d), 0)
            headers += f"|  {' '*lspace}{dimensions[i].upper()}{' '*rspace}  "
            line += f"+--{'-'*max_size[i]}--"
        line += "+"
        headers += "|"
        print(line)
        print(headers)
        print(line)

        for val in results:
            display_val = ""
            for i in range(len(val)):
                sval = val[i]
                l = max_size[i]
                if isinstance(sval, str):
                    sval = val[i][:l]
                elif isinstance(sval, int):
                    sval = f"{sval:{l}d}"
                elif isinstance(sval, float):
                    sval = f"{sval:{l-5}.5f}"
                d = (max_size[i] - len(sval)) / 2
                lspace = max(floor(d), 0)
                rspace = max(ceil(d), 0)
                display_val += f"|  {' '*(lspace+rspace)}{sval}  "
            print(f"{display_val}|")
            print(line)

        print("\n")
        print(f"Compilation time:    {Timing.to_seconds(Timing.compilation_time)}")
        print(f"Execution time:      {Timing.to_seconds(Timing.execution_time)}")
        print(
            f"Total time elapsed:  {Timing.to_seconds(Timing.execution_time + Timing.compilation_time)}\n"
        )
        print("--- END summary")

    def check_correctness(self) -> list:
        if self.check_dump and self.macveth:
            errors = []
            for file in Timing.dump_files:
                if not filecmp.cmp(file, f"{file}MACVETH"):
                    errors.append(file)
            if len(errors) == 0:
                pinfo(
                    "Correctness check for MACVETH went OK according to dumped values."
                )
            for err in errors:
                file_org = open(err, "rt").readlines()
                file_macveth = open(f"{err}MACVETH", "rt").readlines()
                diffs = difflib.Differ().compare(file_org, file_macveth)
                differences = sum([1 for line in diffs if line[:2] == "+ "])
                perror(
                    f"{differences} lines different between dumped files. Check correctness for '{err}'.",
                    exit_on_error=False,
                )
            if len(errors) > 0:
                marta_exit()

    def save_results(self, df: pd.DataFrame, filename: str) -> None:
        """
        Save data as a pandas.DataFrame

        :param df:
        :type df: class:pandas.DataFrame
        :param common_flags: List of flags used for compilation
        :type common_flags: str
        :param exec_args: List of arguments to pass when executing benchmark
        :type exec_args: str
        :param nexec: Number of time to execute whole experiment
        :type nexec: int
        :param filename: Name of the output file
        :type filename: str
        """
        # storing results with metadata, but cleaning first, just in case
        output_format = self.output.get("format", "csv")
        try:
            df.drop([""], axis=1, inplace=True)
        except KeyError:
            pass
        df = df.fillna(0)
        cols = list(df.columns)
        # Set column order
        try:
            cols.remove("compiler")
            cols.remove("compiler_flags")
            cols = ["compiler", "compiler_flags"] + cols
            df = df[cols]
        except ValueError:
            pass

        filename = self.get_kernel_path(f"/marta_profiler_data/{filename}")
        if output_format == "html":
            df.to_html(filename, index=False)
        elif output_format == "json":
            df.to_json(filename, index=False)
        else:
            df.to_csv(filename, index=False)

        if hasattr(self, "generate_report") and self.generate_report:
            report_filename = filename.split(".")[0] + ".log"
            with open(report_filename, "w") as f:
                f.write(self._generate_report())

    def define_papi_counters(self) -> None:
        """
        Define PAPI counters in a new file recognized by PolyBench/C
        """
        if self.papi_counters is None:
            return
        assert isinstance(self.papi_counters, list)
        papi_counter_file = self.get_kernel_path(f"/utilities/papi_counters.list")
        papi_wrapper_counter_file = self.get_kernel_path(
            "/utilities/papi_wrapper/lib/papi_counters.list"
        )
        if len(set(self.papi_counters)) != len(self.papi_counters):
            pwarning("Duplicated counters in PAPI list, skipping them...")
            self.papi_counters = list(set(self.papi_counters))

        try:
            with open(papi_counter_file, "w") as f:
                for ctr in self.papi_counters:
                    f.write('"' + str(ctr) + '",\n')
            if self.multithread:
                with open(papi_wrapper_counter_file, "w") as f:
                    for ctr in self.papi_counters:
                        f.write('"' + str(ctr) + '",\n')
        except FileNotFoundError as f:
            perror(f"Package corrupted: papi_counters.list file not found ('{f}')")
        except Exception as e:
            perror(f"PAPI counters file could not have been set: {e}")

    @staticmethod
    def compute_flops(flops: float, avg_time: Union[float, int, str]) -> float:
        """
        Evaluate FLOPS expression provided by user as string and return a floating
        point value

        :param flops: Expression provided by user, e.g. "X/42", where "X" is a parameter
        :type flops: str
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
            perror("FLOPS formula is not valid; please review it!")

        if avg_time > 0:
            return (flops_eval) / avg_time
        else:
            return 0.0

    def compile(
        self,
        product_params: bytes,
        compiler: str,
        compiler_flags: str,
        quit_on_error=False,
    ) -> bool:
        """Compile a given configuration of the kernel.

        :param product_params: All parameters to be unpacked (pickles)
        :type product_params: bytes
        :param compiler: Compiler name
        :type compiler: str
        :param compiler_flags: Compiler flags used
        :type compiler_flags: str
        :param make_stdout: How to redirect standard output
        :type make_stdout: subprocess.STDOUT
        :param make_stderr: How to redirect error output
        :type make_stderr: subprocess.STDOUT
        :param quit_on_error: Exit execution if errors found, defaults to False
        :type quit_on_error: bool, optional
        :return: `True` is compilation was successfull, `False` otherwise
        :rtype: bool
        """
        tmp_pickle = pickle.loads(product_params)
        kconfig = tmp_pickle["KERNEL_CFG"]
        del tmp_pickle["KERNEL_CFG"]
        params_dict = tmp_pickle
        suffix_file, custom_flags = get_suffix_and_flags(kconfig, params_dict)

        custom_flags += compiler_flags
        local_common_flags = self.common_flags + custom_flags
        local_common_flags += f" -DTSTEPS={self.nsteps} "
        if self.cpu_affinity != -1:
            local_common_flags += f" -DMARTA_CPU_AFFINITY={self.cpu_affinity} "

        # MARTA flags
        if self.cache_flush:
            local_common_flags += f" -DMARTA_FLUSH_DATA=1 "
        else:
            local_common_flags += f" -DMARTA_FLUSH_DATA=0 -DPOLYBENCH_NO_FLUSH_CACHE "

        other_flags = []
        asm_name = get_asm_name(params_dict)
        if asm_name != "":
            other_flags.append(asm_name)

        if "MACVETH" in kconfig:
            kconfig = kconfig.replace("MACVETH", "")
            local_common_flags += " -DMACVETH=1 "
            other_flags.append("MACVETH=true")
            other_flags.append(f"MACVETH_PATH={self.macveth_path}")
            other_flags.append(f"MACVETH_FLAGS={' '.join(self.macveth_flags)}")
            if self.macveth_target != "":
                try:
                    macveth_target = re.sub(".c$", "", tmp_pickle[self.macveth_target])
                    other_flags.append(f" MACVETH_TARGET={macveth_target}")
                except KeyError:
                    perror("Bad key for MACVETH target")

        # ASM syntax flags
        other_flags.append(f"ASM_SYNTAX={self.asm_syntax}")

        other_flags.append(f"LOOP_TYPE={self.loop_type}")

        if self.measure_time:
            other_flags.append("TIME=true")

        if self.measure_tsc:
            other_flags.append("TSC=true")

        if self.multithread:
            other_flags.append("MULTITHREAD=true")
            local_common_flags += " -fopenmp "

        if self.check_dump:
            other_flags.append("DUMP=true")

        if self.papi_counters != None:
            other_flags.append("PAPI=true")

        if not self.inlined:
            other_flags.append("KERNEL_INLINED=true")

        if self.kernel_compilation:
            other_flags.append("COMPILE_KERNEL=true")

        if self.asm_count or self.static_analysis:
            if self.kernel_compilation:
                other_flags.append("ASM_CODE_KERNEL=true")
            other_flags.append("ASM_CODE_MAIN=true")

        main_src = self.main_src
        if self.bench_type == "asm":
            case = params_dict["_ASM_VERSION"]
            asm_init = self.asm_init.get(case, [])
            asm_body = self.asm_body[case]
            if self.asm_permutations:
                perm_indices = [
                    int(idx) for idx in list(params_dict["_ASM_PERMUTATION"])
                ]
                permuted_body = []
                for idx in perm_indices:
                    permuted_body.append(asm_body[idx])
                raw_asm = gen_asm_bench(asm_init, permuted_body, self.asm_unroll)
                main_src = (
                    f"_{case}_perm{params_dict['_ASM_PERMUTATION']}_{self.main_src}"
                )
            elif self.asm_range:
                raw_asm = gen_asm_bench(
                    asm_init,
                    asm_body[: params_dict["_ASM_PERMUTATION"]],
                    self.asm_unroll,
                )
                main_src = (
                    f"_{case}_perm{params_dict['_ASM_PERMUTATION']}_{self.main_src}"
                )
            else:
                raw_asm = gen_asm_bench(asm_init, asm_body, self.asm_unroll)
                main_src = f"_{case}_perm0_{self.main_src}"
            with open(f"{self.path_kernel}/{main_src}", "w") as f:
                f.writelines(raw_asm)

        if shutil.which(compiler) is None:
            return -1

        ret = compile_makefile(
            self.kernel,
            main_src,
            self.path_kernel,
            compiler,
            compiler_flags,
            local_common_flags,
            kconfig,
            other_flags,
            suffix_file,
            self.debug | self.comp_debug,
        )

        return not (not ret and quit_on_error)

    def run(self, product_params: bytes, compiler: str, compiler_flags="") -> list:
        data = {}
        tmp_pickle = pickle.loads(product_params)
        kconfig = tmp_pickle["KERNEL_CFG"]
        del tmp_pickle["KERNEL_CFG"]
        params_dict = tmp_pickle
        name_bin, _ = get_suffix_and_flags(kconfig, params_dict)
        if "MARTA_NUM_THREADS" in params_dict:
            if "OMP_NUM_THREADS" in self.exec_args:
                self.exec_args = re.sub(
                    r"OMP_NUM_THREADS=([0-9]+)",
                    f"OMP_NUM_THREADS={params_dict['MARTA_NUM_THREADS']}",
                    self.exec_args,
                )
            else:
                self.exec_args += f" OMP_NUM_THREADS={params_dict['MARTA_NUM_THREADS']}"
        name_bin = f"{self.kernel}_{name_bin}"
        compiler_flags_suffix = compiler_flags.replace(" ", "_").replace("-", "")

        base_filename = f"{name_bin}_{compiler}_{compiler_flags_suffix}"
        if self.asm_count:
            asm_dict = ASMParserFactory.parse_asm(
                self.asm_syntax,
                self.get_kernel_path(
                    f"/marta_profiler_data/asm_codes/{base_filename}.s"
                ),
            )
            data.update(asm_dict)

        if self.static_analysis:
            self.S.perform_analysis(
                self.get_kernel_path(
                    f"/marta_profiler_data/asm_codes/{base_filename}.s"
                ),
                self.nsteps,
            )
            data.update(self.S.get_data())

        data.update(vector_report_analysis(f"/tmp/{base_filename}.opt", compiler))

        # Dump values: -DPOLYBENCH_DUMP_ARRAYS
        if self.check_dump:
            Timing.dump_values(
                name_bin,
                self.exec_args,
                compiler,
                compiler_flags,
                bin_path=self.get_kernel_path("/"),
            )

        measurements = {
            "papi": self.papi_counters,
            "time": self.measure_time,
            "tsc": self.measure_tsc,
        }
        d_avg_values = {}
        for mtype in measurements:
            if measurements[mtype] is None or (
                isinstance(measurements[mtype], bool) and not measurements[mtype]
            ):
                continue

            raw_values, discarded_values = Timing.measure_benchmark(
                name_bin,
                mtype,
                self.exec_args,
                compiler,
                compiler_flags,
                self.nexec,
                self.nsteps,
                self.threshold_outliers,
                discard_outliers=self.discard_outliers,
                compute_avg=self.compute_avg,
                bin_path=self.get_kernel_path("/marta_profiler_data/bin"),
                redirect_stdout=self.stdout_redirect,
                multithread=self.multithread,
            )
            if not self.multithread:
                if mtype == "papi":
                    if len(self.papi_counters) == 1:
                        d_avg_values[self.papi_counters[0]] = raw_values
                    else:
                        for i in range(len(self.papi_counters)):
                            d_avg_values[self.papi_counters[i]] = raw_values["papi"][i]
                else:
                    d_avg_values[mtype] = raw_values
                if raw_values is None:
                    return None
                if discarded_values != -1:
                    if mtype == "papi" and len(self.papi_counters) != 1:
                        for i in range(len(self.papi_counters)):
                            data.update(
                                {f"{self.papi_counters[i]}": raw_values["papi"][i]}
                            )
                    else:
                        if mtype == "papi":
                            data.update(
                                {f"{self.papi_counters[0]}": raw_values["papi"]}
                            )
                        else:
                            data.update(raw_values)

                    data.update({f"Discarded{mtype}Values": discarded_values})
                if len(d_avg_values) == 0:
                    pwarning(
                        "Nothing executed: set 'time', 'tsc' or at least one PAPI counter"
                    )
            else:
                tmp = raw_values.columns.values.tolist()
                if mtype == "papi":
                    col_dict = dict(zip(tmp, self.papi_counters))
                    raw_values.rename(col_dict, axis=1, inplace=True)
                d_avg_values[mtype] = raw_values

        # Updating parameters
        if not isinstance(params_dict, list):
            data.update(params_dict)
            # sort them by length
            keys = sorted(params_dict.keys(), key=len, reverse=True)
            for key in keys:
                self.flops = self.flops.replace(key, str(params_dict[key]))
        d = get_dict_from_d_flags(kconfig)
        if len(d.keys()) > 0:
            data.update(d)
        if kconfig != [""] and kconfig != "" and kconfig != " ":
            data.update({"CFG": kconfig})
        data.update({"compiler": compiler, "compiler_flags": compiler_flags})

        if not self.multithread:
            # Add metadata
            data.update(get_metadata(self.meta_info, data))
            # Add derived
            data.update(get_derived(self.derived_columns, data))

        # Discard outliers
        if self.measure_time:
            data.update(
                {
                    "FLOPSs": Kernel.compute_flops(
                        self.flops, d_avg_values["time"]["time"]
                    )
                }
            )

        list_rows = []
        if not self.multithread:
            new_dict = data.copy()
            if "time" in d_avg_values:
                new_dict.update(
                    {"FLOPSs": Kernel.compute_flops(self.flops, d_avg_values["time"])}
                )
                new_dict.update({"time": d_avg_values["time"]})
            if "tsc" in d_avg_values:
                if self.measure_tsc:
                    # FIXME:
                    new_dict.update({"tsc": d_avg_values["tsc"]["tsc"]})
            if "papi" in d_avg_values:
                new_dict.update(dict(zip(self.papi_counters, [d_avg_values["papi"]])))
            list_rows += [new_dict]
        else:
            list_rows = pd.DataFrame()
            for key in d_avg_values:
                if not list_rows.empty:
                    list_rows = list_rows.join(d_avg_values[key])
                else:
                    list_rows = d_avg_values[key]
            list_rows = list_rows.reset_index()
            for key in data:
                list_rows[key] = data[key]
            derived = get_derived(self.derived_columns, list_rows)
            for key in derived:
                list_rows[key] = derived[key]
        return list_rows

    def finalize_actions(self):
        self.reset_system_config()
        if self.finalize != None:
            # Cleaning directories
            if self.finalize.get("clean_tmp_files", False):
                os.system(f"rm -Rf tmp/")
                os.system(f"rm -Rf log/")
            if self.finalize.get("clean_bin_files", False):
                os.system(f"rm -Rf bin/")
            if self.finalize.get("clean_asm_files", False):
                os.system(f"rm -Rf asm_codes/")
            if self.finalize.get("command") != None:
                try:
                    os.system(f'{self.finalize.get("command")}')
                except Exception:
                    perror(f"Finalize command went wrong for the kernel")
        self.check_correctness()

    def get_output_filename(self):
        fname = f'{self.kernel}_{self.output.get("name", self.kernel)}'
        tstamp = dt.now().strftime("%d_%m_%y___%H_%M_%S")
        output_filename = (
            f"{fname}_marta_profiler_{tstamp}.{self.output.get('format', 'csv')}"
        )
        return output_filename

    def execute_preamble(self):
        if self.preamble != None and self.preamble.get("command") != None:
            try:
                os.system(f'{self.preamble.get("command")}')
            except Exception:
                perror("Preamble command went wrong...")

    def reset_system_config(self):
        assert hasattr(self, "max_freq") and hasattr(self, "turbo")
        if self.max_freq != "" and self.turbo != "":
            self.system.reset()
            self.system.check_errors("reset")

    def get_kernel_path(self, path: str = ""):
        assert hasattr(self, "path_kernel")
        return self.path_kernel + path

    def get_output_columns(self):
        return self.output.get("columns", "all")

    def emit_report(self):
        return self.output.get("report", False)

    def __init__(self) -> None:
        pass

    def __init__(self, cfg: dict) -> None:
        assert isinstance(cfg, dict)
        parsed_config = parse_kernel_options(cfg)
        for key in parsed_config:
            setattr(self, key, parsed_config[key])
        self.define_papi_counters()
        if self.max_freq != "" and self.turbo != "":
            self.system = SystemConfig({"affinity": [self.cpu_affinity]})
            self.system.tune()
            self.system.check_errors("tune")
        self.execute_preamble()
        if self.static_analysis:
            self.S = StaticCodeAnalyzer("native", self.llvm_mca_binary)
            if not self.S.check_if_compatible_version():
                self.static_analysis = False
                pwarning("LLVM-MCA >= 13.x.x. version required for static analysis")
            else:
                self.static_analysis = True
        self.params = eval_features(self.d_features, self.get_kernel_path())

