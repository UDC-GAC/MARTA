#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# File              : recommender.py
# Author            : Marcos Horro <marcos.horro@udc.gal>
# Date              : Mér 06 Nov 2019 17:54:44 MST
# Last Modified Date: Xov 14 Nov 2019 10:43:08 MST
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
required_named.add_argument('-p', '--pred',  # action='store_const',
                            help='dimension we are predicting', required=True)
required_named.add_argument('-v', '--value',  # action='store_const',
                            help='value we are looking for', required=True)
required_named.add_argument('-t', '--vtype',  # action='store_const',
                            help='type value: numeric/categorial', required=True)
required_named.add_argument('-d', '--dimensions', metavar='dim', type=str, nargs='+',
                            help='values we are interested on', required=True)
required_named.add_argument('-dt', '--dtalg',  # action='store_const',
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
# tree.print_parents_compressed_by_value(norm_val)
leaves = tree.get_parents_compressed_by_value(norm_val)

##################################################
# analyzing outliers
df = pd.read_csv(g_csv_file, comment="#", index_col=False)
df_filtered = pd.DataFrame(columns=df.columns)
for leaf in leaves:
    tmp = df
    d = leaf[1]
    for k, v in d.items():
        for op, val in v.items():
            cond = ops[op](getattr(tmp, k), float(val))
            tmp = tmp[cond]
    df_filtered = pd.concat([df_filtered, tmp]).drop_duplicates()

##################################################
# getting false positives
cond = (getattr(df, g_pred) == norm_val)
actual_val = df[cond]
n_actval = len(actual_val)

false_pos = df_filtered[getattr(df_filtered, g_pred) != norm_val]
pr_col(c.fg.red, "[recommender] false positives: %s/%s" %
       (len(false_pos), n_actval))
print(false_pos)

false_neg = df[~df.index.isin(df_filtered.index) & cond]
pr_col(c.fg.red, "[recommender] false negative: %s " % (len(false_neg)))
print(false_neg)
