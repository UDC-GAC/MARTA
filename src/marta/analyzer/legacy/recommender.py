#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# File              : recommender.py
# Author            : Marcos Horro <marcos.horro@udc.gal>
# Date              : Mér 06 Nov 2019 17:54:44 MST
# Last Modified Date: Xov 14 Nov 2019 11:56:47 MST
# Last Modified By  : Marcos Horro <marcos.horro@udc.gal>
#
# Copyright (c) 2019 Marcos Horro <marcos.horro@udc.gal>
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

import argparse
import pandas as pd
import numpy as np
import operator
from parse_tree import DTTree
from utils.utilities import colors as c
from utils.utilities import pr_col

# translations needed of some operators
ops = {'>': operator.gt, '>=': operator.ge, '<': operator.lt, '<=': operator.le,
       '=': operator.eq}

##################################################
# parsing arguments
parser = argparse.ArgumentParser(
    description='')
required_named = parser.add_argument_group('required named arguments')
required_named.add_argument(
    '-i', '--input', help='input file name', required=True)
required_named.add_argument(
    '-c', '--csv', help='CSV input file name', required=True)
required_named.add_argument('-p', '--pred',
                            help='dimension we are predicting', required=True)
required_named.add_argument('-v', '--value',
                            help='value we are looking for', required=True)
required_named.add_argument('-t', '--vtype',
                            help='type value: numeric/categorial', required=True)
required_named.add_argument('-d', '--dimensions', metavar='dim', type=str, nargs='+',
                            help='values we are interested on', required=True)
required_named.add_argument('-dt', '--dtalg',
                            help='decision tree algorithm, e.g. REPTree, J48',
                            default='REPTree')
args = parser.parse_args()

g_input_file = args.input
g_csv_file = args.csv
g_dimensions = args.dimensions
g_pred = args.pred
g_interest_value = args.value
g_interest_value_t = args.vtype
g_dtalg = args.dtalg

if g_interest_value_t != "numeric" and g_interest_value_t != "categorial":
    pr_col(
        c.fg.red, "[ERROR] interset value type wrong: should be numeric or categorial")
    exit(-1)

# testing parsing tree
tree = DTTree(g_input_file, g_dtalg)
norm_val = g_interest_value
if g_interest_value_t == "numeric":
    norm_val = tree.get_value_range(g_interest_value)
leaves = tree.get_parents_compressed_by_value(norm_val)

##################################################
# analyzing outliers
df = pd.read_csv(g_csv_file, comment="#", index_col=False)
df_filtered = pd.DataFrame(columns=df.columns)
i = 0
for leaf in leaves:
    tmp = df
    d = leaf[1]
    cond_str = ""
    for k, v in d.items():
        for op, val in v.items():
            cond = ops[op](getattr(tmp, k), float(val))
            cond_str += str(k) + str(op) + str(val) + " & "
            tmp = tmp[cond]
    print("cond " + str(i) + ": " + cond_str[:-2])
    df_filtered = pd.concat([df_filtered, tmp]).drop_duplicates()
    i += 1

##################################################
# getting false positives
cond = (getattr(df, g_pred) == norm_val)
actual_val = df[cond]
n_actval = len(actual_val)

false_pos = df_filtered[getattr(df_filtered, g_pred) != norm_val]
pr_col(c.fg.red, "[recommender] false positives: %s/%s" %
       (len(false_pos), n_actval))

# analysis of the false positives. Not significant if they are in contiguous
# categories
# get the categories of false negatives
if len(false_pos) > 1:
    print(g_pred)
    print(getattr(getattr(df, g_pred), "values"))
    cat_org = np.unique(getattr(getattr(df, g_pred), "values"))
    print(cat_org)
    cat_org.sort()
    cat_false_pos = np.unique(getattr(getattr(false_pos, g_pred), "values"))
    inter_org_false_pos = [val for val in cat_org if val in cat_false_pos]
    pos_pred = np.where(cat_org == norm_val)[0]
    for val in inter_org_false_pos:
        pos_fp = np.where(cat_org == val)[0]
        diff = abs(pos_pred-pos_fp)
        df_false_pos_cat = false_pos[getattr(false_pos, g_pred) == val]
        n = len(df_false_pos_cat)
        print("\tdiff with cat %s is %s (%s)" % (str(val), str(diff), str(n)))
        print(df_false_pos_cat[g_dimensions])


##################################################
# getting false negatives
false_neg = df[~df.index.isin(df_filtered.index) & cond]
pr_col(c.fg.red, "[recommender] false negative: %s " % (len(false_neg)))
print(false_neg)
print("Unique values for these outliers:")
for col in false_neg:
    print("col " + str(col) + ", values:" +
          str(np.unique(getattr(getattr(false_neg, col), "values"))))
# analysis of the false negatives: extract common dimensions