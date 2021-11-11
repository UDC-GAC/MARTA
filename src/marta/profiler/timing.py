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
from typing import ContextManager, Optional, Tuple
import datetime as dt
import os
import time
from pathlib import Path
import sys
from tqdm.auto import trange
from contextlib import contextmanager, redirect_stdout


# import warnings
# warnings.filterwarnings("error")

# Third-party libraries
import numpy as np

# Local imports
from marta.utils.marta_utilities import pinfo, pwarning, perror, create_dir_or_pass
from marta.profiler.logger import Logger


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

    @contextmanager
    @staticmethod
    def redirect_output():
        pass

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
        discard_outliers=True,
        compute_avg=True,
        bin_file="",
        bin_path="",
        tmp_file="",
        redirect_stdout=False,
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

        if nexec < 3:
            pinfo("Minimum number of executions is 3")
            nexec = 3

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
            if exec_opts != "" and isinstance(exec_opts, str):
                exec_opts_list = exec_opts.split(" ")
                bin_file = [*exec_opts_list] + bin_file
        if tmp_file == "":
            tmp_file = f"/tmp/___marta_results.txt"

        if os.path.exists(tmp_file):
            os.remove(tmp_file)
        Path(tmp_file).touch()

        def measure(file=None, f=lambda: None):
            for _ in trange(
                nexec, leave=False, desc=f"{benchmark_type.upper():4} exec."
            ):
                p = subprocess.Popen(bin_file, stdout=file)
                p.wait()
                f

        if isinstance(redirect_stdout, str):
            with open(redirect_stdout, "w") as f:
                measure(f, f.flush())
        else:
            measure()

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

        # Empty files...
        if not isinstance(results, np.ndarray):
            return None, None

        if compute_avg:
            results = np.divide(results, nsteps)
        if not discard_outliers:
            return results, -1

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

        # Return mean values in a dictionary fashion
        if isinstance(benchmark_type, list) and len(benchmark_type) > 1:
            return dict(zip(benchmark_type, mean_results)), discarded_values
        else:
            if isinstance(benchmark_type, list):
                benchmark_type = benchmark_type[0]
            return {benchmark_type: mean_results}, discarded_values
