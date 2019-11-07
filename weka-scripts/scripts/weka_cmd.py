#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# File              : weka_cmd.py
# Author            : Marcos Horro <marcos.horro@udc.gal>
# Date              : Mér 06 Nov 2019 21:00:44 MST
# Last Modified Date: Mér 06 Nov 2019 22:16:30 MST
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

import os

PATH_WEKA = "~/Descargas/weka-3-8-3"
WEKA_JAR = PATH_WEKA + "/weka.jar"


def convert_csv_to_arff(tmp_csv, outputfile):
    os.system("java -cp %s weka.core.converters.CSVLoader %s -B 100000 > %s" %
              (WEKA_JAR, tmp_csv, outputfile))


def produce_class_outputs(alg, folderpath, testfile, err_out):
    os.system("java -cp %s"
              " weka.classifiers.trees.%s"
              " -l %s/output.model -T %s -p 0"
              "  > %s/pred.txt %s"
              % (WEKA_JAR, alg, folderpath, testfile,
                 folderpath, err_out))


def produce_tester_stats(alg, folderpath, testfile, err_out):
    os.system("java -cp %s"
              " weka.classifiers.trees.%s"
              " -l %s/output.model -T %s"
              "  > %s/model_test_stats.csv %s"
              % (WEKA_JAR, alg, folderpath, testfile,
                 folderpath, err_out))


def params_to_str(alg, params):
    str_params = "_" + str(alg)
    for k, v in params.items():
        str_params += ("_" + str(k) + str(v))
    return str_params


def train_model(alg, params, trainfile, folderpath, err_out):
    str_params = ""
    for k, v in params.items():
        str_params += (" -" + str(k) + " " + str(v))
    os.system("java -cp %s"
              " weka.classifiers.trees.%s"
              " %s -t %s -d %s/output.model"
              "  > %s/model_learn_stats.txt %s"
              % (WEKA_JAR, alg, str_params, trainfile,
                 folderpath, folderpath, err_out))
