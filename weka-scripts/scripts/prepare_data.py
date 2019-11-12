#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# File              : prepare_data.py
# Author            : Marcos Horro <marcos.horro@udc.gal>
# Date              : Mar 29 Out 2019 09:38:20 MDT
# Last Modified Date: Mar 12 Nov 2019 10:28:59 MST
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

import os
import sys
import argparse
import pandas as pd
import numpy as np
import weka_cmd
from math import ceil
from utils.utilities import StoreDictKeyPair
from utils.utilities import pr_debug
from utils.utilities import pr_col
from utils.utilities import colors as c
# global definitions
PATH_ROOT = os.getcwd() + "/"
PATH_DATA = PATH_ROOT + "data"
PATH_RES = PATH_ROOT + "results"
NSETS = 0
FORCE_REPLACEMENT = True
ALGORITHMS = ['REPTree']
MIN_OBJ = [1]  # min number of instances
MAX_LEAF = [3]  # number of folds
NORM = False

##################################################
# preprocessing data


def check_error(phase, err_log):
    for l in open(err_log, 'r'):
        if "Weka exception" in l:
            pr_col(c.fg.red, "[ERROR] %s could not open file:\n%s" % (phase, l))
            exit(-1)
        if "Exception" in l:
            pr_col(
                c.fg.red, "[ERROR] %s something went wrong:\n%s" % (phase, l))
            exit(-1)


def preprocess_data(inputfile, outputfile, cols, *rows, cat, ncat):
    df = pd.read_csv(inputfile, comment="#", index_col=False)
    if NORM:
        if NORM_MIN_MAX:
            # minmax
            setattr(df, cat, getattr(df, cat)-min(getattr(df, cat)))
            setattr(df, cat, getattr(df, cat)/max(getattr(df, cat)))
        if NORM_Z_SCORE:
            # z-score
            print("[DEBUG] z-score avg = %f" % np.mean(getattr(df, cat)))
            print("[DEBUG] z-score std = %f" % np.std(getattr(df, cat)))
            setattr(df, cat, np.log(getattr(df, cat)))
            setattr(df, cat, (getattr(df, cat)-np.mean(getattr(df, cat)
                                                       ))/np.std(getattr(df, cat)))
    tmp = df
    for d in rows:
        if d == None:
            continue
        for k, v in d.items():
            cond = (getattr(tmp, k) == v)
            tmp = tmp[cond]
    if (tmp.count()[0] == 0):
        pr_col(
            c.fg.red, "[ERROR] DATASET EMPTY! Revise constraints in data please!")
        exit(-1)
    if ncat > 0:
        # categorical data
        tmp_cat = getattr(tmp, cat)
        bins = np.linspace(min(getattr(df, cat)), max(getattr(df, cat)), ncat+1)
        step = bins[1] - bins[0]
        labels = ["I-{0}-{1}".format("{0:.3f}".format(float(i/1e9)),
                                     "{0:.3f}".format(float((i + step)/1e9))) for i in bins]
        setattr(tmp, cat, pd.cut(tmp_cat, bins, labels=labels[:-1]))
    f_cols = cols + [cat]
    tmp = tmp[list(f_cols)]
    tmp.to_csv(outputfile, index=False)
    return

##################################################
# creating files for training and testing


def create_train_and_test(datafile):
    os.system("mkdir -p %s" % PATH_DATA)
    name = datafile.split(".")[0]
    pref = "_full_rand"
    for i in range(1, NSETS+1):
        # training
        suff = "_train.arff"
        filename = "%s_%s%s%s" % (name, str(i), pref, suff)
        if FORCE_REPLACEMENT or not (os.path.exists("%s/%s" % (PATH_DATA, filename))):
            os.system("java -cp %s/weka.jar weka.filters.supervised.instance.StratifiedRemoveFolds "
                      " -i %s -c last -o %s/%s "
                      " -N %s -F %s -V -S 42 %s" % (PATH_WEKA, datafile,
                                                    PATH_DATA, filename,
                                                    str(NSETS), str(i),
                                                    ERR_OUT))
        # testing
        suff = "_test.arff"
        filename = "%s_%s%s%s" % (name, str(i), pref, suff)
        if FORCE_REPLACEMENT or not (os.path.exists("%s/%s" % (PATH_DATA, filename))):
            os.system("java -cp %s/weka.jar weka.filters.supervised.instance.StratifiedRemoveFolds "
                      " -i %s -c last -o %s/%s "
                      " -N %s -F %s -S 42 %s" % (PATH_WEKA, datafile,
                                                 PATH_DATA, filename,
                                                 str(NSETS), str(i), ERR_OUT))
    suff = "_train.arff"
    filename = "%s_all%s%s" % (name, pref, suff)
    os.system("cp %s %s/%s" % (datafile, PATH_DATA, filename))
    suff = "_test.arff"
    filename = "%s_all%s%s" % (name, pref, suff)
    os.system("cp %s %s/%s" % (datafile, PATH_DATA, filename))
##################################################
# runing experiments


def run_experiments(datafile, dtparams):
    os.system("mkdir -p %s" % (PATH_RES))
    alg = dtparams['alg']
    params = dtparams['params']
    name = datafile.split(".")[0]
    pref = "_full_rand"
    liters = list(range(1, NSETS+1))
    liters.append("all")
    for i in liters:
        suffix = weka_cmd.params_to_str(alg, params)
        basename = "%s_%s" % (name, str(i))
        foldername = "exp_%s%s" % (basename, suffix)
        os.system("mkdir -p %s/%s" % (PATH_RES, foldername))
        folderpath = PATH_RES + "/" + foldername
        trainfile = PATH_DATA + "/" + basename + pref + "_train.arff"
        testfile = PATH_DATA + "/" + basename + pref + "_test.arff"
        print("\t[%s] Train... (%s/%d)" %
              (alg, str(i), NSETS))
        weka_cmd.train_model(
            alg, params, trainfile, folderpath, ERR_OUT)
        check_error("[train]", ERR_FILE)
        print("\t[%s] Produce classfied outputs... (%s/%d)" %
              (alg, str(i), NSETS))
        weka_cmd.produce_class_outputs(alg, folderpath, testfile,
                                       ERR_OUT)
        check_error("[class output]", ERR_FILE)
        print("\t[%s] Produce tester stats... (%s/%d)" %
              (alg, str(i), NSETS))
        weka_cmd.produce_tester_stats(alg, folderpath,
                                      testfile, ERR_OUT)
        check_error("[tester]", ERR_FILE)
    return


##################################################
# parsing arguments
parser = argparse.ArgumentParser(
    description='Convert from CSV to ARFF (generic format), creates training and testing sets. Allows the inclusion of custom scripts (no need to be python) for preparing data according to experiments need. TODO: options for selecting categorical value. NOTE: Need to have WEKA installed.')
parser.add_argument('-p', '--pred',  # action='store_const',
                    help='dimension to predict', default="FLOPSs")
parser.add_argument('-nc', '--ncats',  # action='store_const',
                    help='number of categories of dimension to predict,'
                    ' categories are created uniformly in pandas',
                    default=10)
parser.add_argument('-nv', '--norm', action='store_true',
                    help='normalize predicted dimension (min-max norm i.e.'
                    ' values in range [0-1])',
                    default=False)
parser.add_argument('-rm', '--rmtemp', action='store_true',
                    help='clean directory of temp files (default=False)', default=False)
parser.add_argument('-f', '--force', action='store_true',
                    help='force replacement files even if they exist (default=False)', default=False)
parser.add_argument('-r', '--rows', dest="rows", action=StoreDictKeyPair,
                    help="filtering rows as a dictionary. E.g. -r I=0 J=0", nargs="+", metavar="KEY=VAL")
parser.add_argument('-dt', '--dtalg',  # action='store_const',
                    help='decision tree algorithm, e.g. REPTree, J48',
                    default='REPTree')
parser.add_argument('-dtp', '--dtparams', dest="dtparams", action=StoreDictKeyPair,
                    help="decision tree parameters", nargs="*", metavar="KEY=VAL")
required_named = parser.add_argument_group('required named arguments')
required_named.add_argument(
    '-i', '--input', help='input file name', required=True)
required_named.add_argument(
    '-o', '--output', help='output file name', required=True)
required_named.add_argument('-c', '--columns', metavar='col', type=str, nargs='+',
                            help='columns we are interested to filter')
args = parser.parse_args()

FORCE_REPLACEMENT = args.force
INPUT_FILE = args.input
OUTPUT_FILE = args.output
COLUMNS = args.columns
ROWS = args.rows
PRED = args.pred
NCATS = int(args.ncats)
NORM = args.norm
DTALG = args.dtalg
DTPARAMS = args.dtparams
# ERR_OUT = " 2> /dev/null"
ERR_FILE = "___error.log"
ERR_OUT = " 2> %s" % ERR_FILE
##################################################

pr_col(c.fg.green, "[prepare_data] starting process...")
##################################################
# Script based on Pouchet's, but unfollowing him's, I perform the 'filtering' or whatever in the CSV instead of the ARFF
# Main reason: familiarity and ease to work with DataFrames in python and mantainability for me...
# 1) create temporal CSV with filtering perform in terms of columns, rows and even some transformations
TMP_CSV = "___tmp_" + str(INPUT_FILE.split("/")[-1])
pr_col(c.fg.green, "[step 1] filtering csv... (" + INPUT_FILE + ")")
preprocess_data(INPUT_FILE, TMP_CSV, COLUMNS, ROWS, ncat=NCATS, cat=PRED)

##################################################
# 2) convert CSV to ARFF file (all data, beware to have unique name for columns in the CSV file):
pr_col(c.fg.green, "[step 2] converting csv to arff format...")
weka_cmd.convert_csv_to_arff(TMP_CSV, OUTPUT_FILE)

##################################################
# 3) prepare data: create training and testing sets
pr_col(c.fg.green,
       "[step 3] creating training and testing sets... (NSETS = " + str(NSETS) +
       ")")
create_train_and_test(OUTPUT_FILE)

##################################################
# 4) run experiments
pr_col(c.fg.green, "[step 4] running experiments...")
run_experiments(OUTPUT_FILE, {'alg': DTALG, 'params': DTPARAMS})

pr_col(c.fg.green, "[prepare_data] you are all set!")
##################################################
# Clean working directory
if args.rmtemp:
    pr_col(c.orange, "\t[rm option enabled] cleaning temp files!")
    os.system("rm %s %s %s" % (TMP_CSV, ERR_FILE, OUTPUT_FILE))
