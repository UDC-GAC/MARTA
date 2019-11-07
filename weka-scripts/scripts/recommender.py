#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# File              : recommender.py
# Author            : Marcos Horro <marcos.horro@udc.gal>
# Date              : Mér 06 Nov 2019 17:54:44 MST
# Last Modified Date: Mér 06 Nov 2019 22:25:03 MST
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
from parse_tree import REPTree

##################################################
# parsing arguments
parser = argparse.ArgumentParser(
    description='')
requiredNamed = parser.add_argument_group('required named arguments')
requiredNamed.add_argument(
    '-i', '--input', help='input file name', required=True)
requiredNamed.add_argument('-v', '--value',  # action='store_const',
                           help='value we are looking for', required=True)
requiredNamed.add_argument('-d', '--dimensions', metavar='dim', type=str, nargs='+',
                           help='values we are interested on', required=True)
args = parser.parse_args()

INPUT_FILE = args.input
DIMENSIONS = args.dimensions
INTEREST_VALUE = args.value


# testing parsing tree
tree = REPTree(INPUT_FILE)
tree.print_parents_compressed_by_value(INTEREST_VALUE)
