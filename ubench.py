#!/env/python3

import numpy as np
import pandas as pd
import csv
import itertools as it
import os
import sys
from datetime import datetime as dt

# dependencies:
# python3, pandas, numpy

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


# values of interest
init_val = [0, 1, 3, 7, 15, 16]
#init_val = [0, 1]
tile_size = [1]
tile_size = [1,3,4,8,12,16]
step_size = range(1,6)
#step_size = [1]
nexec = 7 # should be at least 7
nruns = 1000000

# pinning thread to CPU (ugly way tho)
th_pin="OMP_NUM_THREADS=1 GOMP_CPU_AFFINITY=7" # gcc version
#th_pin="OMP_NUM_THREADS=1 KMP_AFFINITY=7" # icc version

# custom flags, e.g. vectorization
CUSTOM_FLAGS="-DPOLYBENCH_USE_C99_PROTO -DPOLYBENCH_USE_RESTRICT -Ofast -ftree-vectorize -march=native " + \
             "-mtune=native -fvect-cost-model=unlimited -fsimd-cost-model=unlimited " +\
             "-mavx2 -ftree-vectorizer-verbose=7 --param min-vect-loop-bound=1"
if (len(sys.argv) > 1):
  CUSTOM_FLAGS = str(sys.argv[1])

# file names
tstamp = dt.now().strftime("%H_%M_%S__%m_%d")
#nfile = "exec_%s.csv" % tstamp 
nfile = "asm_%s.csv" % tstamp 

def acceptable_dev(values):
    norm_val = values/np.max(values)
    print("[DEBUG] std deviation = %f\n" % np.std(norm_val))
    return (np.std(norm_val) < acc_dev)

def raw_asm_type(ins):
    op_name = ins[0]
    if (len(ins)<3):
        return op_name
    operands = ins[1].strip().split(",")
    if len(operands)!=0:
        op_name += "_"
        for op in operands:
            if ("%ymm" in op) or ("%xmm" in op):
                op_name += "r"
            else:
                op_name += "m"
    return op_name

# step 2
def asm_type(ins):
    op = ins[0]
    vec_ins = 0
    if op[-2:]=="pd":
        vec_ins = 1
    if ("vmov" in op[:4]):
        ops = ins[1].strip().split(",")
        if ("%xmm" in ops[0][:4]):
            return "Store",vec_ins
        else:
            return "Load",vec_ins
    if ("vfmadd" in op[:6]):
        return "FMA",vec_ins
    if ("vmul" in op[:4]):
        return "Mul",vec_ins
    if ("vadd" in op[:4]):
        return "Add",vec_ins
    if ("vextract" in op[:8]):
        return "Extract",vec_ins
    if ("vbroadcast" in op[:10]):
        return "Bcast",vec_ins
    if ("vinsert" in op[:7]):
        return "Insert",vec_ins

    return "Unknown",vec_ins

def reading_asm_inst(asm_file):
    # Load,Store,FMA,Mul,Add,Bcast,Insert,Extract,Unknown
    dict_inst = {'Load':0,'Store':0,'FMA':0,'Mul':0,'Add':0,\
            'Bcast':0,'Insert':0,'Extract':0,'Unknown':0, 'Vec':0}
    raw_inst = {}
    count = False
    for l in open(asm_file,'r'):
        tok = l.strip().split("\t")
        if tok[0]=='.cfi_endproc':
            dict_inst.update(raw_inst)
            return dict_inst
        if tok[0]=='.cfi_startproc':
            count = True
            continue
        if len(tok[0])==0: continue
        if tok[0][0]=='.':
            continue
        if count:
            ins_type,vec_ins = asm_type(tok)
            raw_asm = raw_asm_type(tok)
            if ins_type in raw_asm:
                raw_inst[ins] += 1
            else:
                raw_inst[raw_asm] = 1
            dict_inst[ins_type] += 1
            dict_inst['Vec'] += vec_ins
    return values

def check_vect():
    with open("kernel.vec",'r') as f:
        for l in f:
            if ("kernel.c" in l) and ("loop vectorized" in l):
                os.system("rm kernel.vec")
                return True
    os.system("rm kernel.vec")
    return False

def csv_header(params):
  header = ""
  for p in params:
    if (type(p)==list):
      header += "# [ "
      for e in p:
        header += str(e) + " "
      header += "]\n"
    if (type(p)==str):
      header += str("# " + p + '\n')
  return header

def avg_exec(name):
  # executing seven times at least
  os.system("%s ./bin/spmv_%s  > ____tmp_%s" % (th_pin,name,name))
  for tt in range(1,nexec):
    # execute
    os.system("%s ./bin/spmv_%s >> ____tmp_%s" % (th_pin,name,name))
  val = []
  for l in open("____tmp_%s" % name):
    val.append(float(l))
  val.sort()
  with open((name + "_" + nfile),"a+") as f:
    for v in val:
      f.write(str(v)+",")
    f.write("\n")
  avg_val = sum(val[1:-1])/len(val[1:-1])
  # keep it clean
  os.system("rm ____tmp_%s" % name)
  return avg_val

# for debuggin purposes and feedback
niters = pow(len(init_val),2) * pow(len(tile_size),2) * pow(len(step_size),2)
iteration = 0

# Structure for storing results and ploting 
#df = pd.DataFrame(columns=["I","It","Is","J","Jt","Js","FLOPSs","Cycles","Time","Vec"])
df = pd.DataFrame(columns=["I","It","Is","J","Jt","Js","Vec"])

print("Microbenchmarking using a SpMV-like code...")
# microbenchmarking according to values of interest
for uI, uJ in it.product(init_val, init_val):
  for uIt, uJt in it.product(tile_size, tile_size):
    for uIs, uJs in it.product(step_size, step_size):
      print("progress = %d / %d" % (iteration,niters))
      iteration += 1
      # compilation
      ret = os.system("make CUSTOM_FLAGS='%s' NRUNS=%d"\
                          " uI=%d uIt=%d uIs=%d"\
                          " uJ=%d uJt=%d uJs=%d"\
                          % (CUSTOM_FLAGS,nruns,uI,uIt,uIs,uJ,uJt,uJs))
      if (ret != 0):
        print("Error compiling, quiting...")
        exit(0)
      
      raw_asm = reading_asm_inst("asm_codes/kernel_I%d_J%d_It%d_Jt%d_Is%d_Js%d.s" %
              (uI,uJ,uIt,uJt,uIs,uJs))
      vect = check_vect()
#      # Average cycles
#      avg_cycles = avg_exec("cyc")
#      # Average time
#      avg_time = avg_exec("time")
#      # FIXME calculating FLOPS/s ad-hoc for this problem
#      flops = (int(uIt/uIs) * int(uJt/uJs) * 2. * nruns) / avg_time
      d = {'I': int(uI), 'It': int(uIt), 'Is': int(uIs),\
              'J': int(uJ), 'Jt': int(uJt), 'Js': int(uJs), 'Vec':int(vect)}
      d.update(raw_asm)
      df = df.append(d, ignore_index=True)

# storing results with metadata
df = df.fillna(0.0)
df.to_csv(nfile,index=False)

machine_file = "machine_info.txt"
os.system("uname -a > %s" % machine_file)
os.system("lscpu >> %s")

with open(nfile, 'r+') as f:
  content = f.read()
  f.seek(0,0)
  with open(machine_file, 'r') as mf:
      l = mf.readline()
      f.write("# " + str(l))
  f.write(csv_header([["init_vals",init_val],\
        ["tile_size",tile_size], ["step_size", step_size],\
        CUSTOM_FLAGS, th_pin, ["runs and execs:", nruns, nexec]]))
  f.write(content)
