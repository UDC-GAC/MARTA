import unittest
import profiler.profiler as profiler


def test_0001():
    assert sum([1, 2, 3]) == 6, "Should be 6"


def test_compute_flops():
    assert profiler.compute_flops("4*8", 100, 1) == 4 * 8 * 100 / 1
