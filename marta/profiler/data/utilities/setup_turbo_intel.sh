# Copyright 2021 Marcos Horro
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

#!/bin/bash
#set -e

# Based on: https://github.com/travisdowns/uarch-bench/

export VENDOR_ID=$(lscpu | grep 'Vendor ID' | egrep -o '[^ ]*$')
export MODEL_NAME=$(lscpu | grep 'Model name' | sed -n 's/Model name:\s*\(.*\)$/\1/p')
SCALING_DRIVER=$(cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_driver)
SCALING_GOVERNOR=$(cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor)
NO_TURBO_FILE="/sys/devices/system/cpu/intel_pstate/no_turbo"

function check_turbo {
        STATE=$(cat "$NO_TURBO_FILE")
        STATE_STR=$(if [ $STATE -eq 0 ]; then echo "ENABLED"; else echo "DISABLED"; fi)
        echo "Current Turbo state: $STATE ($STATE_STR)"
}

echo "Driver: $SCALING_DRIVER, governor: $SCALING_GOVERNOR" 
echo -e "Vendor ID: $VENDOR_ID\nModel name: $MODEL_NAME"
if [ ${VENDOR_ID}x == "GenuineIntelx" ]; then 
        check_turbo 
        if [ $# -gt 0 ] && [ $1 -ge 1 ]; then
                echo "Disabling Turbo"
                echo 1 > ${NO_TURBO_FILE}
        else
                echo "Enabling Turbo"
                echo 0 > ${NO_TURBO_FILE}
        fi
        check_turbo
fi