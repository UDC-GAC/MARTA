# Copyright 2021 Marcos Horro
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

# -*- coding: utf-8 -*-

# Standard libraries
from typing import Optional, Tuple

# Third-party libraries
import pandas as pd
import numpy as np
from sklearn.neighbors import KernelDensity
from sklearn.model_selection import GridSearchCV
from scipy.signal import argrelextrema


# Local imports
from marta.utils.marta_utilities import perror, pinfo


def column_strings_to_int(df: pd.DataFrame, columns: list) -> pd.DataFrame:
    """Given a DataFrame, it converts columns with object type to int

    :param df: Original data.
    :type df: pd.DataFrame
    :return: Same as original but with converted types.
    :rtype: pd.DataFrame
    """
    for col in columns:
        if df[col].values.dtype == np.dtype("object"):
            l = np.unique(df[col])
            d = dict(zip(l, range(len(l))))
            df.loc[:, col] = df[col].apply(lambda x: d[x])
            pinfo(
                f"Converting column '{col}' from object to int values. New assigned values are:"
            )
            for key in d:
                pinfo(f"{key} => {d[key]}")
    return df


def categorize_target_dimension(
    df: pd.DataFrame, target_value: str, ncat: int, catscale: float, grid_search=False
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

    if grid_search:
        pinfo(
            "Finding best bandwidth parameter for kernel density estimation (KDE). This might take a while..."
        )
        bw_space = np.linspace(0.001, 1.0, 30)
        grid = GridSearchCV(
            KernelDensity(),
            {"bandwidth": bw_space},
            cv=10,  # 10 cross validations
            n_jobs=-1,  # all cores
        )
        grid.fit(X)
        bw = grid.best_params_["bandwidth"]
        pinfo(f"Best bandwidth parameter: {bw}")
    else:
        bw = 0.5
    pinfo(
        "KDE for getting the number of clusters to use, i.e. the number of categories"
    )
    kde = KernelDensity(bandwidth=bw).fit(X)
    score_samples_space = np.linspace(min(X), max(X), 100).reshape(1, -1)[0]
    e = kde.score_samples(score_samples_space.reshape(-1, 1))
    mi = argrelextrema(e, np.less)[0]

    P = [X[X < score_samples_space[mi][0]]]
    for i in range(len(mi) - 1):
        P.append(
            X[(X >= score_samples_space[mi][i]) * (X <= score_samples_space[mi][i + 1])]
        )
    if len(mi) >= 1:
        P.append(X[X >= score_samples_space[mi][-1]])

    labels = []
    for cat in P:
        new_label = "{0}-{1}-{2}".format(
            target_value, "{0:.3f}".format(min(cat)), "{0:.3f}".format(max(cat))
        )
        labels.append(new_label)
        pinfo(f"    New category created = {new_label}")

    tmp_target_value = getattr(df, target_value)

    if len(set(labels)) != len(labels):
        perror(
            "There might be duplicated labels when creating categories. "
            "This is due to normalization and scaling issues normally. "
            "Please revise the settings in the configuration file."
        )

    setattr(df, target_value, pd.cut(tmp_target_value, len(P), labels=labels))
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
