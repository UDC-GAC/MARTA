import sys
import os
import pytest

# FIXME: This is a DIY shitty
sys.path.append(os.path.realpath(os.path.dirname(__file__) + "/.."))

from asm_analyzer import ASMParserFactory


def test_wrong_backend():
    with pytest.raises(SystemExit) as pytest_wrapped_e:
        ASMParserFactory.parse_asm("foo", "")
    assert pytest_wrapped_e.type == SystemExit
    assert pytest_wrapped_e.value.code == 1
