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
from .timing import Timing


class Benchmark:
    """Benchmark class if meant for generating small benchmarks dynamically
    """

    def compile(self, output="", compiler="gcc", flags="-O3") -> None:
        if output != "":
            output = f"-o {output}"
        input_file = f"{self.name}"
        os.system(f"{compiler} {flags} {input_file} {output}")

    def compile_run_benchmark(
        self, bin_file="a.out", tmp_file="___tmp.txt", flags=""
    ) -> float:
        self.compile(flags=flags)
        d, _ = Timing.measure_benchmark(
            self.name, self.btype, bin_file=bin_file, tmp_file=tmp_file
        )
        os.remove(f"{bin_file}")
        os.remove(f"{tmp_file}")
        return d[self.btype]

    def __init__(self, name: str, path=".", btype="tsc"):
        self.name = name
        self.path = path
        self.btype = btype
