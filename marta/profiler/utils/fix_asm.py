from asm_analyzer import ASMParser as asm
import pandas as pd


def get_asm_file(y, A, x, isa, comp):
    return f"asm_codes/micro_codelet_codelet_00000000_ORIG_y{y}_ORIG_A{A}_ORIG_x{x}_{isa}_{comp}.s"


max_orig = 4
cols = ["ORIG_y", "ORIG_A", "ORIG_x", "CFG", "compiler"]
df = pd.DataFrame(columns=cols)
for y in range(max_orig):
    for A in range(max_orig):
        for x in range(max_orig):
            for isa in ["msse4.2", "mavx2", "mavx512f"]:
                for comp in ["gcc", "icc"]:
                    d = asm.parse_asm(get_asm_file(y, A, x, isa, comp))
                    vals = dict(zip(cols, [y, A, x, isa, comp]))
                    d.update(vals)
                    df = df.append(d, ignore_index=True)
df = df.fillna(0.0)
df.to_csv("tmp.csv")
