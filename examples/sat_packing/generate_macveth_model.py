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

import sys
import pandas as pd


def prepare_model(input_file, output_file, arch, isa):
    if not input_file.endswith(".csv"):
        print("Input file must be a CSV file")
        exit(1)
    df = pd.read_csv(input_file)
    file_name = df["PACKING_TEMPLATE"].str.rsplit("/", 1).apply(lambda x: x[-1][:-2])
    df["PACKING_TEMPLATE"] = (
        df["PACKING_TEMPLATE"].str.rsplit("/", 1).apply(lambda x: x[-1])
    )
    df["signature"] = (
        file_name.str.split("elems_")
        .apply(lambda x: x[-1])
        .str.replace("nnz", "")
        .str.rsplit("_", 1)
        .apply(lambda x: x[0])
    )
    df["version"] = file_name.str.rsplit("_", 1).apply(lambda x: int(x[-1]))
    df["arch"] = arch
    df["isa"] = isa
    df["datatype"] = file_name.str.split("_").apply(lambda x: x[1])
    # df["cost"] = df["tsc"].apply(lambda x: int(x))
    df["cost"] = df["UNHALTED_CORE_CYCLES"].apply(lambda x: int(x))
    df["nelems"] = (
        file_name.str.split("nnz").apply(lambda x: x[0][-1]).apply(lambda x: int(x))
    )
    columns = ["signature", "cost", "arch", "isa", "datatype", "version"]
    df.sort_values(
        by=["nelems", "cost", "INSTRUCTIONS_RETIRED"], inplace=True, ignore_index=True
    )
    model = df[columns]
    tmp = (
        model.loc[model.groupby("signature").cost.idxmin()]
        .reset_index()
        .drop("index", axis=1)
    )
    tmp.to_csv(output_file, index_label="id")


if __name__ == "__main__":
    if len(sys.argv) != 5:
        print(
            "Wrong number of params: <input>, <output>, <arch> and <isa> required, in that order"
        )
        exit(1)

    prepare_model(*sys.argv[1:])
