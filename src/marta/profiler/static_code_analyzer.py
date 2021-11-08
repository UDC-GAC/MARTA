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
import pathlib
import yaspin

# Local imports
from marta.utils.marta_utilities import pwarning, perror


class LLVMMCAError(Exception):
    pass


class StaticCodeAnalyzer:
    @staticmethod
    def clean_comments(json_file: str = "perf.json") -> None:
        lines = []
        with open(json_file, "r") as f:
            for line in f:
                if (
                    "#NO_APP" in line
                    or "#APP" in line
                    or line.startswith("# ")
                    or line == "\n"
                ) and not "LLVM" in line:
                    continue
                lines.append(line)

        with open(json_file, "w") as f:
            f.writelines(lines)

    @staticmethod
    def fix_json(json_file: str = "perf.json") -> str:
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

    def get_llvm_mca_version(self) -> int:
        lines = os.popen(f"{self.binary} --version").read()
        try:
            for line in lines:
                if "version" in line:
                    major_version = int(line.split(" ")[-1].split(".")[0])
                    return major_version
        except Exception:
            pass
        return -1

    def check_if_compatible_version(self):
        if self.get_llvm_mca_version() < 13:
            return False
        return True

    def compute_performance(
        self,
        name_bench: str,
        iterations: int = 1,
        region: str = "kernel",
        stderr: int = None,
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
        stderr_file = f"/tmp/{name_bench.replace('.s','')}_perf.stderr"

        path_json_file = json_file.rsplit("/", 1)[0]
        if path_json_file != "/tmp":
            pathlib.Path(path_json_file).mkdir(parents=True, exist_ok=True)

        if os.path.exists(json_file):
            os.remove(json_file)

        self.clean_comments(name_bench)

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
        with open(stderr_file, "w") as fstderr:
            ret = subprocess.run(cmd, stderr=fstderr)
        # ret = subprocess.run(cmd, stderr=stderr)

        if ret and not os.path.exists(json_file):
            raise LLVMMCAError("Path does not exist")

        with open(f"{json_file}") as f:
            try:
                dom = json.loads(f.read())
            except Exception:
                json_file = StaticCodeAnalyzer.fix_json(json_file)
                try:
                    with open(f"{json_file}") as f:
                        dom = json.loads(f.read())
                except Exception:
                    raise LLVMMCAError

        llvm_mca_results = {}
        try:
            kernel_region = dom["CodeRegions"][0]
            for i in range(len(dom["CodeRegions"])):
                if region == dom["CodeRegions"][i]["Name"]:
                    kernel_region = dom["CodeRegions"][i]
            summary = kernel_region["SummaryView"]
        except KeyError:
            pwarning("llvm-mca data could not be parsed")
            return llvm_mca_results
        except TypeError:
            pwarning(
                "\nBad format in llvm-mca json output:\n\tyou need to update your version to LLVM >= 13.x.x."
            )
            return llvm_mca_results

        llvm_mca_results.update({"llvm-mca_IPC": summary["IPC"]})
        llvm_mca_results.update(
            {
                "llvm-mca_CyclesPerIteration": summary["TotalCycles"]
                / summary["Iterations"]
            }
        )
        llvm_mca_results.update({"llvm-mca_uOpsPerCycle": summary["uOpsPerCycle"]})
        return llvm_mca_results

    def get_data(self):
        if not hasattr(self, "data"):
            self.data = {}
        return self.data

    def perform_analysis(self, path, nsteps):
        with yaspin(text="Static analysis with LLVM-MCA") as sp:
            self.data = self.compute_performance(path, nsteps)
            sp.hidden()

    def __init__(
        self, cpu: str, binary: str = "llvm-mca", arch: str = "x86-64",
    ) -> None:
        self.binary = binary
        self.cpu = cpu
        self.arch = arch

