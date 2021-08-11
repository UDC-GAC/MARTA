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

# Standard library
import argparse

# Third-party libraries
import numpy as np
import pandas as pd

# Local imports
from marta.analyzer.config import parse_options, load_yaml_file
from marta.analyzer.feature_importance import FeatureImportanceFactory
from marta.analyzer.classification import ClassificationFactory
from marta.analyzer.processing import normalize_data, categorize_target_dimension
from marta.utils.marta_utilities import perror


class Analyzer:
    def parse_arguments(self, args: list) -> argparse.Namespace:
        """Parse arguments

        :return: list of arguments (sys.argv)
        :rtype: argparse.Namespace
        """
        parser = argparse.ArgumentParser(
            description="wrapper for analyzing data given a csv"
        )
        required_named = parser.add_argument_group("required named arguments")
        required_named.add_argument(
            "input",
            metavar="input",
            type=str,
            nargs=1,
            help="input configuration file",
        )

        return parser.parse_args(args)

    def preprocess_data(self) -> pd.DataFrame:
        """Process data: filter, normalize and categorize

        :return: Data processed
        :rtype: pandas.DataFrame
        """
        output_file = f"{self.output_path}/data_processed.csv"
        df = pd.read_csv(self.input_file, comment="#", index_col=False)
        target_value = self.target
        df = normalize_data(df, self.norm, target_value)
        df, labels = categorize_target_dimension(
            df, target_value, self.ncats, self.catscale
        )
        self.labels = labels
        for d in self.filter_rows:
            try:
                cond = getattr(df, d) == eval(self.filter_rows[d])
            except TypeError:
                cond = getattr(df, d) == self.filter_rows[d]
            except Exception:
                perror("check kernel[prepare_data[rows]], there is something wrong.")
            df = df[cond].copy()
        if df.count()[0] == 0:
            perror("dataset empty, check constraints in data please!",)
        f_cols = self.filter_cols + [target_value]
        df = df[list(f_cols)]
        df.to_csv(output_file, index=False)
        return df

    def perform_analysis(self) -> None:
        """
        Train model according to the type of classification algorithm chosen in
        the configuration file.
        """

        # Ad-hoc preprocessing data
        self.data_processed = self.preprocess_data()

        # Classification
        clf = ClassificationFactory.get_class(
            self.clf_type,
            self.clf_cfg,
            self.data_processed[self.filter_cols],
            getattr(self.data_processed, self.target),
        )
        clf.perform_analysis()

        # Feature importance analysis
        feat = FeatureImportanceFactory.get_class(
            self.feat_type,
            self.feat_cfg,
            self.data_processed[self.filter_cols],
            getattr(self.data_processed, self.target),
            self.filter_cols,
        )
        feat.perform_analysis()

    def __init__(self, args):
        self.args = self.parse_arguments(args)
        parsed_config = parse_options(load_yaml_file(self.args.input[0]))
        for key in parsed_config:
            setattr(self, key, parsed_config[key])
        self.perform_analysis()
