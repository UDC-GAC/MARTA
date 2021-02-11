import os
import sys
import numpy as np


class Timing:
    @staticmethod
    def error_and_exit(line, events):
        print(f"Execution did not return a numeric value: {line} {events}")
        if "FAILED" in line:
            print(f"ERROR = {line}")
            print("Executions need to have access to PAPI library")
            print("Seems you do not have access, try: ")
            print(
                "\tsudo sh -c 'echo -1 >/proc/sys/kernel/perf_event_paranoid'"
            )
            print("Or maybe you just misspelled an event:")
            for e in events:
                print(e)
        sys.exit(1)

    @staticmethod
    def measure_benchmark(code, name, exec_opts, compiler, nexec=10, threshold_outliers=3):
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
            print("For time_bench nexec must be, at least, 5; " +
                  "changing to this minimum value...")
            nexec = 5

        # Save values in an array
        aval = np.array([])

        suffix = f"{name}" if type(name) == str else "papi"
        bin_file = f"{exec_opts} ./bin/{code}_{compiler}_{suffix}.o"
        tmp_file = f"tmp/____tmp_{code}_{compiler}_{suffix}"
        os.system(f"{bin_file}  > {tmp_file}")
        for _ in range(1, nexec):
            os.system(f"{bin_file}  >> {tmp_file}")

        try:
            aval = np.loadtxt(tmp_file, delimiter=",")
        except ValueError:
            line = ""
            with open(tmp_file) as f:
                for l in f:
                    if "FAILED" in l:
                        line = l
                        break
            Timing.error_and_exit(line, name)

        mask = ~(abs(aval - aval.mean(axis=0)) <=
                 threshold_outliers * aval.std(axis=0))
        filtered_vals = np.where(mask, np.nan, aval)
        mean_values = np.nanmean(filtered_vals, axis=0)

        # If there is a deviation over more than 40% of values, then a warning
        # is shown in the report
        dev_warning = (np.count_nonzero(mask) > aval.size * .4)

        if type(name) is list:
            return dict(zip(name, mean_values)), dev_warning
        else:
            return {name: mean_values}, dev_warning
