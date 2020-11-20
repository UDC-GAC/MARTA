#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# File              : weka_cmd.py
# Author            : Marcos Horro <marcos.horro@udc.gal>
# Date              : Mér 06 Nov 2019 21:00:44 MST
# Last Modified Date: Xov 14 Nov 2019 10:16:03 MST
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

path_weka = "~/Descargas/weka-3-8-4"
weka_jar = path_weka + "/weka.jar"


def convert_csv_to_arff(tmp_csv, outputfile):
    os.system(
        f"java -cp {weka_jar} weka.core.converters.CSVLoader {tmp_csv} -B 100000 > {outputfile}")


def produce_class_outputs(alg, folderpath, testfile, err_out):
    os.system(f"java -cp {weka_jar}"
              " weka.classifiers.trees.{alg}"
              " -l {folderpath}/output.model -T {testfile} -p 0"
              "  > {folderpath}/pred.txt {err_out}")


def produce_tester_stats(alg, folderpath, testfile, err_out):
    os.system(f"java -cp {weka_jar}"
              " weka.classifiers.trees.{alg}"
              " -l {folderpath}/output.model -T {testfile}"
              "  > {folderpath}/model_test_stats.csv {err_out}")


def params_to_str(alg, params):
    str_params = f"_{str(alg)}"
    for k, v in params.items():
        str_params += (f"_{str(k)}{str(v)}")
    return str_params


def train_model(alg, params, opts, trainfile, folderpath, err_out):
    str_params = ""
    for k, v in params.items():
        str_params += (f" -{str(k)} {str(v)}")
    str_opts = ""
    for opt in opts.split(" "):
        str_opts += f"-{str(opt)} "
    os.system(f"java -cp {weka_jar}"
              " weka.classifiers.trees.{alg}"
              " {str_params} {str_opts} -t {trainfile} -d {folderpath}/output.model"
              "  > {folderpath}/model_learn_stats.txt {err_out}")
