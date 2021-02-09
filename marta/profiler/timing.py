import os
import sys
import numpy as np


class Timing:
    @staticmethod
    def error_and_exit(line, events):
        print("Execution did not return a numeric value.")
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
            print(
                "For time_bench nexec must be, at least, 5; changing to this minimum value..."
            )
            nexec = 5

        if nexec > 10:
            print("For time_bench maybe more than 10 executions is too much...")

        # Save values in an array
        aval = np.array([])

        suffix = f"{name}" if type(name) == str else "papi"
        bin_file = f"{exec_opts} ./bin/{code}_{compiler}_{suffix}.o"
        tmp_file = f"tmp/____tmp_{code}_{compiler}_{suffix}"
        os.system(f"{bin_file}  > {tmp_file}")
        for _ in range(1, nexec):
            os.system(f"{bin_file}  >> {tmp_file}")

        if type(name) == str:
            for l in open(tmp_file):
                try:
                    new_value = float(l)
                    aval = np.append(aval, new_value)
                except ValueError:
                    Timing.error_and_exit(l, name)

            # discard outliers: |x - mean(x)| > threshold * std(x)
            mean_values = aval[
                abs(aval - aval.mean()) <= threshold_outliers * aval.std()
            ].mean()
            return {name: mean_values}

        # if name is not a string, it means there are PAPI counters
        try:
            aval = np.loadtxt(tmp_file, delimiter=",")
        except ValueError:
            Timing.error_and_exit("", name)

        mean_values = []
        for i in range(len(name)):
            cond = abs(aval - aval.mean(axis=0)
                       )[:, i] <= threshold_outliers * aval[:, i].std()
            mean_values += [aval[cond][:, i].mean()]

        return dict(zip(name, mean_values))
