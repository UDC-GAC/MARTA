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

from marta.profiler.system_config import SystemConfig, PyPerfError


@pytest.fixture
def get_system():
    return SystemConfig({"affinity": [2]})


def test_create_system_error():
    with pytest.raises(PyPerfError) as pytest_wrapped_e:
        SystemConfig({})
    assert pytest_wrapped_e.type == PyPerfError


def test_create_system_ok():
    s = SystemConfig({"affinity": [2]})
    assert s.system.cpus == tuple([2])


def test_tune_ok(get_system):
    assert get_system.tune() == None


def test_reset_ok(get_system):
    assert get_system.reset() == None
