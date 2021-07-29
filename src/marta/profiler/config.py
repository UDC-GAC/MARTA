# Copyright 2021 Marcos Horro
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import yaml
from marta.utils.marta_utilities import pwarning, pexcept, perror


class MARTAConfigError(Exception):
    pass


def parse_options(config: dict) -> dict:
    cfg = {}
    try:
        cfg["kernel"] = config["kernel"]["name"]
    except KeyError:
        pexcept("'name' key is missing!", MARTAConfigError)
    cfg["bench_type"] = config["kernel"].get("type", "regular")
    if cfg["bench_type"] not in ["regular", "micro"]:
        pexcept("type of benchmarking must be 'regular' or 'micro'", MARTAConfigError)
    cfg["descr"] = config["kernel"].get("description", "")
    cfg["path_kernel"] = config["kernel"].get("path", "./")
    cfg["show_progress_bars"] = config["kernel"].get("show_progress_bars", True)
    cfg["debug"] = config["kernel"].get("debug", False)

    try:
        config_config = config["kernel"]["configuration"]
        config_exec = config["kernel"]["execution"]
    except KeyError:
        pexcept(
            "Check your configuration file: 'configuration' and 'execution' keys could be missing...",
            MARTAConfigError,
        )

    try:
        config_comp = config["kernel"]["compilation"]
    except KeyError:
        config_comp = {}
        pwarning("No compilation options selected: using 'gcc' without any flags")

    cfg["compilation_enabled"] = config_comp.get("enabled", True)
    try:
        cfg["processes"] = int(config_comp["processes"])
        if cfg["processes"] < 1:
            raise ValueError
        if cfg["processes"] > 32:
            pwarning(
                f"Be careful with high degree of processes for compilation ({cfg['processes']} processes set)"
            )
    except ValueError:
        pexcept("processes must be an integer greater or equal to '1'")
    except KeyError:
        cfg["processes"] = 1
    cfg["compiler_flags"] = config_comp.get("compiler_flags", {"gcc": [""]})
    cfg["common_flags"] = config_comp.get("common_flags", "")
    cfg["kernel_compilation"] = config_comp.get("kernel_compilation_type", "infile")
    cfg["inlined"] = config_comp.get("kernel_inlined", False)
    cfg["comp_debug"] = config_comp.get("debug", False)

    # ASM analysis
    asm_analysis = config_comp.get("asm_analysis", {})
    cfg["asm_count"] = asm_analysis.get("count_ins", False)
    cfg["asm_syntax"] = asm_analysis.get("syntax", "att")
    cfg["static_analysis"] = asm_analysis.get("static_analysis", "")

    # Configuration
    cfg["kernel_cfg"] = config_config.get("kernel_config", [""])
    cfg["d_features"] = config_config.get("d_features", [])
    cfg["d_flags"] = config_config.get("d_flags", [])
    cfg["flops"] = config_config.get("flops", 1)
    meta_info = config_config.get("meta_info", {})
    cfg["meta_info_script"] = meta_info.get("script", "")
    cfg["meta_info_path"] = meta_info.get("path", ".")
    cfg["meta_info_script_input"] = meta_info.get("input", "")
    cfg["meta_info_script_input_suffix"] = meta_info.get("suffix", "")
    cfg["macveth_path"] = config_config.get("macveth_path_buil", "''")
    cfg["macveth_flags"] = config_config.get("macveth_flags", "-misa=avx2")
    cfg["macveth_target"] = config_config.get("macveth_target", "")

    # Execution arguments
    cfg["intel_cache_flush"] = config_exec.get("intel_cache_flush", False)
    cfg["init_data"] = config_exec.get("init_data", False)
    cfg["check_dump"] = config_exec.get("check_dump", False)
    cfg["execution_enabled"] = config_exec.get("enabled", True)
    cfg["measure_time"] = config_exec.get("time", False)
    cfg["measure_tsc"] = config_exec.get("tsc", False)
    cfg["threshold_outliers"] = config_exec.get("threshold_outliers", 3)
    cfg["mean_and_discard_outliers"] = config_exec.get(
        "mean_and_discard_outliers", False
    )
    cfg["nexec"] = config_exec.get("nexec", 7)
    cfg["nsteps"] = config_exec.get("nsteps", 1000)
    cfg["cpu_affinity"] = config_exec.get("cpu_affinity", 0)
    cfg["papi_counters_path"] = config_exec.get("papi_counters_path")
    cfg["papi_counters"] = config_exec.get("papi_counters")
    if cfg["papi_counters"] != None:
        if type(cfg["papi_counters"]) != list:
            pexcept(
                "'papi_counters' must be a list of hardware events!", MARTAConfigError
            )
    cfg["exec_args"] = config_exec.get("prefix", "")
    return cfg


def check_correctness_kernel(config: dict) -> bool:
    try:
        parse_options(config)
    except Exception:
        return False
    return True


def check_correctness_file(config: list) -> bool:
    try:
        if type(config) != list:
            raise Exception
        for cfg in config:
            parse_options(cfg)
    except Exception:
        return False
    return True


def get_kernel_config(input_file: str):
    try:
        from yaml import CLoader as Loader
    except ImportError:
        from yaml import Loader

    yml_config = input_file
    try:
        with open(yml_config, "r") as ymlfile:
            kernel_setup = yaml.load(ymlfile, Loader=Loader)
    except FileNotFoundError:
        perror("Configuration file not found")
    except Exception:
        perror("Unknown error when opening configuration file.")

    return kernel_setup
