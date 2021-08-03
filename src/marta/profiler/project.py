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
import os
from typing import List

# Third-party libraries
import shutil

# Local imports
from marta import get_data
from marta.utils.marta_utilities import perror


class Project:
    @staticmethod
    def dump_config_file() -> List[str]:
        """
        Read config template line by line

        :return: List of strings with all lines
        :rtype: list
        """
        config_file = get_data(f"profiler/template.yml")
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
        return 0
