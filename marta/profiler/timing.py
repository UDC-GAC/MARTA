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

from __future__ import annotations
from typing import Union
import datetime as dt
import os
import numpy as np
import time


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
        print(f"Execution did not return a numeric value: \n'{line}'")
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
        try:
            os.mkdir("dumps")
        except FileExistsError:
            pass
        # Save execution values in an array
        suffix = f"dump"
        bin_file = f"{exec_opts} ./bin/{code}_{compiler}_{suffix}.o 1"
        tmp_file = f"dumps/____tmp_{code}_{compiler}_{suffix}"
        os.system(f"{bin_file}  > {tmp_file}")

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
        tmp_file="",
    ) -> tuple[Union[None, dict], int]:
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
        :rtype: tuple[Union[None, dict], int]
        """
        try:
            os.mkdir("tmp")
        except FileExistsError:
            pass

        if nexec < 5:
            print(
                "For time_bench nexec must be, at least, 5; "
                "changing to this minimum value..."
            )
            nexec = 5

        compiler_flags_suffix = compiler_flags.replace(" ", "_").replace("-", "")

        # Save execution values in an array
        suffix = f"{benchmark_type}" if type(benchmark_type) == str else "papi"
        if bin_file != "" and not bin_file.startswith("./"):
            bin_file = f"./{bin_file}"
        if bin_file == "":
            bin_file = f"{exec_opts} ./bin/{code}_{compiler}_{compiler_flags_suffix}_{suffix}.o {nsteps}"
        if tmp_file == "":
            tmp_file = f"tmp/____tmp_{code}_{compiler}_{suffix}"
        os.system(f"{bin_file}  > {tmp_file}")
        for _ in range(1, nexec):
            os.system(f"{bin_file}  >> {tmp_file}")

        try:
            results = np.loadtxt(tmp_file, delimiter=",")
        except ValueError:
            line = ""
            with open(tmp_file) as f:
                line = " ".join([l for l in f if "FAILED" in l])
            Timing.show_error(line, benchmark_type)
            return None, None

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
