#!/usr/bin/env python
# -*- coding: utf-8 -*-
# parser_data.py
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

import numpy as np
import pandas as pd
import sys
import os
import argparse

parser = argparse.ArgumentParser(description='This script permits performs transformations over a CSV file')
requiredNamed = parser.add_argument_group('required named arguments')
requiredNamed.add_argument('-i', '--input', help='Input file name', required=True)
requiredNamed.add_argument('-o', '--output', help='Output file name', required=True)
requiredNamed.add_argument('columns', metavar='col', type=str, nargs='+', help='columns to parse')

