import os


def raw_asm_type(ins):
    """[summary]

    Args:
        ins ([type]): [description]

    Returns:
        [type]: [description]
    """
    op_name = ins[0]
    if len(ins) < 2:
        return op_name
    operands = ins[1].strip().split(",")
    if len(operands) != 0:
        op_name += "_"
        for op in operands:
            op = op.strip()
            if ("%zmm" in op) or ("%ymm" in op) or ("%xmm" in op):
                op_name += "r"
            else:
                op_name += "m"
    return op_name


def skip_asm(ins):
    if ins[0][0] == ".":
        return True
    for i in ins:
        if i == "ret" or i == "endbr64":
            return True
    return False


def parse_asm(asm_file):
    raw_inst = {}
    count = False
    for l in open(asm_file, "r"):
        if l[0] == '#' or l == '\n':
            continue
        tok = l.strip().split('#')
        tok = tok[0].strip().split('\t')
        if tok[0] == ".cfi_endproc":
            return raw_inst
        if tok[0] == ".cfi_startproc":
            count = True
            continue
        if not count or skip_asm(tok):
            continue
        raw_asm = raw_asm_type(tok)
        if raw_asm in raw_inst.keys():
            raw_inst[raw_asm] += 1
        else:
            raw_inst[raw_asm] = 1
    return raw_inst
