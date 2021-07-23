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

import subprocess
from marta.utils.marta_utilities import pinfo


def compile_makefile(
    kpath: str,
    comp: str,
    compiler_flags: str,
    common_flags: str,
    kconfig: str,
    other_flags="",
    suffix_file="",
    debug="",
) -> bool:
    """
        Compile benchmark according to a set of flags, suffixes and so

        :param common_flags: Flags which are common for all versions
        :type common_flags: str
        :param custom_flags: Flags which are target-dependent
        :type custom_flags: str
        :param suffix_file: Suffix
        :type suffix_file: str
        :param debug: Suffix for execution command in order to redirect output if any
        :type debug: str
        :return: Dictionary of ASM occurrences
        :rtype: dict
        """

    # Check if options in kernel config string:
    tok = kconfig.split(" ")
    for t in tok:
        if "-D" in t:
            kconfig = kconfig.replace(t, "")
            common_flags += f" {t} "
            continue
        if "=" in t:
            kconfig = kconfig.replace(t, "")
            other_flags += f" {t} "

    compiler_flags_suffix = compiler_flags.replace(" ", "_").replace("-", "")

    cmd = [
        "make",
        "-B",
        f"-C {kpath}",
        f"COMP={comp}",
        f"COMP_FLAGS={compiler_flags_suffix}",
        f"KERNEL_CONFIG='{kconfig}'",
        f"COMMON_FLAGS='{common_flags}'",
        f"SUFFIX_ASM='{suffix_file}'",
        f"{other_flags}",
        f"{debug}",
    ]
    ret = subprocess.call(cmd)

    if ret != 0:
        # returns a 16-bit value:
        # * 8 LSB for the signal
        # * 8 MSB for the code
        exit_code = (int(ret) >> 8) & 0xFF
        exit_signal = int(ret) & 0xFF
        pinfo(
            f"'make' exited with code '{str(exit_code)}' (signal '{exit_signal}') while compiling in {kpath}."
        )
    return ret == 0

