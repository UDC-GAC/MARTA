#!/usr/bin/env python3
# Copyright 2019-2021 (c) Colorado State University
# Copyright 2020-2021 (c) Universidade da Coruña
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

# -*- coding: utf-8 -*-

import argparse
import graphviz
import numpy as np
import os
import pandas as pd
import sys
import yaml

from sklearn import tree


class RandomForest:
    # TODO
    pass


class DecisionTree:
    class DTConfig:
        def __init__(self, config: dict) -> None:
            for key in config:
                setattr(self, key, config[key])

            if "max_depth" not in config:
                self.max_depth = 10
            if "max_leaves" not in config:
                self.max_leaves = 50
            # "gini", "entropy"
            if "criterion" not in config:
                self.criterion = "gini"
            if "min_score" not in config:
                self.min_score = 0.5
            if "pruning_mccp_alpha" not in config:
                self.pruning_mccp_alpha = 0.0
            if "text_tree" not in config:
                self.text_tree = False
            if "graph_tree" not in config:
                self.graph_tree = False
            if self.graph_tree:
                self.graph_output_file = "marta_dt"
            # False for vertical, True for horizontal
            if "orientation" not in config:
                self.orientation = False
            else:
                self.orientation = self.orientation == "horizontal"

    def export_graph_tree(self):
        dot_data = tree.export_graphviz(
            self.clf,
            out_file=None,
            feature_names=list(self.data.columns),
            filled=True,
            rounded=True,
            leaves_parallel=True,
            impurity=False,
            class_names=self.labels,
            rotate=self.config.orientation,
            label="none",
        )
        graph = graphviz.Source(dot_data)
        graph.render(self.config.graph_output_file)

    def export_text_tree(self) -> None:
        print(tree.export_text(self.clf, feature_names=list(self.data.columns)))

    def __init__(self, config: DTConfig, data: pd.DataFrame, target: pd.Series):
        self.config = config
        self.clf = tree.DecisionTreeClassifier(
            random_state=0,
            max_depth=config.max_depth,
            criterion=config.criterion,
            max_leaf_nodes=config.max_leaves,
            ccp_alpha=config.pruning_mccp_alpha,
        )
        self.data = data
        self.target_data = target
        self.labels = target.values.unique().tolist()
        self.clf = self.clf.fit(self.data.values, target.values)


class Analyzer:
    def parse_arguments(self) -> argparse.Namespace:
        """Parse arguments

        :return: list of arguments (sys.argv)
        :rtype: argparse.Namespace
        """
        parser = argparse.ArgumentParser(
            description="wrapper for analyzing data given a csv"
        )
        required_named = parser.add_argument_group("required named arguments")
        required_named.add_argument(
            "-i", "--input", help="input file name", required=True
        )
        return parser.parse_args()

    def remove_files(self, tmp_files=["___tmp*"]) -> None:
        """Remove temporal files generated

        :param tmp_files: name or names of temporal files to remove, defaults to ["___tmp*"]
        :type tmp_files: list, optional
        """
        for tmp in tmp_files:
            os.system(f"rm {tmp}")

    def preprocess_data(self) -> pd.DataFrame:
        """Process data: filter, normalize and categorize

        :return: Data processed
        :rtype: pandas.DataFrame
        """
        output_file = f"processed_{self.input_file.split('/')[-1]}"
        df = pd.read_csv(self.input_file, comment="#", index_col=False)
        norm_min_max = self.norm_type in ["min_max", "minmax"]
        norm_z_score = self.norm_type in ["z_score", "zscore"]
        ncat = self.ncats
        cat = self.target
        catscale = self.catscale
        if norm_min_max:
            setattr(df, cat, getattr(df, cat) - min(getattr(df, cat)))
            setattr(df, cat, getattr(df, cat) / max(getattr(df, cat)))
        elif norm_z_score:
            # z-score
            setattr(df, cat, np.log(getattr(df, cat)))
            setattr(
                df,
                cat,
                (getattr(df, cat) - np.mean(getattr(df, cat)))
                / np.std(getattr(df, cat)),
            )
        tmp_cat = getattr(df, cat)
        bins = np.linspace(min(getattr(df, cat)), max(getattr(df, cat)), ncat)
        step = bins[1] - bins[0]
        labels = [
            "P-{0}-{1}".format(
                "{0:.3f}".format(float(i / catscale)),
                "{0:.3f}".format(float((i + step) / catscale)),
            )
            for i in bins
        ]
        setattr(df, cat, pd.cut(tmp_cat, ncat, labels=labels))
        self.labels = labels
        for d in self.filter_rows:
            try:
                cond = getattr(df, d) == eval(self.filter_rows[d])
            except TypeError:
                cond = getattr(df, d) == self.filter_rows[d]
            except Exception:
                self.perror("check kernel[prepare_data[rows]]")
            df = df[cond].copy()
        if df.count()[0] == 0:
            self.perror("dataset empty, check constraints in data please!",)
        f_cols = self.filter_cols + [cat]
        df = df[list(f_cols)]
        df.to_csv(output_file, index=False)
        return df

    def train_model(self):
        """
        Train model according to the type of classification algorithm chosen in
        the configuration file.
        """
        self.data_processed = self.preprocess_data()
        if self.class_type == "decisiontree":
            dt = DecisionTree(
                self.dt_cfg,
                self.data_processed[self.filter_cols],
                getattr(self.data_processed, self.target),
            )
            if self.dt_cfg.text_tree:
                dt.export_text_tree()
            if self.dt_cfg.graph_tree:
                dt.export_graph_tree()

    def perror(self, msg: str, exit_code=1) -> None:
        print(f"[FATAL ERROR] {msg}")
        sys.exit(exit_code)

    def dprint(self, msg: str) -> None:
        if self.debug:
            print(f"[DEBUG] {msg}")

    def __init__(self):
        try:
            self.args = self.parse_arguments()
            self.yml_config = self.args.input
            with open(self.yml_config, "r") as ymlfile:
                cfg = yaml.load(ymlfile, Loader=yaml.FullLoader)

            general_cfg = cfg[0]["kernel"]
            self.debug = general_cfg["debug"] if "debug" in general_cfg else False
            self.input_file = general_cfg["input"]
            self.force_replacement = (
                general_cfg["force_replacement"]
                if "force_replacement" in general_cfg.keys()
                else False
            )
            self.output_file = general_cfg["output"]
            self.rm_temp_files = general_cfg["clean"]
            self.print_debug = general_cfg["debug"]

            # prepare_data keys
            prepdata_cfg = general_cfg["prepare_data"]
            self.filter_cols = prepdata_cfg["cols"].split(" ")
            self.filter_rows = (
                prepdata_cfg["rows"] if "rows" in prepdata_cfg.keys() else ""
            )
            self.target = prepdata_cfg["target"]
            self.norm = (
                prepdata_cfg["norm"]["enabled"]
                if "norm" in prepdata_cfg.keys()
                else False
            )
            self.norm_type = prepdata_cfg["norm"]["type"] if self.norm else ""
            self.ncats = int(prepdata_cfg["categories"]["num"])
            if self.ncats < 1:
                raise ValueError(
                    "categories[num]", f"{self.ncats}", "value must be greater than one"
                )
            self.catscale = eval(prepdata_cfg["categories"]["scale_factor"])
            self.cattype = prepdata_cfg["categories"]["type"]

            # classification keys
            classification_cfg = general_cfg["classification"]
            self.class_type = classification_cfg["type"]
            if self.class_type == "decisiontree":
                self.dt_cfg = DecisionTree.DTConfig(classification_cfg["dt_settings"])
            elif self.class_type == "randomforest":
                # TODO: implement random forest classification
                pass
            else:
                raise ValueError(
                    "classification[type]",
                    self.class_type,
                    "unknown classification algorithm: try 'decisiontree' or 'randomforest'",
                )

            if self.rm_temp_files:
                self.remove_files()
        except KeyError as K:
            self.perror(f"key {K} missing in configuration file")
        except TypeError as T:
            self.perror(f"key {T} wrong type")
        except ValueError as V:
            key, value, msg = V.args
            self.perror(f"{key} = {value}, {msg}")
        except SyntaxError as S:
            self.perror(f"syntax error in {S}")
        except NameError as N:
            self.perror(f"{N}")
        except Exception as E:
            self.perror(f"something went wrong: {E}")


if __name__ == "__main__":
    analyzer = Analyzer()
    analyzer.train_model()

