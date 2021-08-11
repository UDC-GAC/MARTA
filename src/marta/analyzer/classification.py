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

# -*- coding: utf-8 -*-

# Third-party libraries
import graphviz
import pandas as pd
from sklearn import tree

# Local imports
from marta.analyzer.config import DTConfig, decision_tree_synonyms
from marta.utils.marta_utilities import CaptureOutput


class Classification:
    def get_summary(self):
        pass

    def perform_analysis(self):
        pass

    def predict_value(self, predict_value: str):
        pass


class ClassificationFactory:
    @staticmethod
    def get_class(type_clf: str, config: dict, *args) -> Classification:
        if type_clf in decision_tree_synonyms:
            dt_cfg = DTConfig(config)
            return DecisionTree(dt_cfg, *args)
        else:
            raise ValueError(f"No classification class {type_clf}")


class DecisionTree(Classification):
    def export_graph_tree(self, output_path="") -> None:
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
            rotate=False,
            label="none",
        )
        graph = graphviz.Source(dot_data)
        graph_output_file = "marta_analyzer_dt"
        if output_path != "":
            graph_output_file = f"{output_path}/"
        graph.render(graph_output_file)

    def export_text_tree(self) -> None:
        """Export the decision tree as text.
        """
        print(tree.export_text(self.clf, feature_names=list(self.data.columns)))

    def perf_measure(self, y_actual: pd.Series, y_hat: pd.Series):
        """Get performance metrics: true positive, true negative, false
        positive and false negative

        :param y_actual: Real data
        :type y_actual: pd.Series
        :param y_hat: Data categorized
        :type y_hat: pd.Series
        :return: True positives, True negatives, false negatives, false positives
        :rtype: tuple
        """
        TP = 0
        FP = 0
        TN = 0
        FN = 0

        for i in range(len(y_hat)):
            if y_actual[i] == y_hat[i] == 1:
                TP += 1
            if y_hat[i] == 1 and y_actual[i] != y_hat[i]:
                FP += 1
            if y_actual[i] == y_hat[i] == 0:
                TN += 1
            if y_hat[i] == 0 and y_actual[i] != y_hat[i]:
                FN += 1

        return (TP, FP, TN, FN)

    def get_summary(self) -> None:
        """Print a summary of the metrics in the decision tree.
        """
        score = self.clf.score(self.data.values, self.target_data.values)
        print(f"Type:                  decision tree")
        print(f"Number of leaves:      {self.clf.get_n_leaves():4d}".format())
        print(f"Depth of tree:         {self.clf.get_depth():4d}".format())
        print(f"Mean accuracy (score): {score:7.2f}".format())

        # FIXME: this only has meaning if we are going to test our model
        # TP, FP, TN, FN = self.perf_measure(self.data.values, self.target_data.values)
        # print(f"True positives:        {TP:3d}".format())
        # print(f"True negatives:        {TN:3d}".format())
        # print(f"False positives:       {FP:3d}".format())
        # print(f"False negatives:       {FN:3d}".format())

    def perform_analysis(self, output_path=""):
        print("Classification analysis:")
        print("========================")
        self.get_summary()
        if self.config.text_tree:
            print("* Decision tree generated:\n")
            with CaptureOutput() as output:
                self.export_text_tree()
            if output_path == "":
                for line in output:
                    print(f"\t{line}")
            else:
                output_file = f"{output_path}/"
                with open(output_file, "w") as f:
                    f.writelines(output)
        if self.config.graph_tree:
            print(f"Saving graphic decision tree in file {output_path}\n")
            self.export_graph_tree(output_path)

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