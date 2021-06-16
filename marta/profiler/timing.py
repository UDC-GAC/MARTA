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
import os
import numpy as np


class Timing:
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
        code,
        name,
        exec_opts,
        compiler,
        compiler_flags: str,
        nexec=10,
        nsteps=1000,
        threshold_outliers=3,
        mean_and_discard_outliers=True,
    ) -> tuple[Union[None, float], int]:
        """
        Execute and time given benchmark nexec times

        :param code: Name of benchmark
        :type code: str
        :param name: Suffix to identify concrete benchmark
        :type name: str
        :param nexec: Times to execute benchmark
        :type nexec: int
        :param exec_opts: Suffix before executing with environment variables
        :type exec_opts: str
        :return: Pairs of values
        :rtype: dict
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

        compiler_flags_suffix = compiler_flags.replace(" ", "_").replace("-","")

        # Save execution values in an array
        suffix = f"{name}" if type(name) == str else "papi"
        bin_file = f"{exec_opts} ./bin/{code}_{compiler}_{compiler_flags_suffix}_{suffix}.o {nsteps}"
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
            Timing.show_error(line, name)
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
        if type(name) is list and len(name) > 1:
            return dict(zip(name, mean_results)), discarded_values
        else:
            if type(name) is list:
                name = name[0]
            return {name: mean_results}, discarded_values
