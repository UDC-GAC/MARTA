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
import os

# Third-party libraries
import numpy as np
import pandas as pd
import yaml

# Local imports
from marta.analyzer.config import parse_options
from marta.analyzer.decision_tree import DecisionTree
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

    def remove_files(self, tmp_files=["___tmp*"]) -> None:
        """Remove temporal files generated

        :param tmp_files: name or names of temporal files to remove, defaults to ["___tmp*"]
        :type tmp_files: list, optional
        """
        for tmp in tmp_files:
            os.remove(tmp)

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
                perror("check kernel[prepare_data[rows]]")
            df = df[cond].copy()
        if df.count()[0] == 0:
            perror("dataset empty, check constraints in data please!",)
        f_cols = self.filter_cols + [cat]
        df = df[list(f_cols)]
        df.to_csv(output_file, index=False)
        return df

    def train_model(self) -> None:
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
            dt.get_summary()
        elif self.class_type == "randomforest":
            raise TypeError
        else:
            raise TypeError

    def __init__(self, args):
        self.args = self.parse_arguments(args)
        yaml_config = self.args.input[0]
        try:
            from yaml import CLoader as Loader
        except ImportError:
            from yaml import Loader

        try:
            with open(yaml_config, "r") as ymlfile:
                cfg = yaml.load(ymlfile, Loader=Loader)
        except FileNotFoundError:
            perror("Configuration file not found")
        except Exception:
            perror("Unknown error when opening configuration file.")

        parsed_config = parse_options(cfg)
        for key in parsed_config:
            setattr(self, key, parsed_config[key])
        try:
            self.train_model()
        except ValueError:
            perror("Check your dimensions are numeric")
        except Exception:
            perror("Something went wrong")
