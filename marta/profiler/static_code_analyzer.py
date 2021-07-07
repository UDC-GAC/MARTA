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
import json


class StaticCodeAnalyzer:
    def __init__(self, cpu, binary="llvm-mca", arch="x86-64"):
        self.binary = binary
        self.cpu = cpu
        self.arch = arch

    @staticmethod
    def fix_json(json_file="perf.json") -> str:
        """This method is needed if LLVM-MCA version is previous to 12.0.0

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

    def compute_performance(self, name_bench, iterations=1) -> dict:
        json_file = f"{name_bench.replace('.s','')}_perf.json"
        os.system(
            f"{self.binary} -march={self.arch} -mcpu={self.cpu} -iterations={iterations} {name_bench} -json -o {json_file}"
        )
        with open(f"{json_file}") as f:
            try:
                dom = json.loads(f.read())
            except Exception:
                json_file = StaticCodeAnalyzer.fix_json(json_file)
                with open(f"{json_file}") as f:
                    dom = json.loads(f.read())

        summary = dom[0]["SummaryView"]
        d = {}
        d.update({"llvm-mca_IPC": summary["IPC"]})
        d.update(
            {
                "llvm-mca_CyclesPerIteration": summary["TotalCycles"]
                / summary["Iterations"]
            }
        )
        d.update({"llvm-mca_uOpsPerCycle": summary["uOpsPerCycle"]})

        # Be clean
        os.remove(f"{json_file}")
        return d
