import os


def time_benchmark(code, name, nexec, exec_opts):
    """
    Execute given benchmark

    :param code: [description]
    :type code: [type]
    :param name: [description]
    :type name: [type]
    :param nexec: [description]
    :type nexec: [type]
    :param exec_opts: [description]
    :type exec_opts: [type]
    :return: [description]
    :rtype: [type]
    """
    try:
        os.mkdir("tmp")
    except FileExistsError:
        pass

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
