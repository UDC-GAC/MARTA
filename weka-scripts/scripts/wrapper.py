#!/usr/bin/env python
# -*- coding: utf-8 -*-
# File              : wrapper.py
# Author            : Marcos Horro <marcos.horro@udc.gal>
# Date              : Xov 31 Out 2019 09:56:07 MDT
# Last Modified Date: Xov 31 Out 2019 14:36:50 MDT
# Last Modified By  : Marcos Horro <marcos.horro@udc.gal>

import os
import itertools as it
import argparse

# disgusting wrapper


class StoreDictKeyPair(argparse.Action):
    def __init__(self, option_strings, dest, nargs=None, **kwargs):
        self._nargs = nargs
        super(StoreDictKeyPair, self).__init__(
            option_strings, dest, nargs=nargs, **kwargs)

    def __call__(self, parser, namespace, values, option_string=None):
        my_dict = {}
        for kv in values:
            k, v = kv.split("=")
            my_dict[k] = int(v)
        setattr(namespace, self.dest, my_dict)


stride = range(1, 2)
cols = 'I J It Jt Iters Jters NELEMS '

parser = argparse.ArgumentParser(
    description='Wrapper for prepare data. Quite ugly tho...')
parser.add_argument('-r', '--rows', dest="rows", action=StoreDictKeyPair,
                    help="filtering rows as a dictionary. E.g. -r I=0 J=0",
                    nargs="+", metavar="KEY=VAL")
parser.add_argument('-p', '--pred',  # action='store_const',
                    help='dimension to predict', default="FLOPSs")
parser.add_argument('-nc', '--ncats',  # action='store_const',
                    help='number of categories of dimension to predict',
                    default=10)
parser.add_argument('-ml', '--minleaf',  # action='store_const',
                    help='number of folds', default=1)
parser.add_argument('-nf', '--nfolds',  # action='store_cont',
                    help='number of folds', default=3)
parser.add_argument('-nv', '--norm', action='store_true',
                    help='normalize predicted dimension (i.e. [0-1])',
                    default=False)
args = parser.parse_args()
INPUT_FILE = "../data/CSV/exec_reg_model.csv"
OUTPUT_FILE = "testing.arff"
nfolds = args.nfolds
minleaf = args.minleaf
if args.norm:
    norm = "--norm"
else:
    norm = ""
ROWS = args.rows
PRED = args.pred
NCATS = int(args.ncats)
cols += str(PRED)
filter_rows = ""
if ROWS != None:
    for d in ROWS:
        filter_rows += "%s=%s " % (str(d), str(ROWS[d]))

summary_file = "summary_file.txt"
os.system("echo \"\" > %s" % (summary_file))
for Is, Js in it.product(stride, stride):
    print("[wrapper] executing for strides Is %2d Js %2d" % (Is, Js))
    ret = os.system("python3 prepare_data.py -i %s -o %s -r Is=%s Js=%s"
                    " %s -c %s --nfolds=%s --minleaf=%s --pred=%s --ncats=%s"
                    " %s " %
                    (INPUT_FILE, OUTPUT_FILE, str(Is), str(Js), filter_rows, cols, nfolds,
                     minleaf, PRED, str(NCATS), norm))
    if (ret != 0):
        print("[wrapper] Something went wrong!")
    result_file = "results/model_learn_stats_%s_is%s_js%s_folds%s_leaf%s" % (
        str(PRED), str(Is), str(Js), str(nfolds), str(minleaf))
    os.system("cp results/exp_%s_all_REPTree_%s_%s/model_learn_stats.txt"
              " %s" %
              (OUTPUT_FILE.split(".")[0], minleaf, nfolds, result_file))
    os.system("grep -m 1 -n \"Correctly\" %s /dev/null >> %s" %
              (result_file, summary_file))

os.system("cat %s" % summary_file)
