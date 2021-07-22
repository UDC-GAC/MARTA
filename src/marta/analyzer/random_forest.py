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

import pandas as pd
from sklearn.ensemble import RandomForestClassifier


class RandomForest:
    class RFConfig:
        def __init__(self, config: dict) -> None:
            for key in config:
                setattr(self, key, config[key])

            if "n_estimators" not in config:
                self.n_estimators = 100
            if "criterion" not in config:
                self.criterion = "gini"
            if "max_depth" not in config:
                self.max_depth = 10
            if "min_samples_split" not in config:
                self.min_samples_split = 2
            if "min_samples_leaf" not in config:
                self.min_samples_leaf = 1
            if "n_jobs" not in config:
                self.n_jobs = 1
            if "random_state" not in config:
                self.random_state = None

    def __init__(self, config: RFConfig, data: pd.DataFrame, target: pd.Series):
        self.config = config
        self.clf = RandomForestClassifier(
            n_estimators=self.config.n_estimators,
            criterion=self.config.criterion,
            max_depth=self.config.max_depth,
            min_samples_split=self.config.min_samples_split,
            min_samples_leaf=self.config.min_samples_leaf,
            n_jobs=self.config.n_jobs,
            random_state=self.config.random_state,
        )
        self.data = data
        self.target_data = target
        self.labels = target.values.unique().tolist()
        self.clf = self.clf.fit(self.data.values, self.target_data.values)
