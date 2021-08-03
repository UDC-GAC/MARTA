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

# Standard library
import subprocess
import shutil

# Third-party libraries
import pandas as pd

# Local imports
from marta.utils.marta_utilities import pinfo, get_name_from_dir


class CompilationError(Exception):
    pass


class CompilerAnalysis:
    columns = ["loops_vectorized"]

    def analysis(lines: list) -> pd.DataFrame:
        pass


class GCCAnalysis(CompilerAnalysis):
    def analysis(lines: list) -> pd.DataFrame:
        df = pd.DataFrame(
            [0] * len(CompilerAnalysis.columns), columns=CompilerAnalysis.columns
        )
        vect_already_visited = []
        for line in lines:
            if "polybench" in line or "marta" in line:
                continue
            if "optimized: loop vectorized" in line:
                file = line.split(" ")[0]
                if file in vect_already_visited:
                    continue
                df["loops_vectorized"] += 1

        return df


class ICCAnalysis(CompilerAnalysis):
    def analysis(lines: list) -> pd.DataFrame:
        df = pd.DataFrame(
            [0] * len(CompilerAnalysis.columns), columns=CompilerAnalysis.columns
        )
        active_loop = False
        for line in lines:
            if "polybench" in line or "marta" in line:
                continue
            if "LOOP BEGIN" in line:
                active_loop = True
                continue
            if "LOOP END" in line:
                active_loop = False
                continue
            if active_loop and "LOOP WAS VECTORIZED" in line:
                df["loops_vectorized"] += 1

        return df


def vector_report_analysis(file: str, compiler: str) -> pd.DataFrame:
    with open(file) as f:
        if compiler == "gcc":
            return GCCAnalysis.analysis(f.readlines())
        if compiler == "icc":
            return ICCAnalysis.analysis(f.readlines())
    # clang not supported yet...
    return {}


def compile_file(
    src_file: str, output="", compiler="gcc", flags=["-O3"], temp=False
) -> None:
    """Just compile a C file.

    :param src_file: Source file
    :type src_file: str
    :param output: Output file, defaults to ""
    :type output: str, optional
    :param compiler: Compiler, defaults to "gcc"
    :type compiler: str, optional
    :param flags: List of flags, defaults to ["-O3"]
    :type flags: list, optional
    :param temp: Temporal file, defaults to False
    :type temp: bool, optional
    :raises CompilationError: If compilation does not succeeds
    """
    if output == "":
        output = f"/tmp/a.out"
    input_file = f"{src_file}"
    file_name = get_name_from_dir(input_file)
    if temp:
        input_file = f"/tmp/{file_name}"
        try:
            shutil.copyfile(src_file, input_file)
        except shutil.SameFileError:
            pass
    cmd = [compiler, *flags, input_file, "-o", output]
    cp = subprocess.run(cmd)
    if cp.returncode:
        raise CompilationError


def compile_makefile(
    target: str,
    main_src: str,
    kpath: str,
    compiler: str,
    compiler_flags: str,
    common_flags: str,
    kconfig: str,
    other_flags: list,
    suffix_file="",
    stdout=subprocess.STDOUT,
    stderr=subprocess.STDOUT,
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
            common_flags += f" {t}"
            continue
        if "=" in t:
            kconfig = kconfig.replace(t, "")
            other_flags += f" {t}"

    compiler_flags_suffix = compiler_flags.replace(" ", "_").replace("-", "")

    cmd = [
        "make",
        "-B",
        "-C",
        kpath,
        f"TARGET={target}",
        f"BINARY_NAME={target}",
        f"MAIN_FILE={main_src}",
        f"COMP={compiler}",
        f"COMP_FLAGS={compiler_flags_suffix}",
        f"KERNEL_CONFIG={kconfig}",
        f"COMMON_FLAGS={common_flags}",
        f"SUFFIX_ASM={suffix_file}",
        *other_flags,
    ]

    if type(stdout) != type(subprocess.STDOUT):
        with open(stdout, "a") as fstdout:
            with open(stderr, "a") as fstderr:
                cp = subprocess.run(cmd, stdout=fstdout, stderr=fstderr)
    else:
        cp = subprocess.run(cmd)

    if cp.returncode != 0:
        # returns a 16-bit value:
        # * 8 LSB for the signal
        # * 8 MSB for the code
        exit_code = (int(cp.returncode) >> 8) & 0xFF
        exit_signal = int(cp.returncode) & 0xFF
        pinfo(
            f"'make' exited with code '{str(exit_code)}' (signal '{exit_signal}') while compiling in {kpath}."
        )
    return cp.returncode == 0

