# -*- coding: utf-8 -*-
#!/env/python3

import yaml
import argparse
import numpy as np
import pandas as pd
import csv
import itertools as it
import os
import sys
from datetime import datetime as dt

#############################
#############################
#### MUST READ CAREFULLY ####
#############################
#############################

#############################
# Setup of this experiment:
# * thread pinning trying to be more deterministic
# * DVFS controlled (cpufreq)
# * cache reuse: decide whether hot/cold
# * measure deviation
# * vectorization flags: arguments
#############################


#############################
## parse arguments
##################################################
# parsing arguments
parser = argparse.ArgumentParser(
        description='wrapper for preparing data given a csv')
required_named = parser.add_argument_group('required named arguments')
required_named.add_argument(
        '-i', '--input', help='input file name', required=True)
args = parser.parse_args()

##################################################
# parsing all the arguments from the config.yml
yml_config = args.input
with open(yml_config, 'r') as ymlfile:
    cfg = yaml.load(ymlfile)

# compilation arguments
config_comp = cfg[0]['compilation']
compiler = config_comp['compiler']
kernel = config_comp['kernel']
init_val = config_comp['init_val']
tile_size = config_comp['tile_size']
step_size = config_comp['step_size']
nexec = config_comp['nexec']
nruns = int(config_comp['nruns'])
flops = config_comp['flops']
custom_flags = config_comp['custom_flags']
#custom_flags = "-DPOLYBENCH_USE_C99_PROTO -DPOLYBENCH_USE_RESTRICT -Ofast -ftree-vectorize -march=native " + \
        #        "-mtune=native -fvect-cost-model=unlimited -fsimd-cost-model=unlimited " +\
        #        "-mavx2 -ftree-vectorizer-verbose=7 --param min-vect-loop-bound=1"

# execution arguments
config_exec = cfg[1]['execution']
th_pin = config_exec['th_pin']


def acceptable_dev(values):
    norm_val = values/np.max(values)
    print("[DEBUG] std deviation = %f\n" % np.std(norm_val))
    return (np.std(norm_val) < acc_dev)


def raw_asm_type(ins):
    op_name = ins[0]
    if (len(ins) < 3):
        return op_name
    operands = ins[1].strip().split(",")
    if len(operands) != 0:
        op_name += "_"
        for op in operands:
            if ("%ymm" in op) or ("%xmm" in op):
                op_name += "r"
            else:
                op_name += "m"
    return op_name


def reading_asm_inst(asm_file):
    raw_inst = {}
    count = False
    for l in open(asm_file, 'r'):
        if "#"==l[0]:
            continue
        tok = l.strip().split("\t")
        if tok[0] == '.cfi_endproc':
            return raw_inst
        if tok[0] == '.cfi_startproc':
            count = True
            continue
        if len(tok[0]) == 0:
            continue
        if tok[0][0] == '.':
            continue
        if count:
            raw_asm = raw_asm_type(tok)
            if raw_asm in raw_inst:
                raw_inst[raw_asm] += 1
            else:
                raw_inst[raw_asm] = 1
    return raw_inst


def check_vect(code):
    with open(code + ".vec", 'r') as f:
        for l in f:
            if (code + ".c" in l) and ("loop vectorized" in l):
                os.system("rm " + code + ".vec")
                return True
    os.system("rm " + code + ".vec")
    return False


def csv_header(params):
    machine_file = "___tmp__machine_info.txt"
    os.system("uname -a > %s" % machine_file)
    os.system("lscpu >> %s" % machine_file)
    header = ""
    with open(machine_file, 'r') as mf:
        for l in mf:
            header += str("# " + l)
    os.system("rm %s" % machine_file)
    for p in params:
        if type(p) == dict:
            for k, v in p.items():
                header += str("# " + str(k) + ": " + str(v) + "\n")
        else:
            header += str("# " + str(p) + "\n")
    return header


def avg_exec(code, name):
    # executing seven times at least
    os.system("%s ./bin/%s_%s.o  > ____tmp_%s" % (th_pin, code, name, name))
    for tt in range(1, nexec):
        # execute
        os.system("%s ./bin/%s_%s.o >> ____tmp_%s" % (th_pin, code, name, name))
    val = []
    for l in open("____tmp_%s" % name):
        val.append(float(l))
    val.sort()
    with open((name + "_" + code), "a+") as f:
        for v in val:
            f.write(str(v)+",")
        f.write("\n")
    avg_val = sum(val[1:-1])/len(val[1:-1])
    # keep it clean
    os.system("rm ____tmp_%s" % name)
    return avg_val


# for debuggin purposes and feedback
niters = pow(len(init_val), 2) * pow(len(tile_size), 2) * pow(len(step_size), 2)

# main loop
for code in kernel:
    iteration = 0
    basename = code.split(".c")[0]
    # file names
    tstamp = dt.now().strftime("%H_%M_%S__%m_%d")
    fullfile = "full_%s_asm_%s.csv" % (basename,tstamp)

    # Structure for storing results and ploting
    df = pd.DataFrame(columns=["I", "It", "Is", "J", "Jt",
        "Js", "FLOPSs", "Cycles", "Time", "Vec"])

    print("Microbenchmarking for " + code + " code...")
    # microbenchmarking according to values of interest
    for uI, uJ in it.product(init_val, init_val):
        for uIt, uJt in it.product(tile_size, tile_size):
            for uIs, uJs in it.product(step_size, step_size):
                print("progress = %d / %d" % (iteration, niters))
                iteration += 1
                # compilation
                ret = os.system("make CUSTOM_FLAGS='%s' NRUNS=%d"
                        " uI=%d uIt=%d uIs=%d"
                        " uJ=%d uJt=%d uJs=%d"
                        % (custom_flags, nruns, uI, uIt, uIs, uJ, uJt, uJs))
                if (ret != 0):
                    print("Error compiling %s, quiting..." % (code))
                    exit(0)
                raw_asm = reading_asm_inst("asm_codes/%s_I%d_J%d_It%d_Jt%d_Is%d_Js%d.s" %
                        (basename, uI, uJ, uIt, uJt, uIs, uJs))
                vect = check_vect(basename)
                # Average cycles
                # avg_cycles = avg_exec(basename, "cyc")
                avg_cycles = 0.0
                # Average time
                avg_time = avg_exec(basename, "time")
                flops = (int(uIt/uIs) * int(uJt/uJs) * float(flops) * nruns) / avg_time
                d = {'I': int(uI), 'It': int(uIt), 'Is': int(uIs),
                        'J': int(uJ), 'Jt': int(uJt), 'Js': int(uJs), 'FLOPSs': flops,
                        'Cycles': avg_cycles, 'Time': avg_time, 'Vec': vect}
                d.update(raw_asm)
                df = df.append(d, ignore_index=True)

    # storing results with metadata
    df = df.fillna(0.0)
    df.to_csv(fullfile, index=False)

    # saving all data
    with open(fullfile, 'r+') as f:
        content = f.read()
        f.seek(0, 0)
        f.write(csv_header([["init_vals", init_val],
            ["tile_size", tile_size], ["step_size", step_size],
            custom_flags, th_pin, ["runs and execs:", nruns, nexec]]))
        f.write(content)
