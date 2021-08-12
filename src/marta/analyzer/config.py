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


class PlotCfg:
    allowed_types = ["scatterplot", "lineplot", "relplot"]
    allowed_formats = ["pdf", "eps", "png", "ps", "svg"]

    def __init__(self, cfg: dict):
        self.type = cfg.get("type", "scatterplot")
        if self.type not in PlotCfg.allowed_types:
            perror(
                f"Wrong type for plot configuration, must be one of {PlotCfg.allowed_types}"
            )
        self.data = cfg.get("data", "raw")
        self.format = cfg.get("format", "pdf")
        if self.format not in PlotCfg.allowed_formats:
            perror(
                f"Wrong format for plot configuration, must be one of {PlotCfg.allowed_formats}"
            )
        self.hue = cfg.get("hue", None)
        self.size = cfg.get("size", None)
        self.col = cfg.get("col", None)
        self.row = cfg.get("row", None)
        self.x_label = cfg.get("x_label", None)
        self.y_label = cfg.get("y_label", None)
        try:
            self.x_axis = cfg["x_axis"]
            self.y_axis = cfg["y_axis"]
        except KeyError as K:
            perror(f"{K} needed in plot configuration")


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
    try:
        general_cfg = config[0]["kernel"]
        analyzer_cfg["input_file"] = general_cfg["input"]
        tmp = general_cfg["input"].split("/")[-1]
        analyzer_cfg["input_file_name"] = tmp.split(".")[0]
        analyzer_cfg["output_path"] = general_cfg["output_path"]
        if analyzer_cfg["output_path"][-1] == "/":
            analyzer_cfg["output_path"] = analyzer_cfg["output_path"][:-1]
        if not os.path.isdir(analyzer_cfg["output_path"]):
            try:
                os.mkdir(analyzer_cfg["output_path"])
            except Exception:
                perror("Output path not valid")
        # prepare_data keys
        prepdata_cfg = general_cfg["prepare_data"]
    except KeyError as K:
        perror(f"{K} key missing in configuration file")
    if not os.path.isdir(analyzer_cfg["output_path"]):
        perror("output_path specified is not a directory")
    analyzer_cfg["debug"] = general_cfg.get("debug", False)

    analyzer_cfg["filter_cols"] = prepdata_cfg["cols"].split(" ")
    if len(analyzer_cfg["filter_cols"]) == 0:
        perror("Need to choose dimensions (columns) to analyze")
    analyzer_cfg["filter_rows"] = prepdata_cfg.get("rows", "")
    analyzer_cfg["target"] = prepdata_cfg["target"]
    analyzer_cfg["norm"] = prepdata_cfg.get("norm", None)
    try:
        cat_cfg = prepdata_cfg["categories"]
        analyzer_cfg["ncats"] = int(cat_cfg.get("num", 2))
        if analyzer_cfg["ncats"] < 2:
            perror(
                "categories[num]",
                f"{analyzer_cfg['ncats']}",
                "value must be greater than one",
            )
        analyzer_cfg["catscale"] = eval(cat_cfg.get("scaling_factor", "1"))
    except KeyError:
        analyzer_cfg["ncats"] = None

    try:
        # plot keys
        analyzer_cfg["plot_cfg"] = PlotCfg(general_cfg["plot"])
        analyzer_cfg["plot_enabled"] = general_cfg["plot"].get("enabled", True)
    except KeyError:
        analyzer_cfg["plot_cfg"] = False

    if not analyzer_cfg["plot_enabled"]:
        pwarning("Plotting disabled")

    try:
        # classification keys
        classification_cfg = general_cfg["classification"]
        analyzer_cfg["clf_type"] = classification_cfg["type"]
        analyzer_cfg["clf_cfg"] = classification_cfg["config"]
        analyzer_cfg["clf_enabled"] = classification_cfg.get("enabled", True)
    except KeyError:
        analyzer_cfg["clf_enabled"] = False

    if not analyzer_cfg["clf_enabled"]:
        pwarning("Classification analysis disabled")

    try:
        # feature importance keys
        feature_cfg = general_cfg["feature_importance"]
        analyzer_cfg["feat_type"] = feature_cfg["type"]
        analyzer_cfg["feat_cfg"] = feature_cfg["config"]
        analyzer_cfg["feat_enabled"] = feature_cfg.get("enabled", True)
    except KeyError as K:
        analyzer_cfg["feat_enabled"] = False

    if not analyzer_cfg["feat_enabled"]:
        pwarning("Feature importance analysis disabled")

    return analyzer_cfg
