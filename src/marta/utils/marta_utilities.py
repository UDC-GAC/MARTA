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

# Standard libraries
import sys
import os
import shutil
import filecmp
from io import StringIO
from typing import List

# Third-party libraries
from colorama import Fore, Style

# Local imports
from marta import get_data


def colored(msg: str, color=Fore.RED, style=Style.NORMAL) -> str:
    return f"{color}{style}{msg}{Fore.RESET}{Style.RESET_ALL}"


def perror(msg: str, CODE=1, exit_on_error=True) -> None:
    colored_msg = colored(f"[ERROR] {msg}", Fore.RED, Style.BRIGHT)
    print(f"{colored_msg}")
    if exit_on_error:
        sys.exit(CODE)


def pwarning(msg: str) -> None:
    colored_msg = colored(f"[WARNING] {msg}", Fore.YELLOW, Style.BRIGHT)
    print(f"{colored_msg}")


def pexcept(msg: str, exception: Exception) -> None:
    colored_msg = colored(f"[SYSTEM ERROR] {msg}", Fore.RED, Style.BRIGHT)
    print(f"{colored_msg}")
    raise exception


def pinfo(msg: str) -> None:
    colored_msg = colored(f"[INFO] {msg}", Fore.CYAN, Style.NORMAL)
    print(f"{colored_msg}")


def pdebug(msg: str, debug=False) -> None:
    if debug:
        colored_msg = colored(f"[DEBUG] {msg}", Fore.MAGENTA, Style.NORMAL)
        print(f"{colored_msg}")


def create_dir_or_pass(dir_name):
    try:
        os.mkdir(dir_name)
    except FileExistsError:
        pass


def create_directories(asm_dir="asm_codes", bin_dir="bin", root="") -> None:
    if root != "":
        if not os.path.isdir(root):
            create_dir_or_pass(root)
    create_dir_or_pass(root + asm_dir)
    create_dir_or_pass(root + bin_dir)
    create_dir_or_pass(root + "dumps")


def check_marta_files(path: str):
    """Check if MARTA files are already present in project path, otherwise
    create them.

    :param path: Project kernel path
    :type path: str
    """
    import os

    already_makefile = True
    already_marta_makefile = True

    if not os.path.isfile(f"{path}/Makefile"):
        already_makefile = False
        mk_file = get_data(f"profiler/MARTA.mk")
        shutil.copyfile(mk_file, f"{path}/Makefile")
    elif not os.path.isfile(f"{path}/MARTA.mk"):
        already_marta_makefile = False
        mk_file = get_data(f"profiler/MARTA.mk")
        # Do not create new file if not necessary
        if not filecmp.cmp(mk_file, f"{path}/Makefile", shallow=False):
            shutil.copyfile(mk_file, f"{path}/MARTA.mk")

    if already_makefile and already_marta_makefile:
        pinfo("Using existing Makefile. Remember to 'include MARTA.mk' in you Makefile")

    if not os.path.isdir(f"{path}/utilities"):
        utilities_dir = get_data(f"profiler/utilities")
        shutil.copytree(utilities_dir, f"{path}/utilities")


def get_name_from_dir(path_file):
    return path_file.split("/")[-1]


def dump_config_file(data_path: str) -> List[str]:
    """
    Read config template line by line

    :return: List of strings with all lines
    :rtype: list
    """
    config_file = get_data(data_path)
    try:
        f = open(config_file)
    except FileNotFoundError:
        perror("Package corrupted: template.yml missing")
    except IOError:
        perror("I/O error...")
    except Exception:
        perror("Something went wrong when dumping file")
    else:
        with f:
            return f.readlines()


class CaptureOutput(list):
    def __enter__(self):
        self._stdout = sys.stdout
        sys.stdout = self._stringio = StringIO()
        return self

    def __exit__(self, *args):
        self.extend(self._stringio.getvalue().splitlines())
        del self._stringio  # free up some memory
        sys.stdout = self._stdout

