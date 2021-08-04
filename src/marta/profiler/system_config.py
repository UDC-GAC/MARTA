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

# -*- coding: utf-8 -*-

import pyperf
from pyperf._system import System

from marta.utils.marta_utilities import pwarning, pinfo, CaptureOutput

# We are just interested in these capabilities for the moment.
pyperf._system.OPERATIONS = [
    pyperf._system.CPUFrequency,  # set to maximum frequency
    pyperf._system.CPUGovernorIntelPstate,  # set CPU scaling governor of the intel_pstate driver.
    pyperf._system.TurboBoostIntelPstate,  # Set Turbo Boost mode of Intel CPUs by reading from/writing into /sys/devices/system/cpu/intel_pstate/no_turbo of the intel_pstate driver.
    # pyperf._system.TurboBoostMSR,  # Turbo Boost mode of Intel CPUs using /dev/cpu/N/msr.
]


class PyPerfError(Exception):
    pass


class PyPerfArgs:
    def __init__(self, args):
        for arg in args:
            setattr(self, arg, args[arg])
        if not hasattr(self, "affinity") or type(self.affinity) != list:
            raise PyPerfError


class SystemConfig:
    def tune(self):
        with CaptureOutput() as output:
            self.system.run_operations("tune")
        pinfo(f"{output[0]} using pyperf")

    def check_errors(self, val: str):
        with CaptureOutput() as output:
            self.system.render_messages(val)

        errors = False
        for line in output:
            if "Errors" in line:
                errors = True
                continue
            if (
                "===" in line
                or "" == line
                or not errors
                or "ERROR: At least one operation failed with permission error, retry as root"
                in line
            ):
                continue
            pwarning(line)

    def reset(self):
        with CaptureOutput() as output:
            self.system.run_operations("reset")
        pinfo(f"{output[0]} using pyperf")

    def __init__(self, args):
        self.system = System()
        self.system.init(PyPerfArgs(args))

