import pytest

from profiler.asm_analyzer import ASMParserFactory


def test_wrong_backend():
    with pytest.raises(SystemExit) as pytest_wrapped_e:
        ASMParserFactory.parse_asm("foo", "")
    assert pytest_wrapped_e.type == SystemExit
    assert pytest_wrapped_e.value.code == 1
