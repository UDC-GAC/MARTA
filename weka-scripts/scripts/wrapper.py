#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# File              : wrapper.py
# Author            : Marcos Horro <marcos.horro@udc.gal>
# Date              : Xov 31 Out 2019 09:56:07 MDT
# Last Modified Date: Mar 12 Nov 2019 10:28:31 MST
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
import weka_cmd
import utils.utilities as ut
from utils.utilities import StoreDictKeyPair
from utils.utilities import pr_debug
from utils.utilities import pr_col
from utils.utilities import colors as c
from utils.utilities import grep_file2file

##################################################
# parsing arguments
parser = argparse.ArgumentParser(
    description='Wrapper for preparing data given a CSV')
required_named = parser.add_argument_group('required named arguments')
required_named.add_argument(
    '-i', '--input', help='input file name', required=True)
args = parser.parse_args()

##################################################
# parsing all the arguments from the config.yml
YML_CONFIG = args.input
with open(YML_CONFIG, 'r') as ymlfile:
    cfg = yaml.load(ymlfile)

# general config
general_cfg = cfg[0]['general']
INPUT_FILE = general_cfg['input']
OUTPUT_FILE = general_cfg['output']
FORCE_REPLACEMENT = general_cfg['overwrite']
RM_TEMP_FILES = general_cfg['clean']
PRINT_DEBUG = general_cfg['debug']

# prepare data
prepdata_cfg = cfg[1]['prepare_data']
FILTER_COLS = "-c " + \
    prepdata_cfg['cols'] if len(prepdata_cfg['cols']) else ""
FILTER_ROWS = "-r " + \
    prepdata_cfg['rows'] if len(prepdata_cfg['rows']) else ""
PRED = prepdata_cfg['pred']
NORM = "--norm" if prepdata_cfg['norm'] else ""
NCATS = prepdata_cfg['ncats']
DTALG = prepdata_cfg['dt_alg']
DTPARAMS = prepdata_cfg['dt_params']
MIN_ACC = prepdata_cfg['min_acc']

# recommender
recommender_cfg = cfg[2]['recommender']
INTEREST_VALUE = recommender_cfg['interest_value']
INTEREST_VALUE_T = recommender_cfg['interest_value_type']
DIMENSIONS = recommender_cfg['dimensions']

SUMM_FILE = "___tmp__SUMM_FILE.txt"
os.system("echo \"Summary of results: \" > %s" % (SUMM_FILE))

##################################################
# executing experiments
pr_col(c.fg.green, "[wrapper] executing wrapper...")
pr_debug(PRINT_DEBUG, "python3 prepare_data.py -i %s -o %s"
         " %s %s --pred=%s --ncats=%s"
         " %s -dt %s -dtp %s" %
         (INPUT_FILE, OUTPUT_FILE, FILTER_ROWS,
          FILTER_COLS, PRED, str(NCATS), NORM,
          DTALG, DTPARAMS))
ret = os.system("python3 prepare_data.py -i %s -o %s"
                " %s %s --pred=%s --ncats=%s"
                " %s -dt %s -dtp %s" %
                (INPUT_FILE, OUTPUT_FILE, FILTER_ROWS,
                 FILTER_COLS, PRED, str(NCATS), NORM,
                 DTALG, DTPARAMS))
if (ret != 0):
    pr_col(c.fg.red, "[wrapper] Something went wrong!")
    exit(1)
suffix_dtparams = "" if len(DTPARAMS) == 0 else "_" + \
    DTPARAMS.replace("=", "").replace(" ", "_")
suffix = "_" + str(DTALG) + suffix_dtparams
RES_FILE = "results/model_learn_stats_%s%s" % (
    str(PRED), suffix)

##################################################
# parsing results
os.system("cp results/exp_%s_all%s/model_learn_stats.txt"
          " %s" %
          (OUTPUT_FILE.split(".")[0], suffix, RES_FILE))
acc = grep_file2file("Correctly", RES_FILE, SUMM_FILE)
acc = float(grep_file2file("Correlation coefficient", RES_FILE,
                           SUMM_FILE)) if acc == None else float(acc)/100
grep_file2file("Mean absolute error", RES_FILE, SUMM_FILE)
grep_file2file("Relative absolute error", RES_FILE, SUMM_FILE)
grep_file2file("Total Number of Instances", RES_FILE, SUMM_FILE)
tree_size = grep_file2file("Size of the tree", RES_FILE, SUMM_FILE)

##################################################
# results obtained
pr_col(c.fg.green, "[wrapper] displaying summary of results")
os.system("cat %s" % SUMM_FILE)
if MIN_ACC > acc:
    pr_col(c.fg.red, "[ERROR] minimum accuracy (%s) not achieved (%s)" %
           (MIN_ACC, acc))
    exit(-1)
pr_col(c.fg.green, "[wrapper] finished! cleaning temp files...")

##################################################
# copy results for parsing tree
PARSING_TREE_FILE = "___tmp_tree.txt"
os.system("cp %s %s" % (RES_FILE, PARSING_TREE_FILE))

os.system("python3 recommender.py -i %s -v %s -t %s -d %s -dt %s" %
          (PARSING_TREE_FILE, INTEREST_VALUE, INTEREST_VALUE_T, DIMENSIONS,
              DTALG))

##################################################
# remove tmp files
if RM_TEMP_FILES:
    os.system("rm %s" % SUMM_FILE)
    os.system("rm %s" % PARSING_TREE_FILE)
