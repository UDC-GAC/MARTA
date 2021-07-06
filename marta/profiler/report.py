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

import cpuinfo as cpu
import os
from timing import Timing


class Report:
    cinfo = None

    @staticmethod
    def get_machine_info():
        """
        Get information regarding processor and SO of host machine
        """
        cpu_info = ""
        if Report.cinfo == None:
            Report.cinfo = cpu.get_cpu_info()

        cpu_info += f"CPU:           {Report.cinfo['brand_raw']}\n"
        cpu_info += f"Architecture:  {Report.cinfo['arch_string_raw']}\n"
        cpu_info += f"Avail. Cores:  {cpu.os.cpu_count()}\n"
        cpu_info += f"Host OS:       "
        if cpu.platform.win32_ver()[0] != "":
            cpu_info += f"{cpu.platform.win32_ver()[0]}"
        elif cpu.platform.mac_ver()[0] != "":
            cpu_info += f"{cpu.platform.mac_ver()[0]}"
        else:
            cpu_info += f"kernel {cpu.platform.uname()[2]}"

        return f"{cpu_info}\n"

    @staticmethod
    def generate_report(kernel, verbose=True) -> str:
        """
        Generate custom header for CSV file

        :param params: List of parameters to print in the file
        :type params: list
        :param verbose: If `True`, then outputs machine information
        :type verbose: bool
        :return: A string containing all data as a comment (all lines start with #)
        :rtype: str
        """
        content = f"#" * 80 + "\n"
        content += f"#            MARTA file report: {kernel.kernel}\n"
        content += f"#" * 80 + "\n"
        if verbose:
            content += f"\n# -- MACHINE INFO\n"
            content += Report.get_machine_info()

        content += f"\n# -- TIME ELAPSED : {Timing.to_seconds(Timing.total_time)}\n"
        content += f"\t- Total Compilation time: {Timing.to_seconds(Timing.compilation_time)}\n"
        content += (
            f"\t- Total Execution time: {Timing.to_seconds(Timing.execution_time)}\n"
        )
        content += f"\n# -- EXPERIMENT PARAMETERS\n"
        content += f"- Kernel name: {kernel.kernel}\n"
        content += f"- Description: {kernel.descr}\n"
        content += f"- Compilers used:\n"
        for compiler in kernel.compiler_flags:
            content += f"\t{compiler} -> {kernel.compiler_flags[compiler]}\n"
        content += f"- Kernel configurations: {kernel.kernel_cfg}\n"
        content += f"- FLOPS: {kernel.flops}\n"
        content += f"- Loop iterations: {kernel.nsteps}\n"
        content += f"- Number of repetitions: {kernel.nexec}\n"
        content += f"- CPU affinity (if any): {kernel.cpu_affinity}\n"
        if kernel.papi_counters != None:
            content += f"- Hardware counters used:\n"
            for l in kernel.papi_counters:
                content += f"\t{l}\n"

        # Get compilation flags and so
        content += f"\n# -- COMPILATION (stdout)\n"
        try:
            with open("log/___tmp.stdout") as f:
                for l in f.readlines():
                    content += l
            os.system("rm log/___tmp.stdout")
        except FileNotFoundError:
            content += "stdout was redirected manually.\n"

        # Generate errors
        content += f"\n# -- WARNINGS/ERRORS (stderr)\n"
        try:
            with open("log/___tmp.stderr") as f:
                for l in f.readlines():
                    content += l
            os.system("rm log/___tmp.stderr")
        except FileNotFoundError:
            content += "stderr was redirected manually.\n"

        return content
