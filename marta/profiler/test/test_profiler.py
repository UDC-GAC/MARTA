import unittest
import sys
import os

# FIXME: This is a DIY shitty
sys.path.append(os.path.realpath(os.path.dirname(__file__) + "/.."))


import profiler.profiler as p


def test_0001():
    assert sum([1, 2, 3]) == 6, "Should be 6"


def test_compute_flops():
    assert p.compute_flops("4*8", 100, 1) == 4 * 8 * 100 / 1
