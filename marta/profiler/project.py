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

# Standard libraries
import os
from typing import List

# Third-party libraries
from shutil import copytree

# Local imports
from profiler.marta_utilities import perror


class Project:
    @staticmethod
    def dump_config_file() -> List[str]:
        """
        Read config template line by line

        :return: List of strings with all lines
        :rtype: list(str)
        """
        config_file = f"{os.path.dirname(__file__)}/data/template.yml"
        try:
            with open(config_file) as f:
                return f.readlines()
        except Exception:
            perror("Something went wrong when dumping file")

    @staticmethod
    def generate_new_project(name="marta_bench") -> int:
        src = f"{os.path.dirname(__file__)}/data"
        dst = f"{os.getcwd()}/{name}"
        try:
            copytree(src, dst)
        except FileExistsError:
            perror(f"'{name}' directory already exists!")
        except Exception:
            perror(f"Something went wrong when creating new project '{name}'")
        return 0
