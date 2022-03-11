# Copyright 2022 Marcos Horro
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

template_4_fuse_orphan = """
- kernel:
      name: "matrices"
      type: "regular"
      path: "src/"
      preamble:
          command: "sudo cpupower frequency-set -u 2.1GHz  > /dev/null && sudo cpupower frequency-set -d 2.1GHz > /dev/null"
      compilation:
          enabled: True
          processes: 16
          language: "C"
          compiler_flags:
              { "gcc-11": [" -Ofast -march=native -mtune=native -mavx2 "] }
          main_src: "main_big.c"
          kernel_inlined: False
          asm_analysis:
              syntax: "att"
              count_ins: False
              static_analysis: False
              llvm_mca_bin: llvm-mca
          debug: False
      configuration:
          macveth: True
          d_features:
              N:
                  type: "static"
                  value: "[33554432]"
              MATRIX:
                  type: "static"
                  path: True
                  #value: 'glob.glob("[PATH]thesis/matrices1M/*.poly.c")'
                  value: '["[PATH]thesis/matrices1M/#NAME#-d1.poly.c"]'
          macveth_target: "MATRIX"
          macveth_flags:
              [
                  "-misa=avx2",
                  "--march=cascadelake",
                  "--simd-cost-model=unlimited",
                  "--min-redux-size=4",
                  "--redux-win-size=-1",
                  "--no-format",
              ]
          flops: "1"
      execution:
          enabled: True
          papi_counters: [
                  "UNHALTED_CORE_CYCLES",
                  "INSTRUCTIONS_RETIRED",
                  "UOPS_EXECUTED:THREAD",
                  "UOPS_ISSUED:ALL",
                  "UOPS_RETIRED:ALL",
                  "FP_ARITH:SCALAR_SINGLE",
                  "FP_ARITH:128B_PACKED_SINGLE",
                  "FP_ARITH:256B_PACKED_SINGLE",
                  "L1D:REPLACEMENT", # "PAPI_L1_DCM", # L1D:REPLACEMENT
                  "L2_RQSTS:ALL_CODE_RD", # "PAPI_L1_ICM", # L2_RQSTS:ALL_CODE_RD
                  "LLC_REFERENCES", #~"PAPI_L2_TCM", # LLC_REFERENCES
                  "LLC_MISSES", #"PAPI_L3_TCM", # LLC_MISSES
              ]
          tsc: True
          threshold_outliers: 5 # in percentage
          discard_outliers: True # remove outliers from average
          compute_avg: True # divide values by nsteps
          nexec: 20
          nsteps: 1
          cpu_affinity: 10
          check_dump: False
          prefix: "numactl -p 0 taskset -c 10"
      output:
          name: "#NAME#_4redux_orphan_fuse"
          format: "csv" # csv, html, json
          columns: "all"
          report: False
          verbose: True
"""

template_4_fuse_noorphan = """
- kernel:
      name: "matrices"
      type: "regular"
      path: "src/"
      preamble:
          command: "sudo cpupower frequency-set -u 2.1GHz  > /dev/null && sudo cpupower frequency-set -d 2.1GHz > /dev/null"
      compilation:
          enabled: True
          processes: 16
          language: "C"
          compiler_flags:
              { "gcc-11": [" -Ofast -march=native -mtune=native -mavx2 "] }
          main_src: "main_big.c"
          kernel_inlined: False
          asm_analysis:
              syntax: "att"
              count_ins: False
              static_analysis: False
              llvm_mca_bin: llvm-mca
          debug: False
      configuration:
          macveth: True
          d_features:
              N:
                  type: "static"
                  value: "[33554432]"
              MATRIX:
                  type: "static"
                  path: True
                  #value: 'glob.glob("[PATH]thesis/matrices1M/*.poly.c")'
                  value: '["[PATH]thesis/matrices1M/#NAME#-d1.poly.c"]'
          macveth_target: "MATRIX"
          macveth_flags:
              [
                  "-misa=avx2",
                  "--march=cascadelake",
                  "--simd-cost-model=unlimited",
                  "--min-redux-size=4",
                  "--redux-win-size=-1",
                  "--novec-orphan-redux",
                  "--no-format",
              ]
          flops: "1"
      execution:
          enabled: True
          papi_counters: [
                  "UNHALTED_CORE_CYCLES",
                  "INSTRUCTIONS_RETIRED",
                  "UOPS_EXECUTED:THREAD",
                  "UOPS_ISSUED:ALL",
                  "UOPS_RETIRED:ALL",
                  "FP_ARITH:SCALAR_SINGLE",
                  "FP_ARITH:128B_PACKED_SINGLE",
                  "FP_ARITH:256B_PACKED_SINGLE",
                  "L1D:REPLACEMENT", # "PAPI_L1_DCM", # L1D:REPLACEMENT
                  "L2_RQSTS:ALL_CODE_RD", # "PAPI_L1_ICM", # L2_RQSTS:ALL_CODE_RD
                  "LLC_REFERENCES", #~"PAPI_L2_TCM", # LLC_REFERENCES
                  "LLC_MISSES", #"PAPI_L3_TCM", # LLC_MISSES
              ]
          tsc: True
          threshold_outliers: 5 # in percentage
          discard_outliers: True # remove outliers from average
          compute_avg: True # divide values by nsteps
          nexec: 20
          nsteps: 1
          cpu_affinity: 10
          check_dump: False
          prefix: "numactl -p 0 taskset -c 10"
      output:
          name: "#NAME#_4redux_orphan_fuse"
          format: "csv" # csv, html, json
          columns: "all"
          report: False
          verbose: True
"""

import sys

name = sys.argv[1]

template_4_fuse_orphan = template_4_fuse_orphan.replace("#NAME#", name)
template_4_fuse_noorphan = template_4_fuse_noorphan.replace("#NAME#", name)

with open(f"{name}_4redux_orphan_fuse.yml", "w") as f:
    f.writelines(template_4_fuse_orphan)

with open(f"{name}_4redux_noorphan_fuse.yml", "w") as f:
    f.writelines(template_4_fuse_noorphan)
