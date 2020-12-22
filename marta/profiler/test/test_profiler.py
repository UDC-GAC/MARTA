import sys
import os
import pytest

# FIXME: This is a DIY shitty
sys.path.append(os.path.realpath(os.path.dirname(__file__) + "/.."))

import profiler as p


def test_compute_flops():
    assert p.compute_flops("4*8", 100, 1) == 4 * 8 * 100 / 1


def test_compute_flops_exception_0():
    with pytest.raises(Exception):
        p.compute_flops("4*8string", 100, 1)


def test_compute_flops_exception_01():
    with pytest.raises(SystemExit):
        p.compute_flops("string", 100, 1)


def test_compute_flops_exception_1():
    with pytest.raises(Exception):
        p.compute_flops("4", 100, "string")


def test_compute_flops_exception_2():
    with pytest.raises(Exception):
        p.compute_flops("4", "string", 1)
