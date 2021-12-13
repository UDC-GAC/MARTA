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

# Standard libraries
import yaml
import os

# Local imports
from marta.utils.marta_utilities import perror, pwarning

# Globals
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
        self.random_state = config.get("random_state")
        self.max_depth = config.get("max_depth", 10)
        self.max_leaves = config.get("max_leaves", 50)
        self.criterion = config.get("criterion", "gini")
        self.splitter = config.get("splitter", "best")
        self.min_score = config.get("min_score", 0.5)
        self.precision = config.get("precision", 3)
        self.pruning_mccp_alpha = config.get("pruning_mccp_alpha", 0.0)
        self.text_tree = config.get("text_tree", False)
        self.graph_tree = config.get("graph_tree", False)
        self.proportion = config.get("proportion", False)
        self.impurity = config.get("impurity", False)
        # False for vertical, True for horizontal
        self.orientation = config.get("orientation", "vertical")
        self.rotate = self.orientation == "horizontal"
        self.labels = config.get("labels", [])
        self.style = config.get("style", "scikit")
        self.scale = config.get("scale", 1.0)
        for key in config:
            setattr(self, key, config[key])


class PlotCfg:
    allowed_types = [
        "scatterplot",
        "lineplot",
        "relplot",
        "kdeplot",
        "catplot",
        "jointplot",
    ]
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
        self.sort = cfg.get("sort", None)
        self.log_scale = cfg.get("log_scale", None)
        self.kind = cfg.get("kind", None)
        self.hatches = cfg.get("hatches", False)
        self.palette = cfg.get("palette", "pastel")
        self.mark_centroids = cfg.get("mark_centroids", False)
        self.labels_catplot = cfg.get("labels_catplot", None)
        self.font_scale = cfg.get("font_scale", 1.0)
        self.multiple = cfg.get("multiple", "stack")
        self.rugplot = cfg.get("rugplot", False)
        try:
            self.x = cfg["x_axis"]
        except KeyError as K:
            perror(f"{K} needed in plot configuration")
        self.y = cfg.get("y_axis")


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
        analyzer_cfg["bandwidth"] = cat_cfg.get("bandwidth", 1.0)
        analyzer_cfg["bandwidth_type"] = cat_cfg.get("bandwidth_type", "silverman")
        analyzer_cfg["grid_search"] = cat_cfg.get("grid_search", False)
        analyzer_cfg["custom_params"] = cat_cfg.get("custom_params", False)
        analyzer_cfg["kernel"] = cat_cfg.get("kernel", "gaussian")
        analyzer_cfg["mode"] = cat_cfg.get("mode", "normal")
        if analyzer_cfg["ncats"] < 2:
            perror(
                "categories[num]",
                f"{analyzer_cfg['ncats']}",
                "value must be greater than one",
            )
        analyzer_cfg["catscale"] = eval(cat_cfg.get("scaling_factor", "1"))
        analyzer_cfg["categories_enabled"] = cat_cfg.get("enabled", True)
    except KeyError:
        analyzer_cfg["categories_enabled"] = False
        analyzer_cfg["ncats"] = None

    try:
        # plot keys
        analyzer_cfg["plot_cfg"] = {}
        analyzer_cfg["plot_enabled"] = {}
        for key in general_cfg["plot"]:
            analyzer_cfg["plot_cfg"][key] = PlotCfg(general_cfg["plot"][key])
            analyzer_cfg["plot_enabled"][key] = general_cfg["plot"][key].get(
                "enabled", True
            )
    except KeyError as k:
        pass

    try:
        # classification keys
        classification_cfg = general_cfg["classification"]
        analyzer_cfg["clf_type"] = classification_cfg["type"]
        analyzer_cfg["clf_cfg"] = classification_cfg["config"]
        analyzer_cfg["clf_enabled"] = classification_cfg.get("enabled", True)
    except KeyError:
        analyzer_cfg["clf_enabled"] = False
    try:
        # feature importance keys
        feature_cfg = general_cfg["feature_importance"]
        analyzer_cfg["feat_type"] = feature_cfg["type"]
        analyzer_cfg["feat_cfg"] = feature_cfg["config"]
        analyzer_cfg["feat_enabled"] = feature_cfg.get("enabled", True)
    except KeyError as K:
        analyzer_cfg["feat_enabled"] = False

    return analyzer_cfg
