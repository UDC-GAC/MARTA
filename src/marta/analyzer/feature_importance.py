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
# Third-party libraries
import numpy as np
import matplotlib
import matplotlib.pyplot as plt
import pandas as pd
from sklearn.ensemble import RandomForestClassifier
from sklearn.inspection import permutation_importance
from sklearn.model_selection import train_test_split
import numpy as np

# Local imports
from marta.analyzer.config import RFConfig, random_forest_synonyms
from marta.utils.marta_utilities import pinfo


class FeatureImportance:
    def get_summary(self):
        pass

    def perform_analysis(self):
        pass


class FeatureImportanceFactory:
    @staticmethod
    def get_class(type_clf: str, config: dict, *args) -> FeatureImportance:
        if type_clf in random_forest_synonyms:
            rf_cfg = RFConfig(config)
            return RandomForest(rf_cfg, *args)
        else:
            raise ValueError(f"No classification class {type_clf}")


class RandomForest(FeatureImportance):
    def get_feat_importance_mean_decrease(self) -> matplotlib.figure.Figure:
        importances = self.forest.feature_importances_
        std = np.std(
            [tree.feature_importances_ for tree in self.forest.estimators_], axis=0
        )
        forest_importances = pd.Series(importances, index=self.feature_names)
        fig, ax = plt.subplots()
        forest_importances.plot.bar(yerr=std, ax=ax)
        ax.set_title("Feature importances using MDI")
        ax.set_ylabel("Mean decrease in impurity")
        fig.tight_layout()
        return fig

    def get_feat_importance_feat_permutation(self) -> matplotlib.figure.Figure:
        result = permutation_importance(
            self.forest,
            self.var_test,
            self.res_test,
            n_repeats=10,
            random_state=42,
            n_jobs=-1,
        )
        forest_importances = pd.Series(
            result.importances_mean, index=self.feature_names
        )
        fig, ax = plt.subplots()
        forest_importances.plot.bar(yerr=result.importances_std, ax=ax)
        ax.set_title("Feature importances using permutation on full model")
        ax.set_ylabel("Mean accuracy decrease")
        fig.tight_layout()
        return fig

    def get_feature_importance(self) -> np.ndarray:
        return self.forest.feature_importances_

    def get_feature_importance_labeled(self) -> pd.Series:
        return pd.Series(self.get_feature_importance(), index=self.feature_names)

    def perform_analysis(self, output_path="") -> None:
        print("Feature importance analysis:")
        print("============================")
        print(self.get_feature_importance_labeled())

        print(
            f"\nAccuracy: {self.forest.score(self.var_test, self.res_test):7.3f}\n".format()
        )

        pinfo(
            f"Saving plot for feature importance based on mean decrease in impurity in '{output_path}/mean_decrease.png'"
        )
        fig = self.get_feat_importance_mean_decrease()
        file_mean_decrease = f"{output_path}/mean_decrease.pdf"
        fig.savefig(file_mean_decrease, format="pdf")
        pinfo(
            f"Saving plot for feature importance based on feature permutation in '{output_path}/permutation.png'"
        )
        fig = self.get_feat_importance_feat_permutation()
        file_perm = f"{output_path}/permutation.pdf"
        fig.savefig(file_perm, format="pdf")

    def __init__(
        self,
        config: RFConfig,
        data: pd.DataFrame,
        target: pd.Series,
        feature_names: list,
    ):
        self.config = config
        self.forest = RandomForestClassifier(
            n_estimators=self.config.n_estimators,
            criterion=self.config.criterion,
            max_depth=self.config.max_depth,
            min_samples_split=self.config.min_samples_split,
            min_samples_leaf=self.config.min_samples_leaf,
            n_jobs=self.config.n_jobs,
            random_state=self.config.random_state,
        )
        self.feature_names = feature_names
        self.data = data
        self.target_data = target
        self.labels = np.unique(target.values).tolist()
        self.var_train, self.var_test, self.res_train, self.res_test = train_test_split(
            self.data.values, self.target_data.values, test_size=0.2
        )
        self.forest = self.forest.fit(self.var_train, self.res_train)
