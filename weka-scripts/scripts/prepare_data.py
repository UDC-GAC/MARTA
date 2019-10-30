################################################################################
# -*- coding: utf-8 -*-
# prepare_data.py
# Copyright (c) 2019 Marcos Horro <marcos.horro@udc.gal>
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
#!/env/python3

import os
import sys
import argparse
import pandas as pd
import numpy as np

# global definitions
PATH_WEKA="~/Descargas/weka-3-8-3"
PATH_DATA="."
NSETS=5
FORCE_REPLACEMENT=False

class StoreDictKeyPair(argparse.Action):
     def __init__(self, option_strings, dest, nargs=None, **kwargs):
         self._nargs = nargs
         super(StoreDictKeyPair, self).__init__(option_strings, dest, nargs=nargs, **kwargs)
     def __call__(self, parser, namespace, values, option_string=None):
         my_dict = {}
         for kv in values:
             k,v = kv.split("=")
             my_dict[k] = int(v)
         setattr(namespace, self.dest, my_dict)

##################################################
# preprocessing data
def preprocess_data(inputfile, outputfile, cols, *rows, cat="FLOPSs", ncat=20):
  df = pd.read_csv(inputfile, comment="#", index_col=False)
  tmp = df[list(cols)] # selecting only those columns
  for d in rows:
    if d==None: continue
    for k,v in d.items():
      cond = (getattr(tmp,k)==v)
      tmp = tmp[cond]
  # categorical data
  tmp_cat = getattr(tmp,cat)
  bins = np.linspace(min(tmp_cat),max(tmp_cat),ncat+1)
  step = bins[1] - bins[0]
  labels = ["I-{0}-{1}".format("{0:.3f}".format(float(i/1e9)), "{0:.3f}".format(float((i + step)/1e9))) for i in bins]
  setattr(tmp,cat,pd.cut(tmp_cat, bins, labels=labels[:-1]))
  tmp.to_csv(outputfile, index=False)
  return

##################################################
# creating files for training and testing
def train_and_test(datafile):
  name = datafile.split(".")[0] 
  pref="_full_rand"
  for i in range(1,NSETS+1):
    # training
    suff="_train.arff"
    filename="%s_%s%s%s" % (name,str(i),pref,suff)
    if FORCE_REPLACEMENT or not (os.path.exists("%s/%s" % (PATH_DATA,filename))):
      os.system("java -cp %s/weka.jar weka.filters.supervised.instance.StratifiedRemoveFolds "\
                " -i %s/%s -c last -o %s/%s "\
                " -N %s -F %s -V -S 42 2> %s" % (PATH_WEKA,PATH_DATA,datafile,PATH_DATA,filename,str(NSETS),str(i),err_output))
    
    # testing
    suff="_test.arff"
    filename="%s_%s%s%s" % (name,str(i),pref,suff)
    if FORCE_REPLACEMENT or not (os.path.exists("%s/%s" % (PATH_DATA,filename))):
      os.system("java -cp %s/weka.jar weka.filters.supervised.instance.StratifiedRemoveFolds "\
                " -i %s/%s -c last -o %s/%s "\
                " -N %s -F %s -S 42 2> %s" % (PATH_WEKA,PATH_DATA,datafile,PATH_DATA,filename,str(NSETS),str(i),err_output))
    suff="_all_train.arff"
    filename="%s_%s%s%s" % (name,str(i),pref,suff)
    os.system("cp %s/%s %s/%s" % (PATH_DATA,datafile,PATH_DATA,filename))
    
    suff="_all_test.arff"
    filename="%s_%s%s%s" % (name,str(i),pref,suff)
    os.system("cp %s/%s %s/%s" % (PATH_DATA,datafile,PATH_DATA,filename))

##################################################
# parsing arguments
parser = argparse.ArgumentParser(description='Convert from CSV to ARFF (generic format), creates training and testing sets. Allows the inclusion of custom scripts (no need to be python) for preparing data according to experiments need. TODO: options for selecting categorical value. NOTE: Need to have WEKA installed.')
parser.add_argument('-rm', '--rmtemp', action='store_true', help='clean directory of temp files (default=False)', default=False)
parser.add_argument('-f', '--force', action='store_true', help='force replacement files even if they exist (default=False)', default=False)
parser.add_argument('-r','--rows', dest="rows", action=StoreDictKeyPair, help="filtering rows as a dictionary. E.g. -r I=0 J=0", nargs="+", metavar="KEY=VAL")
requiredNamed = parser.add_argument_group('required named arguments')
requiredNamed.add_argument('-i', '--input', help='input file name', required=True)
requiredNamed.add_argument('-o', '--output', help='output file name', required=True)
requiredNamed.add_argument('-c', '--columns', metavar='col', type=str, nargs='+',
                    help='columns we are interested to filter')
args = parser.parse_args()

FORCE_REPLACEMENT=args.force
INPUT_FILE = args.input
OUTPUT_FILE = args.output
COLUMNS = args.columns
ROWS=args.rows
err_output="/dev/null"
##################################################

##################################################
# Script based on Pouchet's, but unfollowing him's, I perform the 'filtering' or whatever in the CSV instead of the ARFF
# Main reason: familiarity and ease to work with DataFrames in python and mantainability for me...
# 1) Create temporal CSV with filtering perform in terms of columns, rows and even some transformations
TMP_CSV = "___tmp_" + str(INPUT_FILE)
print("filtering csv... (", INPUT_FILE, ")")
preprocess_data(INPUT_FILE, TMP_CSV, COLUMNS, ROWS)

##################################################
# 2) Convert CSV to ARFF file (all data, beware to have unique name for columns in the CSV file):
print("converting csv to arff format...")
os.system("java -cp %s/weka.jar weka.core.converters.CSVLoader %s -B 100000 > %s" % (PATH_WEKA,TMP_CSV,OUTPUT_FILE))

##################################################
# 3) Prepare data: create training and testing sets
print("creating training and testing sets...")
train_and_test(OUTPUT_FILE)

print("you are all set!")
##################################################
# 4) Clean working directory
if args.rmtemp:
  print("[rm option enabled] cleaning temp files!")
  os.system("rm %s" % TMP_CSV)
