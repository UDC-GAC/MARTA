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

from marta.utils.marta_utilities import perror, pexcept


def test_perror():
    with pytest.raises(SystemExit) as pytest_wrapped_e:
        perror("Error", 1)
    assert pytest_wrapped_e.type == SystemExit
    assert pytest_wrapped_e.value.code == 1


class TestExcept(Exception):
    pass


def test_pexcept():
    with pytest.raises(TestExcept) as pytest_wrapped_e:
        pexcept("Error", TestExcept)
    assert pytest_wrapped_e.type == TestExcept
