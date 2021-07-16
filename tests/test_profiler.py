import pytest

from marta.profiler.profiler import Profiler


def test_number_iterations():
    assert Profiler.comp_nvals([0, 1, 2, 3]) == 4
