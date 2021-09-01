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

# Standard library
import subprocess
import shutil
from typing import Union, Any, Tuple

# Local imports
from marta.utils.marta_utilities import pinfo, get_name_from_dir, perror


class CompilationError(Exception):
    pass


class CompilerAnalysis:
    columns = ["loops_vectorized", "loop_interchange"]

    def analysis(lines: list) -> dict:
        pass


class GCCAnalysis(CompilerAnalysis):
    def analysis(lines: list) -> dict:
        d = dict(zip(CompilerAnalysis.columns, [0] * len(CompilerAnalysis.columns)))

        vect_already_visited = []
        loop_interchange_visited = []
        for line in lines:
            if "polybench" in line or "marta" in line:
                continue
            file = line.split(" ")[0]
            if "optimized: loop vectorized" in line:
                if file in vect_already_visited:
                    continue
                d["loops_vectorized"] += 1
                vect_already_visited.append(file)
            if "optimized: loops interchanged in loop nest" in line:
                if file in loop_interchange_visited:
                    continue
                d["loop_interchange"] += 1
                loop_interchange_visited.append(file)

        return d


class ICCAnalysis(CompilerAnalysis):
    def analysis(lines: list) -> dict:
        d = dict(zip(CompilerAnalysis.columns, [0] * len(CompilerAnalysis.columns)))
        active_loop = False
        current_loop = ""
        already_visited = []
        for line in lines:
            if "polybench" in line or "marta" in line:
                continue
            pos = line.split("at ")[-1].strip().split(" ")[0].strip()
            if "LOOP BEGIN" in line and not (pos in already_visited):
                active_loop = True
                current_loop = pos
                continue
            if "LOOP END" in line and active_loop:
                active_loop = False
                already_visited.append(current_loop)
                continue
            if active_loop and "LOOP WAS VECTORIZED" in line:
                d["loops_vectorized"] += 1
            if active_loop and "Loopnest Interchanged" in line:
                d["loop_interchange"] += 1

        return d


def vector_report_analysis(file: str, compiler: str) -> dict:
    with open(file) as f:
        if compiler == "gcc" or compiler.startswith("gcc"):
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


def get_asm_name(params: Union[dict, Any]) -> str:
    if not type(params) is dict:
        return ""
    # Parsing parameters
    for pname in params.keys():
        try:
            param_val_parsed = int(params[pname])
        except ValueError:
            # NOTE: for includes or other paths, \"string\" notation is
            # needed, but this is not MARTA's responsibility.
            param_val_parsed = '"' + params[pname] + '"'
        # FIXME:
        if pname == "ASM_NAME":
            return f" {pname}={param_val_parsed}"
    return ""


def get_dict_from_d_flags(params: str) -> dict:
    d = {}
    for tok in params.strip().split(" "):
        tmp = tok.split("=")
        key = tmp[0].replace("-D", "")
        if len(tmp) == 1:
            value = 1
        else:
            value = tmp[1]
        d.update({key: value})
    return d


def get_suffix_and_flags(kconfig: str, params: Union[dict, str]) -> Tuple[str, str]:
    # FIXME: to redo at some point...
    custom_flags = ""
    suffix_file = ""
    custom_bin_name = None
    # Parsing parameters
    if type(params) is dict:
        for pname in params.keys():
            try:
                param_val_parsed = int(params[pname])
            except ValueError:
                # NOTE: for includes or other paths, \"string\" notation is
                # needed, but this is not MARTA's responsibility.
                param_val_parsed = '"' + params[pname] + '"'
            except TypeError:
                perror(f"Something went wrong when parsing files: {params[pname]}")
            if pname != "ASM_NAME":
                custom_flags += f" -D{pname}={param_val_parsed}"
            if pname == "BIN_NAME":
                custom_bin_name = params[pname]
            key = pname.replace("/", "_")
            val = (
                params[pname].replace("/", "_")
                if type(params[pname]) == str
                else params[pname]
            )
            suffix_file += f"_{key}{val}"
        suffix_file = suffix_file.replace("/", "").replace(".c", "")
    else:
        custom_flags = params
        for p in params.strip().replace("-", "").replace("D", "").split(" "):
            suffix_file += f"_{p}"

    # Parsing kconfig
    for kparam in kconfig.strip().replace("-", "").split(" "):
        if "BIN_NAME" in kparam:
            custom_bin_name = kparam.split("=")[1]
            continue
        suffix_file += f"_{kparam}"

    # Avoid very long names
    if custom_bin_name != None:
        suffix_file = custom_bin_name
    if len(suffix_file) > 256:
        perror(
            "Error: too long binary name. Try '-DBIN_NAME=<suffix>' for each compilation case instead"
        )
    return suffix_file, custom_flags

