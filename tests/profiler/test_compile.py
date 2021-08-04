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
import pandas as pd

from marta.profiler.compile import (
    compile_file,
    get_dict_from_d_flags,
    vector_report_analysis,
    get_dict_from_d_flags,
)


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


def test_vector_analysis_gcc():
    df = pd.DataFrame([0], columns=["loops_vectorized"])
    val = vector_report_analysis("tests/profiler/reports/gcc", "gcc")
    assert (df["loops_vectorized"] == val["loops_vectorized"]).all()


def test_vector_analysis_gcc_vectorized():
    df = pd.DataFrame([1], columns=["loops_vectorized"])
    val = vector_report_analysis("tests/profiler/reports/gcc_loop_vectorized", "gcc")
    assert (df["loops_vectorized"] == val["loops_vectorized"]).all()


def test_vector_analysis_icc():
    df = pd.DataFrame([0], columns=["loops_vectorized"])
    val = vector_report_analysis("tests/profiler/reports/icc", "icc")
    assert (df["loops_vectorized"] == val["loops_vectorized"]).all()


def test_vector_analysis_icc_vectorized():
    df = pd.DataFrame([1], columns=["loops_vectorized"])
    val = vector_report_analysis("tests/profiler/reports/icc_loop_vectorized", "icc")
    assert (df["loops_vectorized"] == val["loops_vectorized"]).all()


def test_dict_d_flags():
    expected = {"HELLO": "WORLD"}
    assert get_dict_from_d_flags("-DHELLO=WORLD") == expected
    expected = {"DHELLO": "WORLD"}
    get_dict_from_d_flags("DHELLO=WORLD")
    expected = {"DHELLO": 1}
    get_dict_from_d_flags("DHELLO")
    expected = {"HELLO": "WORLD", "GOODBYE": "WORLD", "HI": 1}
    assert get_dict_from_d_flags(" -DHELLO=WORLD -DGOODBYE=WORLD -DHI ") == expected
