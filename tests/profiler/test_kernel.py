import pytest

import yaml

from marta.profiler.kernel import Kernel


@pytest.fixture
def get_kernel():
    try:
        from yaml import CLoader as Loader
    except ImportError:
        from yaml import Loader
    with open("tests/profiler/config/kernel.yml", "r") as ymlfile:
        kernel_setup = yaml.load(ymlfile, Loader=Loader)
    return Kernel(kernel_setup[0])


def test_generate_report(get_kernel):
    assert type(get_kernel.generate_report()) == str
    assert type(get_kernel.generate_report(False)) == str


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


# TODO
# def test_save_results
# def test_compile_parse_asm
# def test_define_papi_counters
# def test_get_dict_from_d_flags
# def test_get_suffix_and_flags
# def test_get_asm_name
# def test_run
# def test_compile
