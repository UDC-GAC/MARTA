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

from marta.utils.marta_utilities import perror
from marta.analyzer.decision_tree import DecisionTree


def parse_options(config: dict) -> dict:
    analyzer_cfg = {}
    try:
        general_cfg = config[0]["kernel"]
        analyzer_cfg["debug"] = (
            general_cfg["debug"] if "debug" in general_cfg else False
        )
        analyzer_cfg["input_file"] = general_cfg["input"]
        analyzer_cfg["force_replacement"] = (
            general_cfg["force_replacement"]
            if "force_replacement" in general_cfg.keys()
            else False
        )
        analyzer_cfg["output_file"] = general_cfg["output"]
        analyzer_cfg["rm_temp_files"] = general_cfg["clean"]
        analyzer_cfg["print_debug"] = general_cfg["debug"]

        # prepare_data keys
        prepdata_cfg = general_cfg["prepare_data"]
        analyzer_cfg["filter_cols"] = prepdata_cfg["cols"].split(" ")
        analyzer_cfg["filter_rows"] = (
            prepdata_cfg["rows"] if "rows" in prepdata_cfg.keys() else ""
        )
        analyzer_cfg["target"] = prepdata_cfg["target"]
        analyzer_cfg["norm"] = (
            prepdata_cfg["norm"]["enabled"] if "norm" in prepdata_cfg.keys() else False
        )
        analyzer_cfg["norm_type"] = (
            prepdata_cfg["norm"]["type"] if analyzer_cfg["norm"] else ""
        )
        analyzer_cfg["ncats"] = int(prepdata_cfg["categories"]["num"])
        if analyzer_cfg["ncats"] < 1:
            raise ValueError(
                "categories[num]",
                f"{analyzer_cfg['ncats']}",
                "value must be greater than one",
            )
        analyzer_cfg["catscale"] = eval(prepdata_cfg["categories"]["scale_factor"])
        analyzer_cfg["cattype"] = prepdata_cfg["categories"]["type"]

        # classification keys
        classification_cfg = general_cfg["classification"]
        analyzer_cfg["class_type"] = classification_cfg["type"]
        if analyzer_cfg["class_type"] == "decisiontree":
            analyzer_cfg["dt_cfg"] = DecisionTree.DTConfig(
                classification_cfg["dt_settings"]
            )
        elif analyzer_cfg["class_type"] == "randomforest":
            # TODO: implement random forest classification
            pass
        else:
            raise ValueError(
                "classification[type]",
                analyzer_cfg["class_type"],
                "unknown classification algorithm: try 'decisiontree' or 'randomforest'",
            )
    except KeyError as K:
        perror(f"key {K} missing in configuration file")
    except TypeError as T:
        perror(f"key {T} wrong type")
    except ValueError as V:
        key, value, msg = V.args
        perror(f"{key} = {value}, {msg}")
    except SyntaxError as S:
        perror(f"syntax error in {S}")
    except NameError as N:
        perror(f"{N}")
    except Exception as E:
        perror(f"something went wrong: {E}")
    return analyzer_cfg
