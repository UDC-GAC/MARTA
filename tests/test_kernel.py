import pytest

from profiler.kernel import Kernel


def test_compute_flops():
    assert Kernel.compute_flops("4*8", 1) == 4 * 8 / 1


def test_compute_flops_exception_0():
    with pytest.raises(Exception):
        Kernel.compute_flops("4*8string", 100, 1)


def test_compute_flops_exception_01():
    with pytest.raises(SystemExit) as pytest_wrapped_e:
        Kernel.compute_flops("string", 100)
    assert pytest_wrapped_e.type == SystemExit
    assert pytest_wrapped_e.value.code == 1
