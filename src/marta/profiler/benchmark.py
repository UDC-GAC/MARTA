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

from typing import List

# Local imports
from marta.profiler.timing import Timing
from marta.profiler.compile import compile_file
from marta.utils.marta_utilities import perror


class BenchmarkError(Exception):
    pass


class Benchmark:
    """Benchmark class if meant for generating small benchmarks dynamically"""

    def compile(
        self,
        compiler: str = "gcc",
        flags: List[str] = ["-O3"],
        bin_file: str = "/tmp/a.out",
    ) -> float:
        try:
            compile_file(
                self.src_file,
                output=bin_file,
                compiler=compiler,
                flags=flags,
                temp=self.temp,
            )
        except FileNotFoundError as e:
            perror(e)
        except Exception:
            raise BenchmarkError

    def execute(
        self,
        bin_file: str = "/tmp/a.out",
        tmp_file: str = "/tmp/___marta_results.txt",
        nsteps: int = 10000,
        exec_args: List[str] = [""],
    ):
        d, _ = Timing.measure_benchmark(
            self.src_file,
            self.btype,
            bin_file=bin_file,
            tmp_file=tmp_file,
            nsteps=nsteps,
            exec_args=exec_args,
        )
        return d[self.btype]

    def compile_run_benchmark(
        self,
        compiler: str = "gcc",
        flags: List[str] = ["-O3"],
        bin_file: str = "/tmp/a.out",
        tmp_file: str = "/tmp/___marta_results.txt",
        nsteps: int = 10000,
    ) -> float:
        try:
            compile_file(
                self.src_file,
                output=bin_file,
                compiler=compiler,
                flags=flags,
                temp=self.temp,
            )
        except FileNotFoundError as e:
            perror(e)
        except Exception:
            raise BenchmarkError

        d, _ = Timing.measure_benchmark(
            self.src_file,
            self.btype,
            bin_file=bin_file,
            tmp_file=tmp_file,
            nsteps=nsteps,
        )
        return d[self.btype]

    def __init__(
        self, src_file: str, path: str = "/tmp/", btype: str = "tsc", temp: bool = False
    ) -> None:
        self.src_file = src_file
        self.path = path
        self.btype = btype
        self.temp = temp
