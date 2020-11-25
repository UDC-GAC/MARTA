import os


def time_benchmark(code, name, nexec, exec_opts):
    """Measure benchmark

    Args:
        code ([type]): [description]
        name ([type]): [description]

    Returns:
        [type]: [description]
    """
    try:
        os.mkdir("tmp")
    except FileExistsError:
        os.system("rm tmp/*")

    # Execute nexec times
    os.system(f"{exec_opts} ./bin/{code}_{name}.o  > tmp/____tmp_{name}")
    for _ in range(1, nexec):
        os.system(f"{exec_opts} ./bin/{code}_{name}.o  >> tmp/____tmp_{name}")

    # Save values in an array
    val = []
    for l in open(f"tmp/____tmp_{name}"):
        val.append(float(l))
    val.sort()

    # FIXME: Write values in file
    # with open((f"{name}_{code}"), "a+") as f:
    #     for v in val:
    #         f.write(f"{str(v)},")
    #     f.write("\n")
    avg_val = sum(val[1:-1]) / len(val[1:-1])

    # Keep it clean
    os.system(f"rm -Rf tmp")
    return avg_val
