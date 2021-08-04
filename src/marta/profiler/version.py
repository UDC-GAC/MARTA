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
import pkg_resources


def print_version() -> None:
    """
    Print version and copyright message (if not quiet execution)
    """
    __version__ = pkg_resources.require("marta")[0].version
    s = """
 __  __    _    ____ _____  _
|  \/  |  / \  |  _ |_   _|/ \ 
| |\/| | / _ \ | |_) || | / _ \ 
| |  | |/ ___ \|  _ < | |/ ___ \ 
|_|  |_/_/   \_|_| \_\|_/_/   \_\\
    """
    print(
        f"{s}\n"
        f"Micro ARchitectural Toolkit Analysis (MARTA) - Profiler v{__version__}\n",
        end="",
    )