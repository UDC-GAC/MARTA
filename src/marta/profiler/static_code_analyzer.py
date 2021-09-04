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
import json
import subprocess

# Local imports
from marta.utils.marta_utilities import pwarning


class LLVMMCAError(Exception):
    pass


class StaticCodeAnalyzer:
    @staticmethod
    def fix_json(json_file="perf.json") -> str:
        """This method is needed if LLVM-MCA version is previous to 13.0.0

        :param json_file: Input JSON file, defaults to "perf.json"
        :type json_file: str, optional
        :return: Name of fixed JSON file
        :rtype: str
        """
        with open(json_file) as f:
            lines = f.readlines()
            new_lines = []
            new_lines.append("[\n")
            for l in lines:
                if "not implemented" in l or "\n" == l or "Code Region" in l:
                    continue
                if l == "}\n":
                    new_lines.append("},\n")
                elif l == "]\n":
                    new_lines.append("],\n")
                else:
                    new_lines.append(l)
            if new_lines[-1] == "},\n":
                new_lines[-1] = "}\n"
            elif new_lines[-1] == "],\n":
                new_lines[-1] = "]\n"
            new_lines.append("]\n")
        json_file_fixed = json_file.replace(".json", "_fixed.json")
        with open(json_file_fixed, "w") as f:
            f.writelines(new_lines)
        os.remove(f"{json_file}")
        return json_file_fixed

    def compute_performance(
        self, name_bench: str, iterations=1, region="kernel"
    ) -> dict:
        """Get the performance metrics reported by the tool. Currently only LLVM-MCA.

        :param name_bench: Name of the asm file.
        :type name_bench: str
        :param iterations: Number of iterations to run the tool., defaults to 1
        :type iterations: int, optional
        :param region: Name of the region of interest., defaults to "kernel"
        :type region: str, optional
        :return: Returns the IPC, Cycles and uOPS reported by the tool.
        :rtype: dict
        """
        json_file = f"/tmp/{name_bench.replace('.s','')}_perf.json"

        cmd = [
            f"{self.binary}",
            f"-march={self.arch}",
            f"-mcpu={self.cpu}",
            f"-iterations={iterations}",
            f"{name_bench}",
            f"-json",
            "-o",
            f"{json_file}",
        ]
        ret = subprocess.run(cmd)
        if ret:
            raise LLVMMCAError

        with open(f"{json_file}") as f:
            try:
                dom = json.loads(f.read())
            except Exception:
                json_file = StaticCodeAnalyzer.fix_json(json_file)
                with open(f"{json_file}") as f:
                    dom = json.loads(f.read())

        d = {}
        try:
            summary = dom[region]["SummaryView"]
        except KeyError:
            pwarning("llvm-mca data could not be parsed")
            return d
        finally:
            os.remove(f"{json_file}")

        d.update({"llvm-mca_IPC": summary["IPC"]})
        d.update(
            {
                "llvm-mca_CyclesPerIteration": summary["TotalCycles"]
                / summary["Iterations"]
            }
        )
        d.update({"llvm-mca_uOpsPerCycle": summary["uOpsPerCycle"]})
        return d

    def __init__(self, cpu: str, binary="llvm-mca", arch="x86-64") -> None:
        self.binary = binary
        self.cpu = cpu
        self.arch = arch
