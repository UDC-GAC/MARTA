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

import yaml

from marta.profiler.kernel import Kernel


@pytest.fixture
def get_kernel():
    try:
        from yaml import CLoader as Loader
    except ImportError:
        from yaml import Loader
    with open("tests/profiler/config/kernel.yml", "r") as ymlfile:
        kernel_setup = yaml.load(ymlfile, Loader=Loader)
    return Kernel(kernel_setup[0])


def test_generate_report(get_kernel):
    assert isinstance(get_kernel._generate_report(), str)
    assert isinstance(get_kernel._generate_report(False), str)


def test_compute_flops():
    assert Kernel.compute_flops("4*8", 1) == 4 * 8 / 1


def test_compute_flops_exception_0():
    with pytest.raises(Exception):
        Kernel.compute_flops("4*8string", 100, 1)


def test_compute_flops_exception_01():
    with pytest.raises(SystemExit) as pytest_wrapped_e:
        Kernel.compute_flops("string", 100)
    assert pytest_wrapped_e.type == SystemExit
    assert pytest_wrapped_e.value.code == 1


# TODO
# def test_save_results
# def test_compile_parse_asm
# def test_define_papi_counters
# def test_get_dict_from_d_flags
# def test_get_suffix_and_flags
# def test_get_asm_name
# def test_run
# def test_compile
