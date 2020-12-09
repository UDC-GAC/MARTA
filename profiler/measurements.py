import os


def time_benchmark(code, name, nexec, exec_opts):
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

    if nexec < 3:
        print(
            "For time_bench nexec must be, at least, 3; changing to this minimum value..."
        )
        nexec = 3

    # Execute nexec times
    # NOTE: you could do this probably capturing stdout, but you do not want to
    # pollute execution by creating a subprocess
    os.system(f"{exec_opts} ./bin/{code}_{name}.o  > tmp/____tmp_{name}")
    for _ in range(1, nexec):
        os.system(f"{exec_opts} ./bin/{code}_{name}.o  >> tmp/____tmp_{name}")

    # Save values in an array
    val = []
    for l in open(f"tmp/____tmp_{name}"):
        val.append(float(l))
    val.sort()

    # Remove first and last and compute the average
    avg_val = sum(val[1:-1]) / len(val[1:-1])

    return avg_val
