import os
import argparse
import pandas as pd
import numpy as np
import sci
from math import ceil
from common import weka_cmd
from common.weka_cmd import path_weka
from common.utilities import StoreDictKeyPair
from common.utilities import pr_debug
from common.utilities import pr_col
from common.utilities import colors as c

path_root = os.getcwd() + "/"
path_data = path_root + "data"
path_res = path_root + "results"
nsets = 0
force_replacement = True
algorithms = ["reptree"]
min_obj = [1]
max_leaf = [3]
norm = False


class PreProcess:
    def parse_arguments(self):
        parser = argparse.ArgumentParser(
            description="convert from csv to arff (generic format), creates training and testing sets. allows the inclusion of custom scripts (no need to be python) for preparing data according to experiments need. todo: options for selecting categorical value. note: need to have weka installed."
        )
        parser.add_argument(
            "-p", "--pred", help="dimension to predict", default="flopss"
        )
        parser.add_argument(
            "-nc",
            "--ncats",
            help="number of categories of dimension to predict,"
            " categories are created uniformly in pandas",
            default=10,
        )
        parser.add_argument(
            "-cs",
            "--catscale",
            help="scale factor when creating categories, not relevant"
            " if dimension is not numeric",
            default=1,
        )
        parser.add_argument(
            "-nv",
            "--norm",
            action="store_true",
            help="normalize predicted dimension (min-max norm i.e."
            " values in range [0-1])",
            default=False,
        )
        parser.add_argument(
            "-rm",
            "--rmtemp",
            action="store_true",
            help="clean directory of temp files (default=False)",
            default=False,
        )
        parser.add_argument(
            "-f",
            "--force",
            action="store_true",
            help="force replacement files even if they exist (default=False)",
            default=False,
        )
        parser.add_argument(
            "-r",
            "--rows",
            dest="rows",
            action=StoreDictKeyPair,
            help="filtering rows as a dictionary. e.g. -r i=0 j=0",
            nargs="+",
            metavar="key=val",
        )
        parser.add_argument(
            "-dt",
            "--dtalg",
            help="decision tree algorithm, e.g. reptree, j48",
            default="reptree",
        )
        parser.add_argument(
            "-dtp",
            "--dtparams",
            dest="dtparams",
            action=StoreDictKeyPair,
            help="decision tree parameters",
            nargs="*",
            metavar="key=val",
        )
        parser.add_argument(
            "-dto", "--dtopts", dest="dtopts", help="options for ftalgo"
        )
        required_named = parser.add_argument_group("required named arguments")
        required_named.add_argument(
            "-i", "--input", help="input file name", required=True
        )
        required_named.add_argument(
            "-o", "--output", help="output file name", required=True
        )
        required_named.add_argument(
            "-c",
            "--columns",
            metavar="col",
            type=str,
            nargs="+",
            help="columns we are interested to filter",
        )
        return parser.parse_args()

    def preprocess_data(self):
        output_file = f"___tmp_{self.input_file.split('/')[-1]}"
        df = pd.read_csv(self.input_file, comment="#", index_col=False)
        norm_min_max = True
        norm_z_score = False
        ncat = self.ncats
        cat = self.pred
        catscale = self.catscale
        if norm:
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
        tmp = df
        if ncat > 0:
            tmp_cat = getattr(tmp, cat)
            bins = np.linspace(min(getattr(df, cat)), max(getattr(df, cat)), ncat + 1)
            step = bins[1] - bins[0]
            labels = [
                "I-{0}-{1}".format(
                    "{0:.3f}".format(float(i / catscale)),
                    "{0:.3f}".format(float((i + step) / catscale)),
                )
                for i in bins
            ]
            setattr(tmp, cat, pd.cut(tmp_cat, bins, labels=labels[:-1]))
        for d in self.rows:
            if d == None:
                continue
            for k, v in d.items():
                cond = getattr(tmp, k) == v
                tmp = tmp[cond].copy()
        if tmp.count()[0] == 0:
            pr_col(
                c.fg.red, "[error] dataset empty! revise constraints in data please!"
            )
            exit(-1)
        f_cols = self.cols + [cat]
        tmp = tmp[list(f_cols)]
        tmp.to_csv(output_file, index=False)
        return tmp

    def __init__(self):
        args = self.parse_arguments()
        self.force_replacement = args.force
        self.input_file = args.input
        self.output_file = args.output
        self.columns = args.columns
        self.rows = args.rows
        self.pred = args.pred
        self.ncats = int(args.ncats)
        self.catscale = float(args.catscale)
        self.norm = args.norm
        self.dtalg = args.dtalg
        self.dtparams = args.dtparams
        self.dtopts = args.dtopts
        self.processed_df = self.preprocess_data()
        X = self.processed_df.values()

