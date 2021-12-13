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
from scipy.signal import find_peaks
import numpy as np

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
    pinfo(f"Saving {cfg.type} plot in '{output_file}.{cfg.format}'")
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
        kde_keys = ["x", "hue", "y", "log_scale"]
        new_cfg = {k: getattr(cfg, k) for k in kde_keys if k in vars(cfg)}
        p = sns.kdeplot(data=data, **new_cfg)
        lines_set = p.get_lines()
        ax.cla()
        ax.relim()
        n_colors = len(np.unique(data[cfg.hue].values))
        p = sns.kdeplot(
            data=data,
            **new_cfg,
            palette=sns.light_palette("crimson", n_colors=n_colors),
            multiple=cfg.multiple,
        )
        if cfg.mark_centroids:
            for line in lines_set:
                x, y = line.get_data()
                peaks = find_peaks(y, distance=1, width=9)[0]
                for peak in peaks:
                    plt.axvline(x[peak], color="red", linestyle="dotted")
                    ticks = ax.get_xticks()
                    labels = ax.get_xticklabels()
                    idx = ticks.searchsorted(x[peak])
                    ticks = np.concatenate(
                        (ticks[:idx], [round(x[peak], 2)], ticks[idx:])
                    )
                    ax.set_xticks(ticks)
                    # Is this genius or stupid?
                    labels = [""] * len(ticks)
                    max_diff = max(ticks) - min(ticks)
                    for i in range(len(ticks) - 1):
                        diff = ticks[i + 1] - ticks[i]
                        if diff < 0.03 * max_diff:
                            labels[i] = ""
                        else:
                            labels[i] = ticks[i]
                    ax.set_xticklabels(labels, rotation=45, ha="right")
        ax.yaxis.tick_left()
        ax.xaxis.tick_bottom()
        ax.autoscale()
    elif cfg.type == "catplot":
        sns.set(font_scale=cfg.font_scale)
        sns.set_style("whitegrid", {"axes.grid": False})
        n_colors = len(np.unique(data[cfg.hue].values))
        fig = plot_type(
            x=cfg.x,
            hue=cfg.hue,
            kind=cfg.kind,
            data=data,
            col=cfg.col,
            palette=sns.light_palette("crimson", n_colors=n_colors),
            edgecolor=".1",
        )
        if cfg.labels_catplot != None:
            fig.set_axis_labels("", "Count")
            fig.set_xticklabels(cfg.labels_catplot)

        sns.move_legend(
            fig,
            "lower center",
            bbox_to_anchor=(0.5, 1),
            ncol=3,
            title=None,
            frameon=False,
        )
    elif cfg.type == "jointplot":
        plot_type(
            data=data, x=cfg.x, y=cfg.y, hue=cfg.hue, size=cfg.size,
        )
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

    if cfg.hatches and cfg.type not in ["catplot", "relplot"]:
        hatches = ["", "/", "\\", "|", "-", "+", "x", "o", "O", ".", "*"]
        for leg, hatch in zip(ax.legend_.legendHandles, hatches):
            leg.set_hatch(hatch)
        for collection, hatch in zip(ax.collections[::-1], hatches):
            collection.set_hatch(hatch)

    if cfg.rugplot:
        import matplotlib.patheffects as pe

        sns.rugplot(
            data=data,
            x=cfg.x,
            hue=cfg.hue,
            palette=sns.light_palette("crimson", n_colors=n_colors),
            height=-0.02,
            clip_on=False,
            legend=False,
            path_effects=[
                pe.PathPatchEffect(edgecolor="black", linewidth=2),
                pe.Normal(),
            ],
        )

    fig.tight_layout()  # adjust padding
    output_file = f"{output_file.split('.')[0]}.{cfg.format}"
    fig.savefig(output_file, format=cfg.format)
