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

# Standard libraries
from __future__ import annotations
import subprocess
from typing import Optional, Tuple
import datetime as dt
import os
import time
import warnings
from tqdm.auto import trange


warnings.filterwarnings("error")

# Third-party libraries
import numpy as np

# Local imports
from marta.utils.marta_utilities import pinfo, pwarning, perror, create_dir_or_pass


class TimingError(Exception):
    pass


class Timing:
    total_time = time.time()
    compilation_time = 0
    execution_time = 0

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
        return dt.timedelta(seconds=t)

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
    def dump_values(code: str, exec_opts: str, compiler: str) -> None:
        create_dir_or_pass("dumps")
        # Save execution values in an array
        suffix = f"dump"
        bin_file = (
            f"{exec_opts} ./marta_profiler_data/bin/{code}_{compiler}_{suffix}.o 1"
        )
        dump_file = f"/tmp/dumps____tmp_{code}_{compiler}_{suffix}"
        with open(dump_file, "w") as f:
            subprocess.Popen([f"{bin_file}"], stdout=f)

    @staticmethod
    def measure_benchmark(
        code: str,
        benchmark_type: str,
        exec_opts="",
        compiler="gcc",
        compiler_flags="-O3",
        nexec=10,
        nsteps=10000,
        threshold_outliers=3,
        mean_and_discard_outliers=True,
        bin_file="",
        bin_path="",
        tmp_file="",
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
        :param mean_and_discard_outliers: Compute mean and discard outliers, defaults to True
        :type mean_and_discard_outliers: bool, optional
        :param bin_file: Binary file name, defaults to ""
        :type bin_file: str, optional
        :param tmp_file: Temporal file used, defaults to ""
        :type tmp_file: str, optional
        :return:  Set of values collected and the number of discarded values
        :rtype: Tuple[Union[None, dict], int]
        """

        if nexec < 5:
            pinfo("Minimum number of executions is 5")
            nexec = 5

        compiler_flags_suffix = compiler_flags.replace(" ", "_").replace("-", "")

        if (
            bin_file != ""
            and not bin_file.startswith("./")
            and not os.path.exists(bin_file)
        ):
            bin_file = [f"./{bin_file}"]
        if bin_file == "":
            bin_file = [
                f"./{bin_path}/{code}_{compiler}_{compiler_flags_suffix}_{benchmark_type}.o",
                f"{nsteps}",
            ]
            if exec_opts != "":
                bin_file = [exec_opts] + bin_file
        if tmp_file == "":
            tmp_file = f"/tmp/____tmp_{code}_{compiler}_{compiler_flags_suffix}_{benchmark_type}"

        if os.path.exists(tmp_file):
            os.remove(tmp_file)

        with open(tmp_file, "a") as f:
            for _ in trange(nexec, leave=False, desc="Executions"):
                p = subprocess.Popen(bin_file, stdout=f)
                p.wait()
                f.flush()

        try:
            results = np.loadtxt(tmp_file, delimiter=",")
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

        results /= nsteps

        if not mean_and_discard_outliers:
            return results, -1

        # Filter values
        mask = ~(
            abs(results - results.mean(axis=0))
            <= threshold_outliers * results.std(axis=0)
        )
        filtered_results = np.where(mask, np.nan, results)
        mean_results = np.nanmean(filtered_results, axis=0)

        # Retrieve percentage of discarded values
        discarded_values = float(mask.sum()) / results.size

        # Return mean values in a dictionary fashion
        if type(benchmark_type) is list and len(benchmark_type) > 1:
            return dict(zip(benchmark_type, mean_results)), discarded_values
        else:
            if type(benchmark_type) is list:
                benchmark_type = benchmark_type[0]
            return {benchmark_type: mean_results}, discarded_values
