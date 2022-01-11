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

from marta.profiler.kernel import Kernel
from marta.utils.marta_utilities import pinfo


def _pinfo_macveth(kernel: Kernel) -> None:
    if kernel.macveth:
        text = f"MACVETH enabled: this could take longer."
        if not kernel.check_dump:
            text += "Use 'check_dump' option also for correctness."
        else:
            text += " Dumping values for assessing correctness."
        pinfo(text)