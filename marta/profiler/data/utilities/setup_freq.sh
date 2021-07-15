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
set -e

export VENDOR_ID=$(lscpu | grep 'Vendor ID' | egrep -o '[^ ]*$')
export MODEL_NAME=$(lscpu | grep 'Model name' | sed -n 's/Model name:\s*\(.*\)$/\1/p')
SCALING_DRIVER=$(cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_driver)
SCALING_GOVERNOR=$(cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor)

echo "Driver: $SCALING_DRIVER, governor: $SCALING_GOVERNOR" 
echo -e "Vendor ID: $VENDOR_ID\nModel name: $MODEL_NAME"
if [[ -n "$SCALING_GOVERNOR" ]] && [[ "$SCALING_GOVERNOR" != "performance" ]]; then
        original_governor=$SCALING_GOVERNOR
        echo -n "Changing scaling_governor to 'performance': "
        if ! sudo -n true 2>/dev/null; then echo ""; fi # write a newline if we are about to prompt for sudo
        sudo sh -c "echo performance > /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor"
        if [[ $(cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor) == "performance" ]]; then
                echo "SUCCESS";
        else
                echo "FAILED";
        fi
fi