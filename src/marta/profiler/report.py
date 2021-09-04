# Copyright (c) Colorado State University. 2019-2021
# Copyright (c) Universidade da Coruña. 2019-2021
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
#
# Author: Marcos Horro <marcos.horro@udc.es>
#
# -*- coding: utf-8 -*-

# Third-party libraries
import cpuinfo as cpu


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
