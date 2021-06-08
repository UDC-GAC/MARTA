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

import graphviz
import pandas as pd
from sklearn import tree


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

    def export_graph_tree(self) -> None:
        """Export the decision tree as a .pdf file.
        """
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
        """Export the decision tree as text.
        """
        print(tree.export_text(self.clf, feature_names=list(self.data.columns)))

    def get_summary(self) -> None:
        """Print a summary of the metrics in the decision tree.
        """
        score = self.clf.score(self.data.values, self.target_data.values)
        print(f"Mean accuracy (score): {score:6.2f}".format())
        print(f"Number of leaves:      {self.clf.get_n_leaves():3d}".format())
        print(f"Depth of tree:         {self.clf.get_depth():3d}".format())

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
        self.clf = self.clf.fit(self.data.values, self.target_data.values)
