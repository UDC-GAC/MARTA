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
import os

import pytest

from marta.profiler.benchmark import Benchmark


@pytest.fixture(autouse=True)
def run_before_and_after_tests():
    f = "/tmp/test.c"
    os.system(f"cp tests/profiler/src/hello_world.c {f}")
    assert os.path.exists(f)
    yield
    os.system(f"rm {f}")
    assert not os.path.exists(f)


def test_compile_run_benchmark():
    b = Benchmark("/tmp/test.c")
    output = "/tmp/a.out"
    b.compile_run_benchmark()
    assert os.path.exists(output)
    os.system(f"rm {output}")
    assert not os.path.exists(output)
