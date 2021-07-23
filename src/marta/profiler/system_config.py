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

import pyperf

pyperf._system.OPERATIONS = [
    # pyperf._system.PerfEvent,
    # pyperf._system.ASLR,
    # pyperf._system.LinuxScheduler,
    pyperf._system.CPUFrequency,
    pyperf._system.CPUGovernorIntelPstate,
    pyperf._system.TurboBoostIntelPstate,
    # pyperf._system.CheckNOHZFullIntelPstate,
    pyperf._system.TurboBoostMSR,
]


class PyPerfArgs:
    def __init__(self, args):
        for arg in args:
            setattr(self, arg, args[arg])


class SystemConfig:
    def tune(self):
        self.system.run_operations("tune")

    def check_errors(self, val: str):
        self.system.render_messages(val)

    def reset(self):
        self.system.run_operations("reset")

    def __init__(self, args):
        self.system = pyperf._system.System()
        self.system.init(PyPerfArgs(args))

