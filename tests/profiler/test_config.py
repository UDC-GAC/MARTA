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
import pytest
from marta.profiler.config import (
    check_correctness_file,
    check_correctness_kernel,
    get_kernel_config,
)


def test_check_correctness_file_kernel():
    kernel_setup = get_kernel_config("tests/profiler/config/correct.yml")
    assert check_correctness_file(kernel_setup)
    for kernel in kernel_setup:
        assert check_correctness_kernel(kernel)


def test_check_correctness_file_bad_path():
    kernel_setup = get_kernel_config("tests/profiler/config/bad_path.yml")
    with pytest.raises(SystemExit) as pytest_wrapped_e:
        check_correctness_file(kernel_setup)
    assert pytest_wrapped_e.type == SystemExit
    assert pytest_wrapped_e.value.code == 1


def test_check_correctness_incorrect():
    kernel_setup = get_kernel_config("tests/profiler/config/incorrect_file.yml")
    assert check_correctness_file(kernel_setup) == False
    for kernel in kernel_setup:
        assert check_correctness_kernel(kernel) == False


def test_check_correctness_incorrect_0():
    kernel_setup = get_kernel_config("tests/profiler/config/incorrect_file.yml")
    assert check_correctness_file(kernel_setup) == False


def test_check_not_found():
    with pytest.raises(SystemExit) as pytest_wrapped_e:
        get_kernel_config("tests/profiler/config/404.yml")
    assert pytest_wrapped_e.type == SystemExit
    assert pytest_wrapped_e.value.code == 1
