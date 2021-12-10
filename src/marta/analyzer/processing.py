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

# Standard libraries
from typing import Optional, Tuple

# Third-party libraries
import pandas as pd
import numpy as np
from KDEpy import FFTKDE
from sklearn.neighbors import KernelDensity
from sklearn.model_selection import GridSearchCV
from scipy.signal import argrelextrema
from sklearn.preprocessing import LabelEncoder


# Local imports
from marta.utils.marta_utilities import perror, pinfo


def column_strings_to_int(df: pd.DataFrame, columns: list) -> Tuple[pd.DataFrame, dict]:
    """Given a DataFrame, it converts columns with object type to int

    :param df: Original data.
    :type df: pd.DataFrame
    :return: Same as original but with converted types.
    :rtype: pd.DataFrame
    """
    encoders = {}
    for col in columns:
        if df[col].values.dtype == np.dtype("object"):
            labelencoder = LabelEncoder()
            df[col] = labelencoder.fit_transform(df[col])
            pinfo(
                f"Converting column '{col}' from object to int values. New assigned values are:"
            )
            for i in range(len(labelencoder.classes_)):
                pinfo(f"{labelencoder.inverse_transform([i])[0]} => {i}")
            encoders[col] = labelencoder
    return df, encoders


def grid_search(X: pd.Series) -> Tuple[float, str]:
    bw_space = np.linspace(0.0, 1.0, 30)
    kernels = [
        "cosine",
        "epanechnikov",
        "exponential",
        "gaussian",
        "linear",
        "tophat",
    ]
    grid = GridSearchCV(
        KernelDensity(), {"bandwidth": bw_space, "kernel": kernels}, n_jobs=-1,
    )
    pinfo(
        "Finding best bandwidth parameter for kernel density estimation (KDE). This might take a while..."
    )
    grid.fit(X)
    return grid.best_params_["bandwidth"], grid.best_params_["kernel"]


def categorize_target_dimension(
    df: pd.DataFrame,
    target_value: str,
    ncat: int,
    catscale: float,
    mode="normal",
    grid_search=False,
    custom_params=False,
    bandwidth=1.0,
    bandwidth_type="silverman",
    kernel="linear",
) -> Tuple[pd.DataFrame, list]:
    """Create categories for a continuous dimension.

    :param df: Input data
    :type df: pd.DataFrame
    :param target_value: Target dimension.
    :type target_value: str
    :param ncat: Number of categories to create.
    :type ncat: int
    :param catscale: Scaling factor of the category.
    :type catscale: float
    :return: Data processed with the list of labels assigned to continuous intervals.
    :rtype: Tuple[pd.DataFrame, list]
    """
    X = getattr(df, target_value).values[:, np.newaxis]
    X /= catscale
    if ncat == None:
        return df, X

    score_samples_space = np.linspace(min(X), max(X), int(len(X))).reshape(1, -1)[0]
    if mode != "normal":
        if grid_search:
            bw, kern = grid_search(X)
            pinfo(f"Best parameters for KDE: bandwidth = {bw}; kernel = {kern}")
            kde = KernelDensity(bandwidth=bw, kernel=kern).fit(X)
            e = kde.score_samples(score_samples_space.reshape(-1, 1))
        elif custom_params:
            kde = KernelDensity(bandwidth=bandwidth, kernel=kernel).fit(X)
            e = kde.score_samples(score_samples_space.reshape(-1, 1))
        else:
            _, e = FFTKDE(kernel="gaussian", bw=bandwidth_type).fit(X).evaluate(len(X))
    else:
        _, e = FFTKDE(kernel="gaussian", bw="silverman").fit(X).evaluate(len(X))
    mi = argrelextrema(e, np.less)[0]

    P = [X[X < score_samples_space[mi][0]]]
    for i in range(len(mi) - 1):
        new_interval = X[
            (X >= score_samples_space[mi][i]) * (X <= score_samples_space[mi][i + 1])
        ]
        if len(new_interval) >= 2:
            P.append(new_interval)
    if len(mi) >= 1:
        P.append(X[X >= score_samples_space[mi][-1]])

    intervals = []
    for sub_int in P:
        intervals.append(min(sub_int))
    intervals.append(max(P[-1]))

    labels = []
    for cat in P:
        new_label = f"{target_value}-{min(cat):06.3f}-{max(cat):06.3f}"
        labels.append(new_label)
        pinfo(f"    New category created = {new_label}")

    tmp_target_value = getattr(df, target_value)

    if len(set(labels)) != len(labels):
        perror(
            "There might be duplicated labels when creating categories. "
            "This is due to normalization and scaling issues normally. "
            "Please revise the settings in the configuration file."
        )

    df[f"{target_value}_cat"] = pd.cut(
        tmp_target_value, intervals, labels=labels, include_lowest=True
    )
    return df, labels


def normalize_data(
    df: pd.DataFrame, norm: Optional[str], target_value: str
) -> pd.DataFrame:
    """Normalization of data according to the type

    :param df: Input data
    :type df: pd.DataFrame
    :param norm: Type of normalization
    :type norm: Optional[str]
    :param target_value: Dimension to normalize
    :type target_value: str
    :return: Full data with target dimension normalized
    :rtype: pd.DataFrame
    """
    norm_min_max = norm in ["min_max", "minmax"]
    norm_z_score = norm in ["z_score", "zscore"]
    assert not (norm_min_max and norm_z_score)  # NAND
    if norm_min_max:
        setattr(
            df,
            target_value,
            getattr(df, target_value) - min(getattr(df, target_value)),
        )
        setattr(
            df,
            target_value,
            getattr(df, target_value) / max(getattr(df, target_value)),
        )
    if norm_z_score:
        # z-score
        setattr(df, target_value, np.log(getattr(df, target_value)))
        setattr(
            df,
            target_value,
            (getattr(df, target_value) - np.mean(getattr(df, target_value)))
            / np.std(getattr(df, target_value)),
        )
    return df
