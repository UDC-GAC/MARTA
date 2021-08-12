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

# Third-party libraries
import seaborn as sns
import pandas as pd
import matplotlib.pyplot as plt

# Local imports
from marta.analyzer.config import PlotCfg
from marta.utils.marta_utilities import perror, pinfo


def plot_data(data: pd.DataFrame, cfg: PlotCfg, output_file: str) -> None:
    pinfo(f"Saving custom plot in '{output_file}'")
    plot_type = getattr(sns, cfg.type)
    fig, ax = plt.subplots()
    if cfg.x_axis == "index":
        cfg.x_axis = data.index
    if cfg.type == "relplot":
        fig = plot_type(
            data=data,
            x=cfg.x_axis,
            y=cfg.y_axis,
            hue=cfg.hue,
            size=cfg.size,
            col=cfg.col,
            row=cfg.row,
            palette="hls",
        )
    else:
        plot_type(
            data=data, x=cfg.x_axis, y=cfg.y_axis, hue=cfg.hue, size=cfg.size,
        )
    if output_file == "":
        perror("Wrong file to save plot")
    if cfg.x_label != None:
        ax.set_xlabel(cfg.x_label)
    if cfg.y_label != None:
        ax.set_ylabel(cfg.y_label)
    fig.tight_layout()  # adjust padding
    if cfg.format != "png" and not output_file.endswith(cfg.format):
        output_file = f"{output_file.split('.')[0]}.{cfg.format}"
    fig.savefig(output_file, format=cfg.format)

