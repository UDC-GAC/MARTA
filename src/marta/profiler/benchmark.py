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

# Local imports
from marta.profiler.timing import Timing
from marta.profiler.compile import compile_file
from marta.utils.marta_utilities import perror


class BenchmarkError(Exception):
    pass


class Benchmark:
    """Benchmark class if meant for generating small benchmarks dynamically"""

    def compile_run_benchmark(
        self,
        compiler="gcc",
        flags=["-O3"],
        bin_file="/tmp/a.out",
        tmp_file="/tmp/___tmp.txt",
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
            self.src_file, self.btype, bin_file=bin_file, tmp_file=tmp_file
        )
        return d[self.btype]

    def __init__(self, src_file: str, path="/tmp/", btype="tsc", temp=False):
        self.src_file = src_file
        self.path = path
        self.btype = btype
        self.temp = temp
