import os
import sys
import numpy as np


class Timing:
    @staticmethod
    def error_and_exit(l):
        print("Execution did not return a numeric value.")
        if "FAILED" in l:
            print("Executions need to have access to PAPI library")
            print("Seems you do not have access, try: ")
            print(
                "\tsudo sh -c 'echo -1 >/proc/sys/kernel/perf_event_paranoid'"
            )
        sys.exit(1)

    @staticmethod
    def measure_benchmark(code, name, exec_opts, nexec=10, threshold_outliers=3):
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
        :return: Average time value
        :rtype: int
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

        # Execute nexec times
        # NOTE: you could do this probably capturing stdout, but you do not want to
        # pollute execution by creating a subprocess
        os.system(f"{exec_opts} ./bin/{code}_{name}.o  > tmp/____tmp_{name}")
        for _ in range(1, nexec):
            os.system(
                f"{exec_opts} ./bin/{code}_{name}.o  >> tmp/____tmp_{name}")

        # Save values in an array
        aval = np.array([])

        if type(name) == str:
            for l in open(f"tmp/____tmp_{name}"):
                ltmp = l.split(",")
                try:
                    new_value = float(l)
                    aval = np.append(aval, new_value)
                except ValueError:
                    Timing.error_and_exit(l)

            # discard outliers: |x - mean(x)| > threshold * std(x)
            mean_values = aval[
                abs(aval - aval.mean()) < threshold_outliers * aval.std()
            ].mean()
            return mean_values

        # if name is not a string, it means there are PAPI counters
        for l in open(f"tmp/____tmp_{name}"):
            ltmp = l.split(",")
            try:
                new_value = [float(val) for val in ltmp]
                aval = np.append(aval, new_value)
            except ValueError:
                Timing.error_and_exit(l)

        mean_values = aval[
            abs(aval - aval.mean(axis=1)) < threshold_outliers * aval.std(axis=1)
        ].mean(axis=1)
        return dict(zip(name, mean_values))
