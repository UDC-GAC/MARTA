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
import os
from typing import List

# Third-party libraries
import shutil

# Local imports
from marta import get_data
from marta.utils.marta_utilities import perror


class Project:
    @staticmethod
    def generate_new_project(name="marta_bench", type="bench") -> int:
        src = get_data(f"profiler/marta_{type}")
        dst = f"{os.getcwd()}/{name}"
        try:
            shutil.copytree(src, dst)
        except FileExistsError:
            perror(f"'{name}' directory already exists!")
        except FileNotFoundError:
            perror(f"Package corrupted: marta_{type} files are missing")
        except Exception:
            perror(f"Something went wrong when creating new project '{name}'")
        src = get_data(f"profiler/template.yml")
        dst = f"{os.getcwd()}/{name}/profiler.yml"
        lines = Project.dump_config_file(src, name)
        with open(dst, "w") as f:
            f.writelines(lines)

        return 0

    @staticmethod
    def dump_config_file(data_path: str, name: str = "marta_bench") -> List[str]:
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
                lines = []
                for line in f.readlines():
                    lines.append(line.replace("##NAME##", name))
                return lines
