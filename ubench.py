#!/env/python3

import numpy as np
import pandas as pd
import csv
import matplotlib.pyplot as plt
import itertools as it
import os
import seaborn as sns
import sys

# values of interest
init_val = [0, 1, 3, 7]
#init_val = [0]
tile_size = range(2,5,2)
step_size = range(1,3)
nexec = 7 # should be at least 7
nruns = 1000000

# custom flags, e.g. vectorization
CUSTOM_FLAGS=""
if (len(sys.argv) > 1):
  CUSTOM_FLAGS += " " + str(sys.argv[1])

def avg_exec(name):
  # executing seven times at least
  os.system("./bin/spmv_%s  > ____tmp_%s" % (name,name))
  for tt in range(1,nexec):
    # execute
    os.system("./bin/spmv_%s >> ____tmp_%s" % (name,name))
  val = []
  for l in open("____tmp_%s" % name):
    val.append(float(l))
  val.sort()
  avg_val = sum(val[1:-1])/len(val[1:-1])
  # keep it clean
  os.system("rm ____tmp_%s" % name)
  return avg_val

# for debuggin purposes and feedback
niters = pow(len(init_val),2) * pow(len(tile_size),2) * pow(len(step_size),2)
iteration = 0

# Structure for storing results and ploting 
df = pd.DataFrame(columns=["I","It","Is","J","Jt","Js","FLOPSs","Cycles","Time"])

print("Microbenchmarking using a SpMV-like code...")
# microbenchmarking according to values of interest

for uI, uJ in it.product(init_val, init_val):
  for uIt, uJt in it.product(tile_size, tile_size):
    for uIs, uJs in it.product(step_size, step_size):
      print("progress = %d / %d" % (iteration,niters))
      iteration += 1
      # compilation
      ret = os.system("make CUSTOM_FLAGS=%s NRUNS=%d"\
                          " uI=%d uIt=%d uIs=%d"\
                          " uJ=%d uJt=%d uJs=%d"\
                          % (CUSTOM_FLAGS,nruns,uI,uIt,uIs,uJ,uJt,uJs))
      if (ret != 0):
        print("Error compiling, quiting...")
        exit(0)
      # Average cycles
      avg_cycles = avg_exec("cyc")
      # Average time
      avg_time = avg_exec("time")
      # FIXME calculating FLOPS/s ad-hoc for this problem
      flops = uIt * uJt * 2 * nruns / avg_time
      df = df.append({'I': uI, 'It': uIt, 'Is': uIs,\
                  'J': uJ, 'Jt': uJt, 'Js': uJs,\
                  'FLOPSs': flops, 'Cycles': avg_cycles, 'Time': avg_time}, ignore_index=True)

# ploting dataframe according to different features
sns.set()

# Heatmap regarding tiling size
t = df[["It","Jt","FLOPSs"]].pivot("It","Jt","FLOPSs")
sns.heatmap(t)
