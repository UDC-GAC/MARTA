import pytest

from marta.profiler.profiler import Profiler


def test_profiler_correct_file():
    with pytest.raises(SystemExit) as pytest_wrapped_e:
        Profiler(["tests/profiler/config/correct.yml"])
    assert pytest_wrapped_e.type == SystemExit
    assert pytest_wrapped_e.value.code == 0


def test_number_iterations():
    assert Profiler.comp_nvals([0, 1, 2, 3]) == 4
