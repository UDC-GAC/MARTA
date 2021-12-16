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

from marta.profiler.profiler import Profiler
from marta.profiler.d_features import Feature, dict_product


def test_profiler_correct_file():
    with pytest.raises(SystemExit) as pytest_wrapped_e:
        Profiler(["perf", "tests/profiler/config/correct.yml"])
    assert pytest_wrapped_e.type == SystemExit
    assert pytest_wrapped_e.value.code in [0, 1]


def test_number_iterations():
    f = Feature(
        "feature", {"type": "static", "evaluate": True, "value": [0, 1, 2, 3],},
    )
    f2 = Feature(
        "feature2",
        {
            "type": "static",
            "evaluate": True,
            "value": [0, 1, 2, 3],
            "restrict": "feature >= 2",
        },
    )
    f3 = Feature(
        "feature3",
        {
            "type": "static",
            "evaluate": True,
            "value": [0, 1, 2, 3],
            "restrict": "feature2 >= 2",
        },
    )
    assert len([i for i in dict_product({"feature": f}, [""])]) == 4
    assert len([i for i in dict_product({"feature": f, "feature2": f2}, [""])]) == 10
    assert (
        len(
            [
                i
                for i in dict_product(
                    {"feature": f, "feature2": f2, "feature2": f3}, [""]
                )
            ]
        )
        == 12
    )
