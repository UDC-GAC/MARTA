#!/usr/bin/env python
# -*- coding: utf-8 -*-
# File              : wrapper.py
# Author            : Marcos Horro <marcos.horro@udc.gal>
# Date              : Xov 31 Out 2019 09:56:07 MDT
# Last Modified Date: Mér 06 Nov 2019 17:28:24 MST
# Last Modified By  : Marcos Horro <marcos.horro@udc.gal>
#
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

import yaml
import os
import itertools as it
import argparse
from utils.utilities import StoreDictKeyPair
from utils.utilities import prRed
from utils.utilities import prGreen
from utils.utilities import grep_file2file
from parse_tree import REPTree

##################################################
# parsing arguments
parser = argparse.ArgumentParser(
    description='Wrapper for preparing data given a CSV')
requiredNamed = parser.add_argument_group('required named arguments')
requiredNamed.add_argument(
    '-i', '--input', help='input file name', required=True)
args = parser.parse_args()

##################################################
# parsing all the arguments from the config.yml
YML_CONFIG = args.input
with open(YML_CONFIG, 'r') as ymlfile:
    cfg = yaml.load(ymlfile)

# files
files_cfg = cfg[0]['files']
INPUT_FILE = files_cfg['input']
OUTPUT_FILE = files_cfg['output']
FORCE_REPLACEMENT = files_cfg['overwrite']
RM_TEMP_FILES = files_cfg['clean']
# prepare data
prepdata_cfg = cfg[1]['prepare_data']
FILTER_COLS = prepdata_cfg['cols']
FILTER_ROWS = prepdata_cfg['rows']
PRED = prepdata_cfg['pred']
MINLEAF = prepdata_cfg['dt_params']['minleaf']
NFOLDS = prepdata_cfg['dt_params']['nfolds']
NORM = "--norm" if prepdata_cfg['norm'] else ""
NCATS = prepdata_cfg['ncats']

SUMM_FILE = "___tmp__SUMM_FILE.txt"
os.system("echo \"Summary of results: \" > %s" % (SUMM_FILE))

##################################################
# executing experiments
prGreen("[wrapper] executing wrapper...")
ret = os.system("python3 prepare_data.py -i %s -o %s"
                " -r %s -c %s --nfolds=%s --minleaf=%s --pred=%s --ncats=%s"
                " %s --rmtemp" %
                (INPUT_FILE, OUTPUT_FILE, FILTER_ROWS,
                 FILTER_COLS, NFOLDS,
                 MINLEAF, PRED, str(NCATS), NORM))
if (ret != 0):
    prRed("[wrapper] Something went wrong!")
    exit(1)
RES_FILE = "results/model_learn_stats_%s_folds%s_leaf%s" % (
    str(PRED), str(NFOLDS), str(MINLEAF))

##################################################
# parsing results
os.system("cp results/exp_%s_all_REPTree_%s_%s/model_learn_stats.txt"
          " %s" %
          (OUTPUT_FILE.split(".")[0], MINLEAF, NFOLDS, RES_FILE))
grep_file2file("Correctly", RES_FILE, SUMM_FILE)
grep_file2file("Correlation coefficient", RES_FILE, SUMM_FILE)
grep_file2file("Mean absolute error", RES_FILE, SUMM_FILE)
grep_file2file("Relative absolute error", RES_FILE, SUMM_FILE)
grep_file2file("Total Number of Instances", RES_FILE, SUMM_FILE)
grep_file2file("Size of the tree", RES_FILE, SUMM_FILE)

##################################################
# results obtained
prGreen("[wrapper] displaying summary of results")
os.system("cat %s" % SUMM_FILE)
prGreen("[wrapper] finished! cleaning temp files...")

##################################################
# remove tmp files
os.system("rm %s" % SUMM_FILE)

##################################################
# copy results for parsing tree
PARSING_TREE_FILE = "___tmp_tree.txt"
os.system("cp %s %s" % (RES_FILE, PARSING_TREE_FILE))

# testing parsing tree
tree = REPTree(PARSING_TREE_FILE)
tree.print_parents_compressed_by_value("I-5.419-6.035")

os.system("rm %s" % PARSING_TREE_FILE)
