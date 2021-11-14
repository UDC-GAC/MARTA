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
import pkg_resources


def get_version(component: str) -> str:
    __version__ = pkg_resources.require("marta")[0].version
    header = (
        "    __  ___ ___     ____  ______ ___ \n"
        "   /  |/  //   |   / __ \/_  __//   | \n"
        "  / /|_/ // /| |  / /_/ / / /  / /| | \n"
        " / /  / // ___ | / _, _/ / /  / ___ | \n"
        "/_/  /_//_/  |_|/_/ |_| /_/  /_/  |_| \n"
        "                                      \n"
        f"Multi-configuration Assembly pRofiler and Toolkit for performance Analysis (MARTA) - {component} v{__version__}"
    )

    return header


def print_version(component: str) -> None:
    """
    Print version and copyright message
    """
    __version__ = pkg_resources.require("marta")[0].version
    header = """
    __  ___ ___     ____  ______ ___ 
   /  |/  //   |   / __ \/_  __//   |
  / /|_/ // /| |  / /_/ / / /  / /| |
 / /  / // ___ | / _, _/ / /  / ___ |
/_/  /_//_/  |_|/_/ |_| /_/  /_/  |_|
                                     
    """
    print(header)
    print(
        f"Multi-configuration Assembly pRofiler and Toolkit for performance Analysis (MARTA) - {component} v{__version__}"
    )
