import os
import sys
import numpy as np


class Timing:
    @staticmethod
    def error_and_exit(line, events):
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
        sys.exit(1)

    @staticmethod
    def measure_benchmark(
        code,
        name,
        exec_opts,
        compiler,
        nexec=10,
        nsteps=1000,
        threshold_outliers=3,
        mean_and_discard_outliers=True,
    ):
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
                + "changing to this minimum value..."
            )
            nexec = 5

        # Save execution values in an array
        suffix = f"{name}" if type(name) == str else "papi"
        bin_file = f"{exec_opts} ./bin/{code}_{compiler}_{suffix}.o {nsteps}"
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
            Timing.error_and_exit(line, name)

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
