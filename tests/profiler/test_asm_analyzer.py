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

from marta.profiler.asm_analyzer import (
    ASMParserFactory,
    ASMParser,
    ASMParserATT,
    ASMParserIntel,
)


@pytest.fixture
def asm_att_tokenized():
    asm = "vextractf128    $0x1, %ymm0, %xmm1"
    return ASMParser.tokenize_instruction([asm])


@pytest.fixture
def asm_intel_tokenized():
    asm = "vextractf128    xmm1, ymm0, 0x1"
    return ASMParser.tokenize_instruction([asm])


def test_wrong_backend():
    with pytest.raises(SystemExit) as pytest_wrapped_e:
        ASMParserFactory.parse_asm("foo", "")
    assert pytest_wrapped_e.type == SystemExit
    assert pytest_wrapped_e.value.code == 1


def test_skip_asm():
    assert ASMParser.skip_asm_instruction([""])
    assert ASMParser.skip_asm_instruction(["."])
    assert ASMParser.skip_asm_instruction(["ret"])
    assert ASMParser.skip_asm_instruction(["movss xmm0, xmm1", "ret"])
    assert ASMParser.skip_asm_instruction(["movss xmm0, xmm1"]) == False


def test_intel_get_raw_asm_type(asm_intel_tokenized):
    result = "vextractf128_XMM_YMM_IMM"
    assert ASMParserIntel.get_raw_asm_type(asm_intel_tokenized) == result


def test_att_get_raw_asm_type(asm_att_tokenized):
    result = "vextractf128_IMM_YMM_XMM"
    assert ASMParserATT.get_raw_asm_type(asm_att_tokenized) == result


def test_tokenize_instruction(asm_att_tokenized, asm_intel_tokenized):
    assert 4 == len(asm_att_tokenized)
    assert 4 == len(asm_intel_tokenized)


def test_att_operand_to_suffix():
    op = ASMParserATT.operand_to_suffix
    assert "XMM" == op("%xmm0")
    assert "YMM" == op("%ymm0")
    assert "ZMM" == op("%zmm0")
    assert "GPR" == op("%rdx")
    assert "IMM" == op("$11")
    assert "LABEL" == op(".label")
    assert "MEM" == op("32(%rdx,%rax,4)")


def test_intel_operand_to_suffix():
    op = ASMParserIntel.operand_to_suffix
    assert "XMM" == op("xmm0")
    assert "YMM" == op("ymm0")
    assert "ZMM" == op("zmm0")
    assert "GPR" == op("rdx")
    assert "IMM" == op("0x4")
    assert "IMM" == op("50")
    assert "LABEL" == op(".label")
    assert "MEM" == op("[%rdx + %rax + 4]")
