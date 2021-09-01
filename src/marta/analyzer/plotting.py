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

# Third-party libraries
import seaborn as sns
import pandas as pd
import matplotlib.pyplot as plt

# Local imports
from marta.analyzer.config import PlotCfg
from marta.utils.marta_utilities import perror, pinfo


def plot_data(data: pd.DataFrame, cfg: PlotCfg, output_file: str) -> None:
    """Just a simple wrapping function for plotting and saving figures.

    :param data: Input data.
    :type data: pd.DataFrame
    :param cfg: Configuration with all parameters needed for plotting.
    :type cfg: PlotCfg
    :param output_file: File to output plot.
    :type output_file: str
    """
    pinfo(f"Saving custom plot in '{output_file}'")
    plot_type = getattr(sns, cfg.type)
    if cfg.sort != None:
        data = (
            data.sort_values(cfg.sort, ascending=False)
            .reset_index()
            .drop("index", axis=1)
        )
    fig, ax = plt.subplots()
    if cfg.x == "index":
        cfg.x = data.index
    if cfg.type == "relplot":
        try:
            hue = data[cfg.hue].values
        except Exception:
            hue = None
        fig = plot_type(
            data=data,
            x=cfg.x,
            y=cfg.y,
            hue=hue,
            size=cfg.size,
            col=cfg.col,
            row=cfg.row,
            palette="hls",
        )
    elif cfg.type == "kdeplot":
        kde_keys = ["x", "y", "hue", "log_scale"]
        new_cfg = {k: getattr(cfg, k) for k in kde_keys if k in vars(cfg)}
        plot_type(data=data, **new_cfg, multiple="stack", alpha=0.5)
    else:
        plot_type(
            data=data, x=cfg.x, y=cfg.y, hue=cfg.hue, size=cfg.size,
        )
        sns.rugplot(data=data, x=cfg.x, y=cfg.y, hue=cfg.hue)
    if output_file == "":
        perror("Wrong file to save plot")
    if cfg.x_label != None:
        ax.set_xlabel(cfg.x_label)
    if cfg.y_label != None:
        ax.set_ylabel(cfg.y_label)
    fig.tight_layout()  # adjust padding
    output_file = f"{output_file.split('.')[0]}.{cfg.format}"
    fig.savefig(output_file, format=cfg.format)

