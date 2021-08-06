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
import os

from marta.utils.marta_utilities import perror, pwarning

decision_tree_synonyms = ["decision tree", "decisiontree", "decision_tree"]
random_forest_synonyms = ["random_forest", "random forest", "randomforest"]


class RFConfig:
    def __init__(self, config: dict) -> None:
        self.n_estimators = config.get("n_estimators", 100)
        self.criterion = config.get("criterion", "gini")
        self.max_depth = config.get("max_depth", 10)
        self.min_samples_split = config.get("min_samples_split", 2)
        self.min_samples_leaf = config.get("min_samples_leaf", 1)
        self.n_jobs = config.get("n_jobs", 1)
        self.random_state = config.get("random_state", 0)
        for key in config:
            setattr(self, key, config[key])


class DTConfig:
    def __init__(self, config: dict) -> None:
        self.max_depth = config.get("max_depth", 10)
        self.max_leaves = config.get("max_leaves", 50)
        self.criterion = config.get("criterion", "gini")
        self.min_score = config.get("min_score", 0.5)
        self.pruning_mccp_alpha = config.get("pruning_mccp_alpha", 0.0)
        self.text_tree = config.get("text_tree", False)
        self.graph_tree = config.get("graph_tree", False)
        # False for vertical, True for horizontal
        if "orientation" not in config:
            self.orientation = False
        else:
            self.orientation = config["orientation"] == "horizontal"
            if self.orientation:
                pwarning("Horizontal Decision Tree printing disabled.")
        for key in config:
            setattr(self, key, config[key])


def load_yaml_file(file: str) -> dict:
    try:
        from yaml import CLoader as Loader
    except ImportError:
        from yaml import Loader

    try:
        with open(file, "r") as ymlfile:
            cfg = yaml.load(ymlfile, Loader=Loader)
    except FileNotFoundError:
        perror("Configuration file not found")
    except Exception:
        perror("Unknown error when opening configuration file.")
    return cfg


def parse_options(config: dict) -> dict:
    analyzer_cfg = {}
    general_cfg = config[0]["kernel"]
    analyzer_cfg["input_file"] = general_cfg["input"]
    analyzer_cfg["output_file"] = general_cfg["output_path"]
    if not os.path.isdir(analyzer_cfg["output_file"]):
        perror("output_path specified is not a directory")
    analyzer_cfg["debug"] = general_cfg.get("debug", False)

    # prepare_data keys
    prepdata_cfg = general_cfg["prepare_data"]
    analyzer_cfg["filter_cols"] = prepdata_cfg["cols"].split(" ")
    if len(analyzer_cfg["filter_cols"]) == 0:
        perror("Need to choose dimensions (columns) to analyze")
    analyzer_cfg["filter_rows"] = prepdata_cfg.get("rows", "")
    analyzer_cfg["target"] = prepdata_cfg["target"]
    analyzer_cfg["norm"] = prepdata_cfg.get("norm", None)
    cat_cfg = prepdata_cfg["categories"]
    analyzer_cfg["ncats"] = int(cat_cfg.get("num", 2))
    if analyzer_cfg["ncats"] < 2:
        raise ValueError(
            "categories[num]",
            f"{analyzer_cfg['ncats']}",
            "value must be greater than two",
        )
    analyzer_cfg["catscale"] = eval(cat_cfg.get("scaling_factor", "1"))

    # classification keys
    classification_cfg = general_cfg["classification"]
    analyzer_cfg["clf_type"] = classification_cfg["type"]
    analyzer_cfg["clf_cfg"] = classification_cfg["config"]

    # feature importance keys
    feature_cfg = general_cfg["feature_importance"]
    analyzer_cfg["feat_type"] = feature_cfg["type"]
    analyzer_cfg["feat_cfg"] = feature_cfg["config"]
    return analyzer_cfg
