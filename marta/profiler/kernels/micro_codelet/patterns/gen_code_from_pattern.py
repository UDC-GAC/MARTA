#!/env/python3

import sys
import numpy as np


def get_offset_1d(val, ub, orig):
    offset = f"{orig}"
    if val < 0:
        m = (int(ub)) * (abs(val) + 1)
        offset = f"{m} + {orig}"
    return offset


def generate_codelet_1d(t1, t2, orig_y="ORIG_y", orig_A="ORIG_A", orig_x="ORIG_x"):
    i_LB = f"{t2[1]}"
    i_UB = f"{t2[0]}"
    offset = get_offset_1d(t1[0], i_UB, orig_y)
    y_idx = f"{t1[0]}*i + {offset}"
    A_idx = f"i + {orig_A}"
    offset = get_offset_1d(t1[1], i_UB, orig_x)
    x_idx = f"{t1[1]}*i + {offset}"

    print(f"for (i = {i_LB}; i <= {i_UB}; ++i) {{")
    print(f"    y[{y_idx}] += A[{A_idx}] * x[{x_idx}];")
    print(f"}}")


def get_offset_2d(val0, val1, ub0, ub1, orig):
    offset = f"{orig}"
    m0 = 0
    if val0 < 0:
        m0 = (int(ub0)) * (abs(val0) + 1)

    m1 = 0
    if val1 < 0:
        m1 = (int(ub1)) * (abs(val1) + 1)

    if val0 < 0 or val1 < 0:
        offset = f"{m0} + {m1} + {orig}"
    return offset


def generate_codelet_2d(t1, t2, orig_y="ORIG_y", orig_A="ORIG_A", orig_x="ORIG_x"):
    i_LB = f"{t2[2]}"
    i_UB = f"{t2[0]}"
    j_LB = f"{t2[3]}"
    j_UB = f"{t2[1]}"

    offset = get_offset_2d(t1[0], t1[1], i_UB, j_UB, orig_y)
    y_idx = f"{t1[0]}*i + {t1[1]}*j + {offset}"
    offset = get_offset_1d(t2[1] + 1, i_UB, orig_A)
    A_idx = f"{int(t2[1])+1}*i + j + {offset}"
    offset = get_offset_2d(t1[2], t1[3], i_UB, j_UB, orig_x)
    x_idx = f"{t1[2]}*i + {t1[3]}*j + {offset}"

    print(f"for (i = {i_LB}; i <= {i_UB}; ++i) {{")
    print(f"    for (j = {j_LB}; j <={j_UB}; ++j) {{")
    print(f"        y[{y_idx}] += A[{A_idx}] * x[{x_idx}];")
    print(f"     }}")
    print(f"}}")


def generate_header_file(name, t1, t2):
    header_name = f"_{name.upper()}_H"
    orig_A = 0
    orig_x = 0
    orig_y = 0
    tmp = abs((t1.reshape((2, -1)) * t2[: len(t2) // 2]).sum(axis=1))
    n_value = np.maximum(tmp.max() + 1, np.prod(np.array(tmp + 1)))
    print(f"#ifndef {header_name}")
    print(f"#define {header_name}")
    print(f"")
    print(f"#ifndef ORIG_y")
    print(f"#define ORIG_y\t{orig_y}")
    print(f"#endif")
    print(f"")
    print(f"#ifndef ORIG_A")
    print(f"#define ORIG_A\t{orig_A}")
    print(f"#endif")
    print(f"")
    print(f"#ifndef ORIG_x")
    print(f"#define ORIG_x\t{orig_x}")
    print(f"#endif")
    print(f"")
    print(f"#define N\t{n_value}\n")
    print(f"#endif /* {header_name} */")


n_codelets = -1
one_codelet = -1
if len(sys.argv) == 2:
    one_codelet = int(sys.argv[1])
if len(sys.argv) == 3:
    n_codelets = int(sys.argv[2])
f = open("pattern-info.txt")

n = 0
for l in f:
    if (n_codelets == -1) & (one_codelet != n):
        n += 1
        continue
    if (n_codelets != -1) & (n > n_codelets):
        sys.exit(0)
    l = l.replace("],", "];")
    tokens = l.split(";")
    t1 = np.array(tokens[0].replace("[", "").replace("]", "").split(","), dtype=int)
    t2 = np.array(tokens[1].replace("[", "").replace("]", "").split(","), dtype=int)
    tokens = tokens[2].split(",")
    count = tokens[0]
    flops = tokens[1]
    codelet_name = f"codelet_{int(n):08d}"
    file_name = f"{codelet_name}.c"
    header_name = f"{codelet_name}.h"
    with open(file_name, "w+") as f:
        sys.stdout = f
        if len(t1) > 2:
            generate_codelet_2d(t1, t2)
        else:
            generate_codelet_1d(t1, t2)
    with open(header_name, "w+") as f:
        sys.stdout = f
        generate_header_file(codelet_name, t1, t2)
    n = n + 1
