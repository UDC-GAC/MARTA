#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# File              : wrapper.py
# Author            : Marcos Horro <marcos.horro@udc.gal>
# Date              : Xov 31 Out 2019 09:56:07 MDT
# Last Modified Date: Ven 15 Nov 2019 15:49:01 MST
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


from common.utilities import pr_debug
from common.utilities import pr_col
from common.utilities import colors as c
from common.utilities import grep_file2file


def parse_arguments():
    parser = argparse.ArgumentParser(
        description="wrapper for preparing data given a csv"
    )
    required_named = parser.add_argument_group("required named arguments")
    required_named.add_argument("-i", "--input", help="input file name", required=True)
    return parser.parse_args()


if __name__ == "__main__":
    #############################
    # Parsing CLI inputs
    #############################
    args = parse_arguments()

    ##################################################
    # parsing all the arguments from the config.yml
    yml_config = args.input
    with open(yml_config, "r") as ymlfile:
        cfg = yaml.load(ymlfile, Loader=yaml.FullLoader)

    # general config
    general_cfg = cfg[0]["kernel"]
    input_file = general_cfg["input"]
    output_file = general_cfg["output"]
    force_replacement = general_cfg["overwrite"]
    rm_temp_files = general_cfg["clean"]
    print_debug = general_cfg["debug"]

    # prepare data
    prepdata_cfg = cfg[1]["prepare_data"]
    filter_cols = "-c " + prepdata_cfg["cols"] if len(prepdata_cfg["cols"]) else ""
    filter_rows = "-r " + prepdata_cfg["rows"] if len(prepdata_cfg["rows"]) else ""
    pred = prepdata_cfg["pred"]
    norm = "--norm" if prepdata_cfg["norm"]["enabled"] else ""
    norm_type = prepdata_cfg["norm"]["type"]
    ncats = prepdata_cfg["cats"]["num"]
    catscale = prepdata_cfg["cats"]["scale_factor"]
    dtalg = prepdata_cfg["dt_settings"]["name"]
    dtparams = prepdata_cfg["dt_settings"]["params"]
    dtopts = prepdata_cfg["dt_settings"]["opts"]
    min_acc = prepdata_cfg["min_acc"]

    # recommender
    recommender_cfg = cfg[2]["recommender"]
    interest_value = recommender_cfg["interest_dim"]["value"]
    interest_value_t = recommender_cfg["interest_dim"]["type"]
    dimensions = recommender_cfg["dim"]

    # preparing temp file
    tmp_csv = "___tmp_" + str(input_file.split("/")[-1])
    summ_file = "___tmp__summ_file.txt"
    os.system('echo "summary of results: " > %s' % (summ_file))

    ##################################################
    # some comprobations
    if not os.path.exists(input_file):
        pr_col(
            c.fg.red, "[error] introduce a valid input file in " + yml_config + " file"
        )
        exit(-1)

    ##################################################
    # executing experiments
    pr_col(c.fg.green, "[wrapper] executing wrapper...")
    cmd_line = (
        "python3 prepare_data.py -i %s -o %s"
        " %s %s --pred=%s --ncats=%s --catscale=%s"
        " %s -dt %s -dtp %s -dto %s %s"
        % (
            input_file,
            output_file,
            filter_rows,
            filter_cols,
            pred,
            str(ncats),
            str(catscale),
            norm,
            dtalg,
            dtparams,
            dtopts,
            ("--rmtemp" if rm_temp_files else ""),
        )
    )
    pr_debug(print_debug, cmd_line)
    ret = os.system(cmd_line)

    if ret != 0:
        pr_col(c.fg.red, "[wrapper] something went wrong!")
        exit(1)
    suffix_dtparams = (
        "" if len(dtparams) == 0 else "_" + dtparams.replace("=", "").replace(" ", "_")
    )
    suffix = "_" + str(dtalg) + suffix_dtparams
    res_file = "results/model_learn_stats_%s%s" % (str(pred), suffix)

    ##################################################
    # parsing results
    os.system(
        "cp results/exp_%s_all%s/model_learn_stats.txt"
        " %s" % (output_file.split(".")[0], suffix, res_file)
    )
    acc = grep_file2file("Correctly", res_file, summ_file)
    acc = (
        float(grep_file2file("Correlation coefficient", res_file, summ_file))
        if acc == None
        else float(acc) / 100
    )
    grep_file2file("Mean absolute error", res_file, summ_file)
    grep_file2file("Relative absolute error", res_file, summ_file)
    grep_file2file("Total number of instances", res_file, summ_file)
    tree_size = grep_file2file("Size of the tree", res_file, summ_file)

    ##################################################
    # results obtained
    pr_col(c.fg.green, "[wrapper] displaying summary of results")
    os.system("cat %s" % summ_file)
    if min_acc > acc:
        pr_col(
            c.fg.red, "[error] minimum accuracy (%s) not achieved (%s)" % (min_acc, acc)
        )
        exit(-1)
    pr_col(c.fg.green, "[wrapper] finished! cleaning temp files...")

    ##################################################
    # copy results for parsing tree
    parsing_tree_file = "___tmp_tree.txt"
    os.system("cp %s %s" % (res_file, parsing_tree_file))

    pr_col(c.fg.green, "[wrapper] executing recommender.py")
    os.system(
        "python3 recommender.py -i %s -c %s -p %s -v %s -t %s -d %s -dt %s"
        % (
            parsing_tree_file,
            tmp_csv,
            pred,
            interest_value,
            interest_value_t,
            dimensions,
            dtalg,
        )
    )

    ##################################################
    # remove tmp files
    if rm_temp_files:
        os.system("rm %s" % summ_file)
        os.system("rm %s" % parsing_tree_file)
        os.system("rm %s" % tmp_csv)
