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
import os

from marta.utils.marta_utilities import (
    perror,
    pexcept,
    check_marta_files,
    CaptureOutput,
    get_name_from_dir,
)


def test_perror():
    with pytest.raises(SystemExit) as pytest_wrapped_e:
        perror("Error", 1)
    assert pytest_wrapped_e.type == SystemExit
    assert pytest_wrapped_e.value.code == 1


def test_pexcept():
    with pytest.raises(Exception) as pytest_wrapped_e:
        pexcept("Error", Exception)
    assert pytest_wrapped_e.type == Exception


def test_check_marta_files_no_mod():
    check_marta_files("/tmp/")
    assert os.path.isfile("/tmp/Makefile")
    check_marta_files("/tmp/")
    assert os.path.isfile("/tmp/MARTA.mk") == False
    os.remove("/tmp/Makefile")


def test_get_name_from_dir():
    assert get_name_from_dir("hello/world") == "world"
    assert get_name_from_dir("/hello/world") == "world"
    assert get_name_from_dir("./hello/world") == "world"
    assert get_name_from_dir("./hello//world") == "world"


def test_capture_output():
    with CaptureOutput() as output:
        print("hello")
        print("world")

    assert output[0] == "hello"
    assert output[1] == "world"

    with CaptureOutput() as output:
        print("hello\nworld")

    assert output[0] == "hello"
    assert output[1] == "world"

    with CaptureOutput(output) as output:
        print("hello\nworld")

    assert output[0] == "hello"
    assert output[1] == "world"
    assert output[2] == "hello"
    assert output[3] == "world"
