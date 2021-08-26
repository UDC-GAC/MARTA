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

# Standard libraries
import os

# Third-party libraries
import graphviz
import pandas as pd
from sklearn import tree
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import confusion_matrix, ConfusionMatrixDisplay
import matplotlib.pyplot as plt

# Local imports
import marta.analyzer._custom_decision_tree  # this is needed for overwritting a funtion in sklearn
from marta.analyzer.config import DTConfig, decision_tree_synonyms
from marta.utils.marta_utilities import CaptureOutput, pinfo, pwarning


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
            proportion=self.config.proportion,
            class_names=self.labels,
            rotate=self.config.rotate,
            label="none",
        )
        graph = graphviz.Source(dot_data)
        graph_output_file = "graph_decision_tree"
        if output_path != "":
            graph_output_file = f"{output_path}/graph_decision_tree"
        graph.render(graph_output_file)
        if output_path != "":
            os.remove(f"{output_path}/graph_decision_tree")
        else:
            os.remove(f"graph_decision_tree")

    def export_text_tree(self) -> None:
        """Export the decision tree as text.
        """
        print(tree.export_text(self.clf, feature_names=list(self.data.columns)))

    def get_summary(self, output_path="") -> None:
        """Print a summary of the metrics in the decision tree.
        """
        score_dt = self.clf.score(self.var_test, self.res_test)
        score_kneigh = self.kneigh.score(self.var_test, self.res_test)
        print(f"Type:                       decision tree and K-Neighbors")
        print(f"Number of leaves:        {self.clf.get_n_leaves():4d}".format())
        print(f"Depth of the tree:       {self.clf.get_depth():4d}".format())
        print(f"Accuracy decision tree:  {score_dt:8.3f}".format())
        print(f"Accuracy K-Neighbors:    {score_kneigh:8.3f}".format())

        predictions = self.clf.predict(self.data.values)
        missclassified = 0
        for prediction, label in zip(predictions, self.target_data.values):
            if prediction != label:
                missclassified += 1
        if missclassified:
            pwarning(
                f"Missclassified data: {missclassified}/{len(self.data.values)} ({1-score_dt:.3f})".format()
            )

        print("Confusion matrix:")
        print("=================")
        cm = confusion_matrix(self.target_data.values, predictions, labels=self.labels)
        print(cm)
        print("Categories:")
        print(self.labels)
        disp = ConfusionMatrixDisplay(confusion_matrix=cm, display_labels=self.labels)
        # plt.show()
        file_conf_matrix = f"{output_path}/conf_matrix.pdf"
        fig, ax = plt.subplots()
        disp.plot(ax=ax, xticks_rotation="vertical")
        fig.tight_layout()
        fig.savefig(file_conf_matrix, format="pdf")

    def perform_analysis(self, output_path="") -> None:
        print("Classification analysis:")
        print("========================")
        self.get_summary(output_path)
        if self.config.text_tree:
            print("\n-> Decision tree generated:\n")
            with CaptureOutput() as output:
                self.export_text_tree()
            for line in output:
                print(f"\t{line}")
            if output_path != "":
                pinfo(f"Saving text decision tree in directory '{output_path}'")
                output_file = f"{output_path}/text_decision_tree"
                with open(output_file, "w") as f:
                    f.write("Decision tree generated:\n")
                    f.write("========================\n")
                    for line in output:
                        f.write(f"{line}\n")
        if self.config.graph_tree:
            pinfo(f"Saving graphic decision tree in directory '{output_path}'")
            self.export_graph_tree(output_path)
        print("\n")

    def __init__(self, config: DTConfig, data: pd.DataFrame, target: pd.Series):
        self.config = config
        self.clf = tree.DecisionTreeClassifier(
            random_state=config.random_state,
            splitter=config.splitter,
            criterion=config.criterion,
            max_depth=config.max_depth,
            max_leaf_nodes=config.max_leaves,
            ccp_alpha=config.pruning_mccp_alpha,
        )
        self.data = data
        self.target_data = target
        self.labels = target.values.unique().tolist()
        self.var_train, self.var_test, self.res_train, self.res_test = train_test_split(
            self.data.values, self.target_data.values, test_size=0.2
        )
        self.clf = self.clf.fit(self.var_train, self.res_train)
        self.kneigh = KNeighborsClassifier(n_neighbors=250).fit(
            self.var_train, self.res_train
        )
