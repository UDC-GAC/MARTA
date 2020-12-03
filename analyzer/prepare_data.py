#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# File              : prepare_data.py
# Author            : Marcos Horro <marcos.horro@udc.gal>
# Date              : Mar 29 Out 2019 09:38:20 MDT
# Last Modified Date: Ven 15 Nov 2019 15:50:08 MST
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
from math import ceil
from utils import weka_cmd
from utils.weka_cmd import path_weka
from utils.utilities import StoreDictKeyPair
from utils.utilities import pr_debug
from utils.utilities import pr_col
from utils.utilities import colors as c

path_root = os.getcwd() + "/"
path_data = path_root + "data"
path_res = path_root + "results"
nsets = 0
force_replacement = True
algorithms = ['reptree']
min_obj = [1]  # min number of instances
max_leaf = [3]  # number of folds
norm = False

train_suffix = "_train.arff"
test_suffix = "_test.arff"

##################################################
# preprocessing data


def check_error(phase, err_log):
    if not os.path.exists(err_log):
        pr_col(c.fg.orange, "[warning] no err log file")
        return
    for l in open(err_log, 'r'):
        if "weka exception" in l:
            pr_col(
                c.fg.red, "[error] %s could not open file:\n%s" % (phase, l))
            exit(-1)
        if "exception" in l:
            pr_col(
                c.fg.red, "[error] %s something went wrong:\n%s" % (phase, l))
            exit(-1)


def preprocess_data(inputfile, outputfile, cols, *rows, cat, catscale=1, ncat):
    df = pd.read_csv(inputfile, comment="#", index_col=False)
    if norm:
        # FIXME:
        if norm_min_max:
            # minmax
            setattr(df, cat, getattr(df, cat)-min(getattr(df, cat)))
            setattr(df, cat, getattr(df, cat)/max(getattr(df, cat)))
        if norm_z_score:
            # z-score
            print("[debug] z-score avg = %f" % np.mean(getattr(df, cat)))
            print("[debug] z-score std = %f" % np.std(getattr(df, cat)))
            setattr(df, cat, np.log(getattr(df, cat)))
            setattr(df, cat, (getattr(df, cat)-np.mean(getattr(df, cat)
                                                       ))/np.std(getattr(df, cat)))
    tmp = df
    if ncat > 0:
        # categorical data
        tmp_cat = getattr(tmp, cat)
        bins = np.linspace(min(getattr(df, cat)),
                           max(getattr(df, cat)), ncat+1)
        step = bins[1] - bins[0]
        labels = ["I-{0}-{1}".format("{0:.3f}".format(float(i/catscale)),
                                     "{0:.3f}".format(float((i + step)/catscale))) for i in bins]
        setattr(tmp, cat, pd.cut(tmp_cat, bins, labels=labels[:-1]))
    for d in rows:
        if d == None:
            continue
        for k, v in d.items():
            cond = (getattr(tmp, k) == v)
            tmp = tmp[cond].copy()
    if (tmp.count()[0] == 0):
        pr_col(
            c.fg.red, "[error] dataset empty! revise constraints in data please!")
        exit(-1)
    f_cols = cols + [cat]
    tmp = tmp[list(f_cols)]
    tmp.to_csv(outputfile, index=False)
    return

##################################################
# creating files for training and testing


def create_train_and_test(datafile):
    os.system("mkdir -p %s" % path_data)
    name = datafile.split(".")[0]
    pref = "_full_rand"
    for i in range(1, nsets+1):
        # training
        suff = train_suffix
        filename = "%s_%s%s%s" % (name, str(i), pref, suff)
        if force_replacement or not (os.path.exists("%s/%s" % (path_data, filename))):
            os.system("java -cp %s/weka.jar weka.filters.supervised.instance.stratifiedremovefolds "
                      " -i %s -c last -o %s/%s "
                      " -n %s -f %s -v -s 42 %s" % (path_weka, datafile,
                                                    path_data, filename,
                                                    str(nsets), str(i),
                                                    err_out))
        # testing
        suff = test_suffix
        filename = "%s_%s%s%s" % (name, str(i), pref, suff)
        if force_replacement or not (os.path.exists("%s/%s" % (path_data, filename))):
            os.system("java -cp %s/weka.jar weka.filters.supervised.instance.stratifiedremovefolds "
                      " -i %s -c last -o %s/%s "
                      " -n %s -f %s -s 42 %s" % (path_weka, datafile,
                                                 path_data, filename,
                                                 str(nsets), str(i), err_out))
    suff = train_suffix
    filename = "%s_all%s%s" % (name, pref, suff)
    os.system("cp %s %s/%s" % (datafile, path_data, filename))
    suff = test_suffix
    filename = "%s_all%s%s" % (name, pref, suff)
    os.system("cp %s %s/%s" % (datafile, path_data, filename))
##################################################
# runing experiments


def run_experiments(datafile, dtparams):
    os.system("mkdir -p %s" % (path_res))
    alg = dtparams['alg']
    params = dtparams['params']
    opts = dtparams['opts']
    name = datafile.split(".")[0]
    pref = "_full_rand"
    liters = list(range(1, nsets+1))
    liters.append("all")
    for i in liters:
        suffix = weka_cmd.params_to_str(alg, params)
        basename = "%s_%s" % (name, str(i))
        foldername = "exp_%s%s" % (basename, suffix)
        os.system("mkdir -p %s/%s" % (path_res, foldername))
        folderpath = path_res + "/" + foldername
        trainfile = path_data + "/" + basename + pref + train_suffix
        testfile = path_data + "/" + basename + pref + test_suffix
        print("\t[%s] train... (%s/%d)" %
              (alg, str(i), nsets))
        weka_cmd.train_model(
            alg, params, opts, trainfile, folderpath, err_out)
        check_error("[train]", err_file)
        print("\t[%s] produce classfied outputs... (%s/%d)" %
              (alg, str(i), nsets))
        weka_cmd.produce_class_outputs(alg, folderpath, testfile,
                                       err_out)
        check_error("[class output]", err_file)
        print("\t[%s] produce tester stats... (%s/%d)" %
              (alg, str(i), nsets))
        weka_cmd.produce_tester_stats(alg, folderpath,
                                      testfile, err_out)
        check_error("[tester]", err_file)
    return


##################################################
# parsing arguments
parser = argparse.ArgumentParser(
    description='convert from csv to arff (generic format), creates training and testing sets. allows the inclusion of custom scripts (no need to be python) for preparing data according to experiments need. todo: options for selecting categorical value. note: need to have weka installed.')
parser.add_argument('-p', '--pred',
                    help='dimension to predict', default="flopss")
parser.add_argument('-nc', '--ncats',
                    help='number of categories of dimension to predict,'
                    ' categories are created uniformly in pandas',
                    default=10)
parser.add_argument('-cs', '--catscale',
                    help='scale factor when creating categories, not relevant'
                    ' if dimension is not numeric',
                    default=1)
parser.add_argument('-nv', '--norm', action='store_true',
                    help='normalize predicted dimension (min-max norm i.e.'
                    ' values in range [0-1])',
                    default=False)
parser.add_argument('-rm', '--rmtemp', action='store_true',
                    help='clean directory of temp files (default=False)', default=False)
parser.add_argument('-f', '--force', action='store_true',
                    help='force replacement files even if they exist (default=False)', default=False)
parser.add_argument('-r', '--rows', dest="rows", action=StoreDictKeyPair,
                    help="filtering rows as a dictionary. e.g. -r i=0 j=0", nargs="+", metavar="key=val")
parser.add_argument('-dt', '--dtalg',
                    help='decision tree algorithm, e.g. reptree, j48',
                    default='reptree')
parser.add_argument('-dtp', '--dtparams', dest="dtparams", action=StoreDictKeyPair,
                    help="decision tree parameters", nargs="*", metavar="key=val")
parser.add_argument('-dto', '--dtopts', dest="dtopts",
                    help="options for ftalgo")
required_named = parser.add_argument_group('required named arguments')
required_named.add_argument(
    '-i', '--input', help='input file name', required=True)
required_named.add_argument(
    '-o', '--output', help='output file name', required=True)
required_named.add_argument('-c', '--columns', metavar='col', type=str, nargs='+',
                            help='columns we are interested to filter')
args = parser.parse_args()

force_replacement = args.force
input_file = args.input
output_file = args.output
columns = args.columns
rows = args.rows
pred = args.pred
ncats = int(args.ncats)
catscale = float(args.catscale)
norm = args.norm
dtalg = args.dtalg
dtparams = args.dtparams
dtopts = args.dtopts
err_file = "___error.log"
err_out = " 2> %s" % err_file
##################################################

pr_col(c.fg.orange, "[prepare_data] starting process...")
##################################################
# script based on pouchet's, but unfollowing him's, i perform the 'filtering' or whatever in the csv instead of the arff
# main reason: familiarity and ease to work with dataframes in python and mantainability for me...
# 1) create temporal csv with filtering perform in terms of columns, rows and even some transformations
tmp_csv = "___tmp_" + str(input_file.split("/")[-1])
pr_col(c.fg.orange, "[step 1] filtering csv... (" + input_file + ")")
preprocess_data(input_file, tmp_csv, columns, rows, ncat=ncats,
                catscale=catscale, cat=pred)

##################################################
# 2) convert csv to arff file (all data, beware to have unique name for columns in the csv file):
pr_col(c.fg.orange, "[step 2] converting csv to arff format...")
weka_cmd.convert_csv_to_arff(tmp_csv, output_file)

##################################################
# 3) prepare data: create training and testing sets
pr_col(c.fg.orange,
       "[step 3] creating training and testing sets... (nsets = " + str(nsets) +
       ")")
create_train_and_test(output_file)

##################################################
# 4) run experiments
pr_col(c.fg.orange, "[step 4] running experiments...")
run_experiments(output_file, {'alg': dtalg,
                              'params': dtparams, 'opts': dtopts})

pr_col(c.fg.orange, "[prepare_data] you are all set!")
##################################################
# clean working directory
if args.rmtemp:
    pr_col(c.fg.orange, "[prepare_data] cleaning temp files!")
    os.system("rm %s %s" % (err_file, output_file))
