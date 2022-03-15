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
from __future__ import annotations
import subprocess
from typing import Optional, Tuple
import datetime as dt
import os
import time
from pathlib import Path
from tqdm.auto import trange
import warnings
import shlex

warnings.filterwarnings("error")

# Third-party libraries
import numpy as np
import pandas as pd

# Local imports
from marta.utils.marta_utilities import pwarning, perror, create_dir_or_pass
from marta.profiler.logger import Logger


class TimingError(Exception):
    pass


class Timing:
    total_time = time.time()
    compilation_time = 0
    execution_time = 0
    dump_files = []

    @staticmethod
    def start_timer(timer_type: str) -> None:
        if timer_type == "compilation":
            Timing.compilation_time = time.time()
        elif timer_type == "execution":
            Timing.execution_time = time.time()
        else:
            raise TypeError

    @staticmethod
    def accm_timer(timer_type: str) -> None:
        if timer_type == "compilation":
            Timing.compilation_time = time.time() - Timing.compilation_time
        elif timer_type == "execution":
            Timing.execution_time = time.time() - Timing.execution_time
        else:
            raise TypeError

    @staticmethod
    def save_total_time() -> None:
        Timing.total_time = time.time() - Timing.total_time

    @staticmethod
    def to_seconds(t: float) -> float:
        """Compute seconds elapsed

        :param t: Time elapsed
        :type t: float
        :return: Seconds elapsed
        :rtype: float
        """
        return dt.timedelta(seconds=int(t))

    @staticmethod
    def show_error(line: str, events: list) -> None:
        pwarning(f"Execution did not return a numeric value: \n'{line}'")
        if "FAILED" in line:
            print("Executions need to have access to PAPI library")
            print("Seems you do not have access, try: ")
            print("\tsudo sh -c 'echo -1 >/proc/sys/kernel/perf_event_paranoid'")
            print("Or maybe you just misspelled an event:")
            for e in events:
                print(f"\t{e}")
            print(
                "Check if listed events are available in the machine using 'papi_avail' or 'papi_native_avail'"
            )

    @staticmethod
    def dump_values(
        code: str,
        exec_opts: str,
        compiler: str,
        compiler_flags: str = "-O3",
        bin_path: str = "",
    ) -> None:
        create_dir_or_pass("dumps")
        # Save execution values in an array
        benchmark_type = f"dump"
        compiler_flags_suffix = compiler_flags.replace(" ", "_").replace("-", "")
        if not bin_path.endswith("/"):
            bin_path += "/"
        cmd_line = f"./{bin_path}marta_profiler_data/dumps/{code}_{compiler}_{compiler_flags_suffix}_{benchmark_type}.o"
        if exec_opts != "" and isinstance(exec_opts, str):
            cmd_line = f"{exec_opts} {cmd_line}"
        cmd_line = shlex.split(cmd_line)
        dump_file = f"/tmp/dumps____tmp_{code}_{compiler}__{compiler_flags_suffix}"
        if "MACVETH" in dump_file:
            dump_file = dump_file.replace("MACVETH", "") + "MACVETH"
        else:
            Timing.dump_files.append(dump_file)
        with open(dump_file, "w") as f:
            p = subprocess.Popen(cmd_line, stderr=f)
            p.wait()

    @staticmethod
    def compute_results(results, threshold_outliers, benchmark_type):
        if len(results.shape) > 0: results = np.sort(results)[1:-1]
        res_mean = np.mean(results)
        res_dev = np.std(results)
        avg_dev = np.divide(
            100.0 * res_dev, res_mean, out=np.zeros(res_mean.size), where=res_mean != 0
        )
        outliers = False
        for val in range(avg_dev.size):
            if avg_dev[val] > threshold_outliers:
                outliers = True
                Logger.warning(
                    f"Deviation exceeding threshold: {avg_dev[val]:2.1f}% ({threshold_outliers}%, {benchmark_type.upper()} benchmark)"
                )

        # Filter values
        mask = ~(np.abs(results - res_mean) <= threshold_outliers * res_dev)
        filtered_results = np.where(mask, np.nan, results)
        mean_results = np.nanmean(filtered_results, axis=0)
        if outliers and isinstance(mean_results, np.ndarray):
            Logger.info(
                f"Mean values after removing outliers: {' '.join(map(lambda x: f'{x:.2f}', mean_results))}"
            )

        # Retrieve percentage of discarded values
        discarded_values = float(mask.sum()) / results.size
        if discarded_values > 0.25:
            pwarning(f"Discarded values = {discarded_values:.2f}")
        return mean_results, discarded_values

    @staticmethod
    def compute_multithread(
        results,
        discard_outliers: bool,
        compute_avg: bool,
        nexec: int,
        nsteps: int,
        benchmark_type,
    ) -> Tuple[dict, Optional[int]]:
        df = pd.DataFrame(results).rename({0: "n_thread"}, axis=1)
        df["n_thread"] = df["n_thread"].apply(int)
        df = df.set_index("n_thread") / nsteps
        if nexec > 1:
            if compute_avg:
                results = df.groupby("n_thread", axis=0).mean()
            else:
                results = df.groupby("n_thread", axis=0).min()
        tmp = results.columns.values.tolist()
        if not isinstance(benchmark_type, list):
            benchmark_type = [benchmark_type]
            col_dict = dict(zip(tmp, benchmark_type))
            results.rename(col_dict, axis=1, inplace=True)
        return results, 0

    @staticmethod
    def read_results(tmp_file, benchmark_type):
        try:
            results = np.loadtxt(tmp_file, delimiter=",")
        except UserWarning as e:
            perror(f"{e}")
        except ValueError:
            line = ""
            with open(tmp_file) as f:
                line = " ".join([l for l in f if "FAILED" in l])
            Timing.show_error(line, benchmark_type)
            return None, None
        except Exception as E:
            perror(f"Something went wrong when executing: {E}")
        except RuntimeWarning as R:
            perror(f"Treating warnings as error: {R}")
        return results

    @staticmethod
    def measure_benchmark(
        code: str,
        benchmark_type: str,
        exec_opts: str = "",
        compiler: str = "gcc",
        compiler_flags: str = "-O3",
        nexec: int = 10,
        nsteps: int = 10000,
        threshold_outliers: int = 3,
        discard_outliers: bool = True,
        compute_avg: bool = True,
        bin_file: str = "",
        bin_path: str = "",
        tmp_file: str = "",
        redirect_stdout: bool = False,
        multithread: bool = False,
    ) -> Tuple[Optional[dict], Optional[int]]:
        """Execute and time given benchmark nexec times

        :param code: Name of the code
        :type code: str
        :param benchmark_type: Benchmark type
        :type benchmark_type: str
        :param exec_opts: Execution parameters, defaults to ""
        :type exec_opts: str, optional
        :param compiler: Name of the compiler, defaults to "gcc"
        :type compiler: str, optional
        :param compiler_flags: Compiler options used, defaults to "-O3"
        :type compiler_flags: str, optional
        :param nexec: Number of execution, defaults to 10
        :type nexec: int, optional
        :param nsteps: Number of TSTEPS, defaults to 10000
        :type nsteps: int, optional
        :param threshold_outliers: Threshold used for discarding outliers, defaults to 3
        :type threshold_outliers: int, optional
        :param discard_outliers: Compute mean and discard outliers, defaults to True
        :type discard_outliers: bool, optional
        :param bin_file: Binary file name, defaults to ""
        :type bin_file: str, optional
        :param tmp_file: Temporal file used, defaults to ""
        :type tmp_file: str, optional
        :return:  Set of values collected and the number of discarded values
        :rtype: Tuple[Union[None, dict], int]
        """

        cmd_line = bin_file
        if nexec < 3:
            Logger.warning(
                "Consider increasing the number of executions to, at least, 3"
            )
        compiler_flags_suffix = compiler_flags.replace(" ", "_").replace("-", "")
        if (
            bin_file != ""
            and not bin_file.startswith("./")
            and not os.path.exists(bin_file)
        ):
            cmd_line = f"./{bin_file}"
        env = os.environ.copy()
        if bin_file == "":
            cmd_line = f"./{bin_path}/{code}_{compiler}_{compiler_flags_suffix}_{benchmark_type}.o {nsteps}"
            if exec_opts != "" and isinstance(exec_opts, str):
                exec_opts_list = exec_opts.split(" ")
                commands = ""
                environment_vars = []
                for e in exec_opts_list:
                    if not "=" in e:
                        commands += f"{e} "
                    else:
                        environment_vars.append(e)
                environment_vars = [i.split("=") for i in environment_vars]
                key_list = []
                val_list = []
                for k, v in environment_vars:
                    key_list.append(k)
                    val_list.append(v)
                cmd_line = f"{commands} {cmd_line}"
                env.update(dict(zip(key_list, val_list)))

        if tmp_file == "":
            tmp_file = f"/tmp/___marta_results.txt"

        if os.path.exists(tmp_file):
            os.remove(tmp_file)
        Path(tmp_file).touch()

        cmd_list = shlex.split(cmd_line)

        def __measure(env: dict = {}, file=None, f=lambda: None):
            for _ in trange(
                nexec, leave=False, desc=f"{benchmark_type.upper():4} exec."
            ):
                p = subprocess.Popen(cmd_list, stdout=file, env=env)
                p.wait()
                f

        if isinstance(redirect_stdout, str):
            with open(redirect_stdout, "w") as f:
                __measure(env=env, file=f, f=f.flush())
        else:
            __measure(env=env)

        results = Timing.read_results(tmp_file, benchmark_type)
        if results.size == 0:
            perror("Results are empty: probably there was an error in the execution")

        if not isinstance(results, np.ndarray):
            return None, None

        if multithread:
            return Timing.compute_multithread(
                results, discard_outliers, compute_avg, nexec, nsteps, benchmark_type
            )

        results = np.divide(results, nsteps)
        if not compute_avg:
            if nexec != 1:
                results = np.min(results, axis=0)
            if isinstance(benchmark_type, list) and len(benchmark_type) > 1:
                return dict(zip(benchmark_type, results)), 0
            else:
                if isinstance(benchmark_type, list):
                    benchmark_type = benchmark_type[0]
                return {benchmark_type: results}, 0

        if not discard_outliers:
            return results, -1

        mean_results, discarded_values = Timing.compute_results(
            results, threshold_outliers, benchmark_type
        )

        # Return mean values in a dictionary fashion
        if isinstance(benchmark_type, list) and len(benchmark_type) > 1:
            return dict(zip(benchmark_type, mean_results)), discarded_values
        else:
            if isinstance(benchmark_type, list):
                benchmark_type = benchmark_type[0]
            return {benchmark_type: mean_results}, discarded_values
