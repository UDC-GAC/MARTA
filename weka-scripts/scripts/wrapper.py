#!/usr/bin/env python
# -*- coding: utf-8 -*-
# File              : wrapper.py
# Author            : Marcos Horro <marcos.horro@udc.gal>
# Date              : Xov 31 Out 2019 09:56:07 MDT
# Last Modified Date: Mar 05 Nov 2019 10:59:38 MST
# Last Modified By  : Marcos Horro <marcos.horro@udc.gal>
# wrapper.py
# Copyright (c) 2019 Computer Architecture Group, Universidade da Coruña
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
# Authors: Marcos Horro

import os
import itertools as it
import argparse
from utils.utilities import StoreDictKeyPair
from utils.utilities import prRed
from utils.utilities import prGreen

##################################################
# parsing arguments
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
parser.add_argument('-c', '--columns', metavar='col', type=str, nargs='+',
                    help='columns we are interested to filter')
args = parser.parse_args()

##################################################
# parsing all the arguments
INPUT_FILE = "exec_asm_full_filtered.csv"
OUTPUT_FILE = "testing.arff"
NFOLDS = args.nfolds
MINLEAF = args.minleaf
COLS = args.columns
NORM = ""
if args.norm:
    NORM = "--norm"
ROWS = args.rows
PRED = args.pred
NCATS = int(args.ncats)
COLS += [PRED]
FILTER_ROWS = ""
if ROWS != None:
    FILTER_ROWS = "-r "
    for d in ROWS:
        FILTER_ROWS += "%s=%s " % (str(d), str(ROWS[d]))
FILTER_COLS = ""
for c in COLS:
    FILTER_COLS = FILTER_COLS + " " + c

SUMM_FILE = "___tmp__SUMM_FILE.txt"
os.system("echo \"\" > %s" % (SUMM_FILE))

##################################################
# executing experiments
prGreen("[wrapper] executing wrapper...")
ret = os.system("python3 prepare_data.py -i %s -o %s"
                " %s -c %s --nfolds=%s --minleaf=%s --pred=%s --ncats=%s"
                " %s --rmtemp" %
                (INPUT_FILE, OUTPUT_FILE, FILTER_ROWS,
                 FILTER_COLS, NFOLDS,
                 MINLEAF, PRED, str(NCATS), NORM))
if (ret != 0):
    prRed("[wrapper] Something went wrong!")
result_file = "results/model_learn_stats_%s_folds%s_leaf%s" % (
    str(PRED), str(NFOLDS), str(MINLEAF))

##################################################
# parsing results
os.system("cp results/exp_%s_all_REPTree_%s_%s/model_learn_stats.txt"
          " %s" %
          (OUTPUT_FILE.split(".")[0], MINLEAF, NFOLDS, result_file))
os.system("grep -m 1 -n \"Correctly\" %s /dev/null >> %s" %
          (result_file, SUMM_FILE))
os.system("grep -m 1 -n \"Correlation coefficient\" %s /dev/null >> %s" %
          (result_file, SUMM_FILE))
os.system("grep -m 1 -n \"Size of the tree\" %s /dev/null >> %s" %
          (result_file, SUMM_FILE))

##################################################
# results obtained
prGreen("[wrapper] results")
os.system("cat %s" % SUMM_FILE)
prGreen("[wrapper] finished! cleaning temp files...")

##################################################
# remove tmp files
os.system("rm %s" % SUMM_FILE)
