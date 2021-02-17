from profiler import Profiler
import sys
import os
import pytest

# FIXME: This is a DIY shitty
sys.path.append(os.path.realpath(os.path.dirname(__file__) + "/.."))


def test_number_iterations():
    assert Profiler.comp_nvals([0, 1, 2, 3]) == 4
    #assert Profiler.comp_nvals(range(4)) == 4
