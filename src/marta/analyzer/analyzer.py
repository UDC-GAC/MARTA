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

# Standard library
import argparse
import sys

# Third-party libraries
import pandas as pd

# Local imports
from marta.analyzer.config import parse_options, load_yaml_file
from marta.analyzer.feature_importance import FeatureImportanceFactory
from marta.analyzer.classification import ClassificationFactory
from marta.analyzer.plotting import plot_data
from marta.analyzer.processing import (
    normalize_data,
    categorize_target_dimension,
    column_strings_to_int,
)
from marta.utils.marta_utilities import (
    perror,
    pinfo,
    dump_config_file,
    pwarning,
    print_version,
)


class Analyzer:
    def parse_arguments(self, args: list) -> argparse.Namespace:
        """Parse arguments

        :return: list of arguments (sys.argv)
        :rtype: argparse.Namespace
        """
        parser = argparse.ArgumentParser(
            description="wrapper for analyzing data given a csv"
        )
        required_input = 1
        if (
            ("-v" in args)
            or ("--version" in args)
            or ("-dump" in args)
            or ("--dump-config-file" in args)
            or ("-h" in args)
            or ("--help" in args)
        ):
            required_input = "?"
        required_named = parser.add_argument_group("required named arguments")
        required_named.add_argument(
            "input",
            metavar="input",
            type=str,
            nargs=required_input,
            help="input configuration file",
        )

        # Optional arguments
        optional_named = parser.add_argument_group("optional named arguments")
        optional_named.add_argument(
            "-q", "--quiet", action="store_true", help="quiet execution", required=False
        )

        optional_named.add_argument(
            "-v",
            "--version",
            action="store_true",
            help="display version and quit",
            required=False,
        )

        optional_named.add_argument(
            "-dump",
            "--dump-config-file",
            action="store_true",
            help="dump a sample configuration file with all needed files for analyzer to work properly",
            required=False,
        )

        return parser.parse_args(args)

    def preprocess_data(self) -> pd.DataFrame:
        """Process data: filter, normalize and categorize

        :return: Data processed
        :rtype: pandas.DataFrame
        """
        output_file = f"{self.output_path}/{self.input_file_name}_data_processed.csv"
        df = pd.read_csv(self.input_file, comment="#", index_col=False)
        self.raw_data = df.copy()
        target_value = self.target
        for d in self.filter_rows:
            try:
                cond = getattr(df, d) == eval(self.filter_rows[d])
            except NameError:
                cond = getattr(df, d) == self.filter_rows[d]
            except TypeError:
                cond = getattr(df, d) == self.filter_rows[d]
            except Exception as E:
                try:
                    cond = eval(f"df['{d}']{self.filter_rows[d]}")
                except Exception as E:
                    perror(
                        f"check kernel[prepare_data[rows]], there is something wrong: {E}"
                    )
            df = df[cond].copy()
        if df.count()[0] == 0:
            perror("dataset empty, check constraints in data please!")

        if target_value.lower() == "tsc":
            if "overhead_loop" in df.columns:
                df[target_value] -= df["overhead_loop"]

        df = normalize_data(df, self.norm, target_value)
        new_cat = []
        if self.categories_enabled:
            df, labels = categorize_target_dimension(
                df,
                target_value,
                self.ncats,
                self.catscale,
                self.mode,
                self.grid_search,
                self.custom_params,
                self.bandwidth,
                self.bandwidth_type,
                self.kernel,
            )
            new_cat = [f"{target_value}_cat"]
        else:
            import numpy as np

            labels = np.unique(df[target_value].values)
        self.labels = labels
        f_cols = self.filter_cols + [target_value] + new_cat
        df, self.encoders = column_strings_to_int(df, self.filter_cols)
        df = df[list(f_cols)]
        df.to_csv(output_file, index=False)
        pinfo(f"Saving processed data in '{output_file}'")
        return df

    def perform_analysis(self) -> None:
        """
        Train model according to the type of classification algorithm chosen in
        the configuration file.
        """

        # Ad-hoc preprocessing data
        self.data_processed = self.preprocess_data()

        # Classification
        if self.clf_enabled:
            clf = ClassificationFactory.get_class(
                self.clf_type,
                self.clf_cfg,
                self.data_processed,
                self.filter_cols,
                self.target,
                self.encoders,
            )
            clf.labels = self.labels
            clf.perform_analysis(output_path=self.output_path)
        else:
            pwarning("Classification analysis disabled")

        # Feature importance analysis
        if self.feat_enabled and not clf.continuous:
            feat = FeatureImportanceFactory.get_class(
                self.feat_type,
                self.feat_cfg,
                self.data_processed,
                self.filter_cols,
                self.target,
            )
            feat.perform_analysis(output_path=self.output_path)
        else:
            pwarning("Feature importance analysis disabled")

        # Plotting
        if len(self.plot_cfg) > 0:
            for plt in self.plot_cfg:
                if not self.plot_enabled[plt]:
                    pwarning(f"Plotting disabled for {plt}")
                    continue
                if self.plot_cfg[plt].data == "raw":
                    plot_data(
                        self.raw_data,
                        self.plot_cfg[plt],
                        f"{self.output_path}/plot_raw_data_{self.plot_cfg[plt].type}",
                    )
                else:
                    plot_data(
                        self.data_processed,
                        self.plot_cfg[plt],
                        f"{self.output_path}/plot_processed_data_{self.plot_cfg[plt].type}",
                    )
        else:
            pwarning("Nothing to plot")

    def __init__(self, args):
        self.args = self.parse_arguments(args)
        if not self.args.quiet or self.args.version:
            print_version("Analyzer")
            if self.args.version:
                sys.exit(0)

        if self.args.dump_config_file:
            dump_config_file("analyzer/template.yml")
            sys.exit(0)

        parsed_config = parse_options(load_yaml_file(self.args.input[0]))
        for key in parsed_config:
            setattr(self, key, parsed_config[key])
        self.perform_analysis()
