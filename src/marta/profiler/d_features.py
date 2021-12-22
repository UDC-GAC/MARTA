# Copyright (c) Colorado State University. 2019-2021
# Copyright (c) Universidade da Coruña. 2019-2021
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
#
# Author: Marcos Horro <marcos.horro@udc.es>
#
# -*- coding: utf-8 -*-

import os
import copy
import itertools as it
import pickle
import glob

# Do not remove this: d_features may contain formulas using numpy functions
import numpy as np

from marta.utils.marta_utilities import perror


class Feature:
    def __init__(self, name: str, cfg: dict) -> None:
        self.name = name
        self.type_feature = cfg.get("type", "static")
        self.is_path = cfg.get("path", False)
        self.restrictions = cfg.get("restrict")
        self.value = cfg.get("value")
        self.params_values = cfg.get("value")


def dict_product(dicts: dict, kernel_cfg: list):
    """
    Generate the product of different dictionaries in a serializable
    fashion, since `dict_keys` is not serializable.

    >>> list(dict_product(dict(number=[1,2], character='ab')))
    [{'character': 'a', 'number': 1},
    {'character': 'a', 'number': 2},
    {'character': 'b', 'number': 1},
    {'character': 'b', 'number': 2}]
    """
    dicts.update({"KERNEL_CFG": kernel_cfg})
    values = [
        dicts[d] if isinstance(dicts[d], list) else dicts[d].params_values
        for d in dicts
    ]
    values_filtered = []
    restrictions = {}
    for key in dicts:
        if not isinstance(dicts[key], Feature):
            continue
        restr = dicts[key].restrictions
        if not restr is None:
            restrictions[key] = restr
    if len(restrictions) == 0:
        return (pickle.dumps(dict(zip(dicts, x))) for x in it.product(*values))
    for x in it.product(*values):
        tmp_dict = dict(zip(dicts, x))
        for key in dicts:
            restr = restrictions.get(key)
            if not restr is None:
                for _key in dicts:
                    rp = restr.replace(_key, f"tmp_dict['{_key}']")
                    if rp == restr:
                        continue
                    try:
                        if not eval(rp):
                            tmp_dict.pop(key)
                            break
                    except Exception:
                        continue

        if not (tmp_dict in values_filtered):  # avoid duplicates
            values_filtered.append(tmp_dict)
    return (pickle.dumps(x) for x in values_filtered)


def get_params_values(params_dict, f, feature, path):
    params_values = [feature]
    if isinstance(f.value, str):
        try:
            to_eval = f.value
            if f.is_path:
                if isinstance(to_eval, list):
                    new_list = []
                    for val in to_eval:
                        new_list.append(val.replace("[PATH]", f"{os.getcwd()}/{path}"))
                    to_eval = new_list
                elif isinstance(to_eval, str):
                    to_eval = to_eval.replace("[PATH]", f"{os.getcwd()}/{path}")
            if f.type_feature == "dependent":
                for key in params_dict:
                    to_eval.replace(key, params_dict[key])
            params_values = eval(to_eval)
        except NameError as name:
            perror(f"Evaluation of expression for {feature} went wrong: {name}")
        except Exception as err:
            perror(f"{feature}: {err}")
    return params_values


def eval_features(d_features: dict, path: str) -> dict:
    """
    Evaluate features from configuration file

    Example:

    "it.combinations(range(0,4),2)"

    This would generate a list of values such as: (0,1), (0,2), (0,3), (1,2), etc.

    :param feat: Dictionary of strings
    :type feat: dict
    :return: Returns a dict with all features or parameters properly expanded
    :rtype: dict
    """
    params_dict = {}
    for feature in d_features.keys():
        f = Feature(feature, d_features[feature])
        params_values = get_params_values(params_dict, f, d_features[feature], path)
        # This is useful for iterators, such as permutations, combinations...
        if f.type_feature == "dynamic":
            try:
                size = len(params_values)
            except TypeError:
                tmp_eval_copy = copy.deepcopy(params_values)
                for t in tmp_eval_copy:
                    size = len(t)
                    break
            for i in range(size):
                new_f = copy.deepcopy(f)
                new_f.params_values = [params_values]
                params_dict[f"{feature}{str(i)}"] = new_f
        else:
            try:
                f.params_values = list(params_values)
            except TypeError:
                f.params_values = params_values
            params_dict[feature] = f
    return params_dict
