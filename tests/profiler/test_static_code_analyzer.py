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

import pytest

from marta.profiler.static_code_analyzer import StaticCodeAnalyzer


@pytest.fixture
def check_llvm_mca():
    import subprocess

    for suffix in ["", "-10", "-11" "-12"]:
        try:
            executable = f"llvm-mca{suffix}"
            subprocess.call([executable, "--version"])
            return executable
        except OSError:
            pass
    return None


def test_compute_performance():
    # TODO
    assert True

