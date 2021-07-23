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

import sys
import pytest
from unittest import mock

from marta.profiler.cli import cli


@pytest.mark.parametrize("args", ["", ["", ""], ["", "'not_found_file'"]])
def test_marta_profiler_error(args):
    with pytest.raises(SystemExit) as pytest_wrapped_e:
        with mock.patch.object(sys, "argv", args):
            cli()
    assert pytest_wrapped_e.type == SystemExit
    assert pytest_wrapped_e.value.code != 0


@pytest.mark.parametrize("args", [["", "-h"]])
def test_marta_profiler_normal_exit(args):
    with pytest.raises(SystemExit) as pytest_wrapped_e:
        with mock.patch.object(sys, "argv", args):
            cli()
            check_output_if_needed(args)
    assert pytest_wrapped_e.type == SystemExit
    assert pytest_wrapped_e.value.code == 0


def check_output_if_needed(args):
    # TODO
    pass
