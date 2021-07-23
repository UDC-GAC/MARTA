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

import pytest

from marta.profiler.compile import compile_file


@pytest.fixture(autouse=True)
def run_before_and_after_tests():
    input_file = "/tmp/test.c"
    os.system(f"cp tests/profiler/src/hello_world.c {input_file}")
    assert os.path.exists(input_file)
    yield
    os.remove(input_file)
    assert not os.path.exists(input_file)


def test_compile_run_benchmark():
    input_file = "/tmp/test.c"
    compile_file(input_file)
    assert os.path.exists(input_file)
    assert os.path.exists("/tmp/a.out")
    os.remove("/tmp/a.out")
