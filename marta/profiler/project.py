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

import os
import sys
from shutil import copytree


class Project:
    @staticmethod
    def dump_config_file():
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
            print("Something went wrong when dumping file")
            sys.exit(1)

    @staticmethod
    def generate_new_project(name="new_bench"):
        src = f"{os.path.dirname(__file__)}/data"
        dst = f"{os.getcwd()}/{name}"
        try:
            copytree(src, dst)
        except FileExistsError:
            print("'new_bench' directory already exists!")
            sys.exit(1)
        except Exception:
            print("Something went wrong when creating new project")
            sys.exit(1)
        return 0
