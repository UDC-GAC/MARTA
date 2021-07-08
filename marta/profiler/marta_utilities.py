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

import sys
from colorama import Fore, Style


def colored(msg, color=Fore.RED, style=Style.NORMAL):
    return f"{color}{style}{msg}{Fore.RESET}{Style.RESET_ALL}"


def perror(msg: str, CODE=1) -> None:
    colored_msg = colored(f"[ERROR] {msg}", Fore.RED, Style.BRIGHT)
    print(f"{colored_msg}")
    sys.exit(CODE)


def pwarning(msg: str) -> None:
    colored_msg = colored(f"[WARNING] {msg}", Fore.YELLOW, Style.BRIGHT)
    print(f"{colored_msg}")


def pinfo(msg: str) -> None:
    colored_msg = colored(f"[INFO] {msg}", Fore.CYAN, Style.NORMAL)
    print(f"{colored_msg}")
