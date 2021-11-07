# Copyright (c) Colorado State University. 2019-2021
# Copyright (c) Universidade da Coruña. 2019-2021
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
#
# Author: Marcos Horro <marcos.horro@udc.es>
#
# -*- coding: utf-8 -*-

import os
import yaml
import subprocess

from marta.utils.marta_utilities import pwarning, pexcept, perror, check_marta_files


class MARTAConfigError(Exception):
    pass


def parse_kernel_options(config: dict) -> dict:
    cfg = {}
    try:
        cfg["kernel"] = config["kernel"]["name"]
    except KeyError:
        pexcept("'name' key is missing!", MARTAConfigError)
    cfg["bench_type"] = config["kernel"].get("type", "regular")
    if cfg["bench_type"] not in ["regular", "micro"]:
        pexcept("type of benchmarking must be 'regular' or 'micro'", MARTAConfigError)
    cfg["descr"] = config["kernel"].get("description", "")
    try:
        cfg["path_kernel"] = config["kernel"].get("path", ".")
        if not os.path.isdir(cfg["path_kernel"]):
            raise MARTAConfigError
        check_marta_files(cfg["path_kernel"])
    except MARTAConfigError:
        perror("Kernel path does not exists")
    except Exception:
        perror("Something went wrong when checking path")
    cfg["show_progress_bars"] = config["kernel"].get("show_progress_bars", True)
    cfg["debug"] = config["kernel"].get("debug", False)
    cfg["preamble"] = config["kernel"].get("preamble")
    cfg["finalize"] = config["kernel"].get("finalize")

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
        pexcept(
            "processes must be an integer greater or equal to '1'", MARTAConfigError
        )
    except KeyError:
        cfg["processes"] = 1
    cfg["compiler_flags"] = config_comp.get("compiler_flags", {"gcc": [""]})
    cfg["common_flags"] = config_comp.get("common_flags", "")
    cfg["main_src"] = config_comp.get("main_src", False)
    cfg["inlined"] = config_comp.get("kernel_inlined", False)
    cfg["loop_type"] = config_comp.get("loop_type", "C")
    cfg["kernel_compilation"] = not cfg["inlined"]
    cfg["comp_debug"] = config_comp.get("debug", False)

    # ASM analysis
    asm_analysis = config_comp.get("asm_analysis", {})
    if isinstance(asm_analysis, dict):
        cfg["asm_count"] = asm_analysis.get("count_ins", False)
        cfg["asm_syntax"] = asm_analysis.get("syntax", "att")
        cfg["static_analysis"] = asm_analysis.get("static_analysis", "")
    else:
        pexcept("'asm_analysis' must be a dict", MARTAConfigError)

    # Configuration
    cfg["kernel_cfg"] = config_config.get("kernel_cfg", [""])
    if len(cfg["kernel_cfg"]) == 0:
        cfg["kernel_cfg"] = [""]
    cfg["d_features"] = config_config.get("d_features", [])
    cfg["d_flags"] = config_config.get("d_flags", [])
    cfg["flops"] = config_config.get("flops", 1)
    cfg["meta_info"] = config_config.get("meta_info", {})
    # meta_info = config_config.get("meta_info", {})
    # cfg["meta_info_script"] = meta_info.get("script", "")
    # cfg["meta_info_path"] = meta_info.get("path", ".")
    # cfg["meta_info_script_input"] = meta_info.get("input", "")
    # cfg["meta_info_script_input_suffix"] = meta_info.get("suffix", "")
    cfg["macveth_path"] = config_config.get("macveth_path_buil", "''")
    cfg["macveth_flags"] = config_config.get("macveth_flags", "-misa=avx2")
    cfg["macveth_target"] = config_config.get("macveth_target", "")

    # Derived columns
    cfg["derived_columns"] = config_config.get("derived", None)

    # Execution arguments
    cfg["intel_cache_flush"] = config_exec.get("intel_cache_flush", False)
    cfg["multithread"] = config_exec.get("multithread", False)
    cfg["init_data"] = config_exec.get("init_data", False)
    cfg["check_dump"] = config_exec.get("check_dump", False)
    cfg["execution_enabled"] = config_exec.get("enabled", True)
    cfg["measure_time"] = config_exec.get("time", False)
    cfg["measure_tsc"] = config_exec.get("tsc", False)
    cfg["threshold_outliers"] = config_exec.get("threshold_outliers", 3)
    cfg["discard_outliers"] = config_exec.get("discard_outliers", False)
    cfg["compute_avg"] = config_exec.get("compute_avg", True)
    cfg["nexec"] = config_exec.get("nexec", 7)
    cfg["nsteps"] = config_exec.get("nsteps", 1000)
    cfg["cpu_affinity"] = config_exec.get("cpu_affinity", 0)
    if cfg["cpu_affinity"] == 0:
        pwarning(
            "Consider using other CPU core than 0. Set in 'execution' under 'cpu_affinity'"
        )
    cfg["turbo"] = config_exec.get("intel_turbo", "")
    cfg["max_freq"] = config_exec.get("max_freq", "")
    cfg["papi_counters_path"] = config_exec.get("papi_counters_path")
    cfg["papi_counters"] = config_exec.get("papi_counters")
    if cfg["papi_counters"] != None:
        if not isinstance(cfg["papi_counters"], list):
            pexcept(
                "'papi_counters' must be a list of hardware events!", MARTAConfigError
            )
    cfg["exec_args"] = config_exec.get("prefix", "")
    cfg["output"] = config_exec.get("output", {})
    return cfg


def check_correctness_kernel(config: dict) -> bool:
    try:
        parse_kernel_options(config)
    except Exception:
        return False
    return True


def check_correctness_file(config: list) -> bool:
    try:
        if not isinstance(config, list):
            raise Exception
        for cfg in config:
            parse_kernel_options(cfg)
    except Exception:
        return False
    return True


def get_metadata(meta_info: dict, data: dict,) -> dict:
    meta_info_script = meta_info.get("script", "")
    meta_info_script_input = meta_info.get("input", ".")
    meta_info_script_input_suffix = meta_info.get("suffix", "")
    meta_info_path = meta_info.get("path", ".")
    if meta_info_script != "":
        # The script should return a dictionary
        input_arg = (
            data.get(meta_info_script_input, meta_info_script_input)
            + meta_info_script_input_suffix
        )
        proc = subprocess.Popen(
            ["python3", meta_info_script, input_arg],
            stdout=subprocess.PIPE,
            cwd=meta_info_path,
        )
        while True:
            line = proc.stdout.readline()
            try:
                if line.strip() == b"":
                    break
                return eval(line.strip())
            except Exception:
                perror(f"meta_info script does not return a dictionary: {line}!")
            if not line:
                break
    return {}


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
    except yaml.YAMLError as exc:
        if hasattr(exc, "problem_mark"):
            mark = exc.problem_mark
            perror(
                f"Error position in configuration file: row {mark.line+1}, column {mark.column+1})"
            )
        perror(f"Error in configuration file: {exc}")
    except Exception:
        perror("Unknown error when opening configuration file.")

    return kernel_setup


def get_derived_single(
    variables: list, derived: str, expression: str, data: dict
) -> dict:
    var_index = 0
    new_expression = expression
    for var in variables:
        new_expression = new_expression.replace(f"VAR_{var_index}", f"{str(data[var])}")
        var_index += 1
    try:
        value = eval(new_expression)
    except KeyError as k:
        perror(f"Key {k} does not exist in derived columns")
    except Exception as e:
        perror(f"Something went wrong when parsing derived values: {e}")
    return {derived: value}


def get_derived_multi(
    variables: list, derived: str, expression: str, data: dict
) -> dict:
    derived_dict = {}
    for var in variables:
        new_key = f"{derived}{var}"
        try:
            value = eval(expression.replace("VAR", f"{str(data[var])}"))
        except KeyError:
            try:
                value = eval(expression.replace("VAR", f"{str(derived_dict[var])}"))
            except KeyError:
                perror("Key does not exist in derived columns")
            except Exception:
                perror("Something went wrong when parsing derived values")
        except Exception:
            perror("Something went wrong when parsing derived values")
        derived_dict.update({new_key: value})
    return derived_dict


def get_derived_all(variables: list, derived: str, expression: str, data: dict) -> dict:
    new_expr = "["
    for var in variables:
        new_expr += f"{str(data[var])},"
    new_expr = f"{new_expr[:-1]}]"
    expression = expression.replace("ALL_VAR", new_expr)
    import numpy as np

    expression = expression.replace("SIZE", "len")
    expression = expression.replace("UNIQUE", "np.unique")
    try:
        value = eval(expression)
    except Exception:
        perror(
            "Expression not valid in derived arguments. Only SIZE and UNIQUE operations permitted, besides ALL_VAR variable"
        )

    return {derived: value}


def get_derived(derived_columns: dict, data: dict) -> dict:
    if derived_columns != None:
        derived_dict = {}
        for derived in derived_columns:
            variables = derived_columns[derived].get("variables")
            if variables == None or not isinstance(variables, list):
                perror("Bad formatting derived")
            expression = derived_columns[derived].get("expression")
            if expression == None:
                perror("Bad formatting derived")
            expr_type = derived_columns[derived].get("type", "single")
            if expr_type == "single":
                derived_dict.update(
                    get_derived_single(variables, derived, expression, data)
                )
            elif expr_type == "multi":
                derived_dict.update(
                    get_derived_multi(variables, derived, expression, data)
                )
            elif expr_type == "all":
                tmp = data.copy()
                tmp.update(derived_dict)
                derived_dict.update(
                    get_derived_all(variables, derived, expression, tmp)
                )
            else:
                perror("Bad type for derived, only allowed: all, single")

        return derived_dict
    return {}
