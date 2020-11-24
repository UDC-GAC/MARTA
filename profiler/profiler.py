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
import copy
from datetime import datetime as dt
from math import ceil
from tqdm import tqdm

#############################
# Setup of this experiment:
# * thread pinning trying to be more deterministic
# * DVFS controlled (cpufreq)
# * cache reuse: decide whether hot/cold
# * measure deviation
# * vectorization flags: arguments
#############################

debug = False


def dprint(d, msg):
    if (not d):
        return
    print(msg)


def raw_asm_type(ins):
    op_name = ins[0]
    if (len(ins) < 3):
        return op_name
    operands = ins[1].strip().split(",")
    if len(operands) != 0:
        op_name += "_"
        for op in operands:
            if ("%zmm" in op) or ("%ymm" in op) or ("%xmm" in op):
                op_name += "r"
            else:
                op_name += "m"
    return op_name


def parse_asm(asm_file):
    raw_inst = {}
    count = False
    for l in open(asm_file, 'r'):
        if "#" == l[0]:
            continue
        tok = l.strip().split("\t")
        if len(tok[0]) == 0 or tok[0][0] == '.':
            continue
        if tok[0] == '.cfi_endproc':
            return raw_inst
        if tok[0] == '.cfi_startproc':
            count = True
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
    os.system(f"uname -a > {machine_file}")
    os.system(f"lscpu >> {machine_file}")
    header = ""
    with open(machine_file, 'r') as mf:
        for l in mf:
            header += f"# {l}"
    os.system(f"rm {machine_file}")
    for p in params:
        if type(p) == dict:
            for k, v in p.items():
                header += f"# {str(k)}: {str(v)}\n"
        else:
            header += f"# {str(p)}\n"
    return header


def avg_exec(code, name):
    # executing seven times at least
    try:
        os.mkdir("tmp")
    except FileExistsError:
        os.system("rm tmp/*")
    os.system(f"{th_pin} ./bin/{code}_{name}.o  > tmp/____tmp_{name}")
    for tt in range(1, nexec):
        # execute
        os.system(f"{th_pin} ./bin/{code}_{name}.o  >> tmp/____tmp_{name}")
    val = []
    for l in open(f"tmp/____tmp_{name}"):
        val.append(float(l))
    val.sort()
    with open((f"{name}_{code}"), "a+") as f:
        for v in val:
            f.write(f"{str(v)},")
        f.write("\n")
    avg_val = sum(val[1:-1])/len(val[1:-1])
    # keep it clean
    os.system(f"rm -Rf tmp")
    return avg_val


if __name__ == "__main__":
    #############################
    # parsing CLI arguments
    #############################
    parser = argparse.ArgumentParser(
        description='wrapper for preparing data given a csv')
    required_named = parser.add_argument_group('required named arguments')
    required_named.add_argument(
        '-i', '--input', help='input file name', required=True)
    required_named.add_argument(
        '-d', '--debug', action='store_true', help='debug verbose', required=False)
    args = parser.parse_args()

    #############################
    # parsing all the arguments from the config.yml
    #############################
    try:
        from yaml import CLoader as Loader
    except ImportError:
        from yaml import Loader

    yml_config = args.input
    debug = args.debug
    with open(yml_config, 'r') as ymlfile:
        kernel_configs = yaml.load(ymlfile, Loader=Loader)

    #############################
    # init folders
    #############################
    os.system("mkdir -p asm_codes")
    os.system("mkdir -p bin")

    tmp_files = ""

    #############################
    # main loop
    #############################
    for cfg in kernel_configs:
        # compilation arguments
        kernel = cfg['kernel']['name']
        target_file = cfg['kernel']['target']
        descr = cfg['kernel']['descr']
        path_kernel = cfg['kernel']['path']
        config_comp = cfg['kernel']['compilation']
        compiler = config_comp['compiler']
        kernel_cfg = config_comp['kernel_cfg']
        output_cols = config_comp['output_cols']
        feat = config_comp['features']
        nexec = config_comp['nexec']
        nruns = int(config_comp['nruns'])
        flops = config_comp['flops']
        common_flags = config_comp['common_flags']
        debug_comp = config_comp['debug']
        macveth = config_comp['macveth']
        is_silent = config_comp['silent']

        # execution arguments
        config_exec = cfg['kernel']['execution']
        th_pin = config_exec['th_pin']
        basename = target_file.split(".c")[0]

        # file names
        tstamp = dt.now().strftime("%H_%M_%S__%m_%d")
        fullfile = f"full_{basename}_asm_{tstamp}.csv"

        params_name = list()
        params_values = list()
        for f in feat.keys():
            if type(feat[f]) is str:
                try:
                    tmp_eval = eval(feat[f])
                except NameError:
                    print(
                        f"Evaluation of expression for feature {f} went wrong!")
                    exit(1)
                tmp_eval_copy = copy.deepcopy(tmp_eval)
                for t in tmp_eval_copy:
                    size = len(t)
                    break
                for i in range(size):
                    params_name += [f"{f}{str(i)}"]
                params_values += [tmp_eval]
            else:
                params_name += [f]
                params_values += [feat[f]]

        if output_cols == "all":
            output_cols = params_name.copy()
        if type(output_cols) is not list:
            print("output_cols parameter must be a list")
            exit(1)
        output_cols += ["FLOPSs", "Cycles", "Time", "CFG"]

        # Structure for storing results and ploting
        df = pd.DataFrame(columns=output_cols)

        params_values_copy = copy.deepcopy(params_values)
        niterations = len(list(*params_values_copy))

        print("Microbenchmarking for " + kernel + " code...")
        # microbenchmarking according to values of interest
        with tqdm(total=niterations) as pbar:
            for kconfig in kernel_cfg:
                for params in it.product(*params_values):
                    pbar.update(1)
                    try:
                        params = list(*params)
                    except Exception:
                        pass
                    n = 0
                    tmp_dict = {}
                    custom_params = ""
                    suffix_file = ""
                    for p in params:
                        tmp_dict[params_name[n]] = p
                        custom_params += f" -D{params_name[n]}={p}"
                        suffix_file += f"-{params_name[n]}{p}"
                        flops = flops.replace(params_name[n], str(p))
                        n = n + 1
                    common_flags += custom_params
                    silent = ""
                    if is_silent:
                        silent = " > /dev/null 2> /dev/null"
                    # compilation
                    ret = os.system(
                        f"make -C {path_kernel} COMP={compiler}"
                        f" COMMON_FLAGS='{common_flags}'"
                        f" SUFFIX_ASM='{suffix_file}'"
                        f" NRUNS={nruns} {silent}")
                    if (ret != 0):
                        print(f"Error compiling in {path_kernel}, quiting...")
                        exit(1)
                    tmp_dict.update(parse_asm(f"asm_codes/{basename}_{suffix_file}.s"
                                              ))
                    # Average cycles
                    avg_cycles = avg_exec(basename, "cyc")
                    # Average time
                    avg_time = avg_exec(basename, "time")
                    # FLOPS formula
                    try:
                        flops_eval = eval(flops)
                    except NameError:
                        print("FLOPS formula is not valid; please review it!")
                        exit(1)
                    flopss = (flops_eval * nruns) / avg_time
                    tmp_dict.update({'FLOPSs': flopss,
                                     'Cycles': avg_cycles, 'Time': avg_time,
                                     'CFG': kconfig})
                    # Apending results
                    df = df.append(tmp_dict, ignore_index=True)

                # storing results with metadata
                df = df.fillna(0.0)
                df.to_csv(fullfile, index=False)

                # saving all data to file
                with open(fullfile, 'r+') as f:
                    content = f.read()
                    f.seek(0, 0)
                    f.write(csv_header([
                        common_flags, th_pin, ["runs and execs:", nruns, nexec]]))
                    f.write(content)

    # Clean director1y
    if (tmp_files != ""):
        os.system(f"rm {tmp_files}")
