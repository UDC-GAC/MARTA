#!/env/python3

import sys

if len(sys.argv) != 5:
    print("Wrong number of arguments")
    sys.exit(1)

main_file = sys.argv[1]
kernel_file = sys.argv[2]
function_name = sys.argv[3]
compiler = sys.argv[4]

label_no = 1000


def new_label():
    global label_no
    new_str = f".L{label_no}"
    label_no += 1
    return new_str


def extract_kernel_icc():
    # TODO:
    global kernel_file
    with open(kernel_file) as kern:
        lines = []
        goto = dict()
        started = False
        for line in kern:
            pass
    return lines


def extract_kernel_gcc():
    global kernel_file
    with open(kernel_file) as kern:
        lines = []
        goto = dict()
        started = False
        for line in kern:
            if ".cfi_startproc" in line:
                started = True
                continue
            if not started:
                continue
            # avoid
            if ".cfi_" in line:
                continue
            # if "ret" in line or "leave" in line:
            if "ret" in line:
                break
            # change label naming, in order to avoid collisions with main file
            if ".L" in line:
                # get .LNUMBER
                label_name = line.split("\t")[-1].strip().replace(":", "")
                if not (label_name in goto):
                    goto[label_name] = new_label()
                if line.startswith(".L"):
                    lines.append(f"{goto[label_name]}:\n")
                else:
                    tmp = line.split("\t")
                    tmp[-1] = goto[label_name]
                    new_line = ""
                    for tok in tmp:
                        new_line += f"\t{tok}"
                    lines.append(f"{new_line}\n")
                continue
            lines.append(line)
    return lines


if compiler == "gcc":
    kernel = extract_kernel_gcc()
else:
    kernel = extract_kernel_icc()

with open(main_file) as main:
    lines = []
    for line in main:
        if ("call" in line) and (function_name in line):
            lines.extend(kernel)
        else:
            lines.append(line)


with open(main_file, "w+") as f:
    f.writelines(lines)
