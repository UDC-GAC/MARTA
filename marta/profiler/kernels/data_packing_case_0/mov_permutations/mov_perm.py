from itertools import permutations as perm
import numpy as np
import pandas as pd

insts = np.array(
    [
        "\tvmovq	xmm0, QWORD PTR [rdi]\n",
        "\tvmovq	xmm1, QWORD PTR [rdx]\n",
        "\tvmovhps	xmm2, xmm0, QWORD PTR [rdi+168]\n",
        "\tvmovq	xmm0, QWORD PTR [rsi]\n",
        "\tvmovhps	xmm1, xmm1, QWORD PTR [rdx+168]\n",
        "\tvmovhps	xmm0, xmm0, QWORD PTR [rsi+168]\n",
    ]
)

prolog = (
    '\t.file	"data_packing_case_0.c"\n'
    + "\t.intel_syntax noprefix\n"
    + "\t.text\n"
    + "\t.p2align 4\n"
    + "\t.globl	data_packing_case_0\n"
    + "\t.type	data_packing_case_0, @function\n"
    + "data_packing_case_0:\n"
    + ".LFB5277:\n"
    + "\t.cfi_startproc\n"
)

# FIXME: interchanged vfmadds, mov changed to XMM1, instead of XMM0
epilog = (
    "\tvfmadd132ps	xmm0, xmm1, xmm2\n"
    + "\tvfmadd231ps	xmm1, xmm2, xmm0\n"
    + "\tvmovlps	QWORD PTR [rdx], xmm1\n"
    + "\tvmovhps	QWORD PTR [rdx+168], xmm1\n"
    + "\tret\n"
    + "\t.cfi_endproc\n"
    + ".LFE5277:\n"
    + "\t.size	data_packing_case_0, .-data_packing_case_0\n"
    + '\t.ident	"GCC: (GNU) 9.3.0"\n'
    + '\t.section	.note.GNU-stack,"",@progbits\n'
)

import sys

no_prog_epilog = False
if len(sys.argv) > 1 and sys.argv[1] == "no_prolog_epilog":
    no_prog_epilog = True

perm_number = 0
csv_file = "csv_perms.csv"
df = pd.DataFrame(columns=["perm", "asm"])
for x in perm(np.arange(6)):
    file_name = f"perm_{perm_number}.s"
    asm_code = insts.take(x)
    d = {"perm": file_name, "asm": asm_code}
    df = df.append(d, ignore_index=True)
    with open(file_name, "w") as f:
        if not no_prog_epilog:
            f.write(prolog)
        f.writelines(asm_code)
        if not no_prog_epilog:
            f.write(epilog)
    perm_number += 1

df.to_csv(csv_file)