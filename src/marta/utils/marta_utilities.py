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

# Standard libraries
import sys
import os

# Third-party libraries
from colorama import Fore, Style


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


def get_name_from_dir(path_file):
    return path_file.split("/")[-1]
