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

# Third-party libraries
import pyperf
from pyperf._system import System

# Local imports
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
    warning_no_ops = "pyperf does not allow any operations in this host machine..."

    def tune(self):
        if self.disabled:
            pwarning(SystemConfig.warning_no_ops)
            return
        with CaptureOutput() as output:
            self.system.run_operations("tune")
        pinfo(f"{output[0]} using pyperf")

    def check_errors(self, val: str):
        if self.disabled:
            pwarning(SystemConfig.warning_no_ops)
            return
        with CaptureOutput() as output:
            self.system.render_messages(val)

        errors = False
        n_errors = 0
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
            n_errors += 1
        if n_errors:
            pwarning(
                "Something went wrong when setting frequency and turbo. Check permissions."
            )

    def reset(self):
        if self.disabled:
            pwarning(SystemConfig.warning_no_ops)
            return
        with CaptureOutput() as output:
            self.system.run_operations("reset")
        pinfo(f"{output[0]} using pyperf")

    def is_disabled(self):
        assert hasattr(self, "disabled")
        return self.disabled

    def __init__(self, args):
        self.system = System()
        try:
            self.system.init(PyPerfArgs(args))
            self.disabled = False
        except SystemExit:
            self.disabled = True

