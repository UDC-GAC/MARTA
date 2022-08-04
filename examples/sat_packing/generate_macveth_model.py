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
import numpy as np


def prepare_model(input_recipes, input_gather, output_file, arch, isa):
    if not input_recipes.endswith(".csv") or not input_gather.endswith( ".csv" ):
        print("Input file must be a CSV file")
        exit(1)
    df = pd.read_csv(input_recipes)
    file_name = df["PACKING_TEMPLATE"].str.rsplit("/", 1).apply(lambda x: x[-1][:-2])
    df["PACKING_TEMPLATE"] = (
        df["PACKING_TEMPLATE"].str.rsplit("/", 1).apply(lambda x: x[-1])
    )
    df["signature"] = (
        file_name.str.split("n")
        .apply(lambda x: x[-1])
        .str.rsplit("_", 1)
        .apply(lambda x: x[0])
    )
    df["version"] = file_name.str.rsplit("_", 1).apply(lambda x: int(x[-1]))
    df["arch"] = arch
    df["isa"] = isa
    df["datatype"] = file_name.str.split("_").apply(lambda x: x[0])
#    df["cost"] = df.tsc.apply( lambda x: x.replace("[","").replace("]","").split() ).apply( lambda x: list( map( float, x ) ) ).apply( np.mean )
#    df["cost"] = df["CYCLES_NOT_IN_HALT"].apply(lambda x: int(x))
    
    # First step: isolate recipes with best instruction count 
    df["cost"] = df["INSTRUCTIONS_RETIRED"].round()
    df2 = df[df.groupby("signature").cost.apply( lambda x: x == x.min() )]

    # Second step: isolate recipes with best uops count
    df2["cost"] = df2['UOPS_EXECUTED:THREAD'].round()
    df3=df2[df2.groupby("signature").cost.apply( lambda x: x == x.min() )]

    # Last step: get the best unhalted core cycles
    df3["cost"] = df3["UNHALTED_CORE_CYCLES"].round()
    df_recipes = df3.loc[df3.groupby("signature").cost.idxmin()]

    # Open gather results
    df_gather = pd.read_csv( input_gather )
    df_gather["contiguity"]=df_gather.apply( lambda x: [x.IDX0] + [x.IDX1] + [x.IDX2] + [x.IDX3] + [x.IDX4] + [x.IDX5] + [x.IDX6] + [x.IDX7], axis=1 ).apply( np.diff ).apply( lambda x: (x==1).astype(int).astype(str) )
    df_gather["signature"]=df_gather.contiguity.apply( lambda x: str(len(x)+1)+"_"+"_".join(x) )
    df_gather = df_gather.groupby( "signature" )[["UOPS_EXECUTED:THREAD","INSTRUCTIONS_RETIRED","UNHALTED_CORE_CYCLES"]].agg( lambda x: x.round().min() )

    # Merge and generate final model
    df_merge = pd.merge(df_recipes,df_gather,left_on="signature", right_index=True, how="outer")
    df_merge["INSTRUCTIONS_RETIRED_y"].fillna( df_merge["INSTRUCTIONS_RETIRED_x"], inplace=True )
    mask = (df_merge["INSTRUCTIONS_RETIRED_x"] <= df_merge["INSTRUCTIONS_RETIRED_y"])
    df_model = df_recipes.loc[mask.index[mask]]
    df_model["arch"] = arch
    df_model["isa"] = isa
    df_model["datatype"] = file_name.str.split("_").apply(lambda x: x[0])

    df = df_model
    df["nelems"] = (
        file_name.str.split("nnz").apply(lambda x: x[0][-1]).apply(lambda x: int(x))
    )
    columns = ["signature", "cost", "arch", "isa", "datatype", "version"]
#    df.sort_values(
#        by=["nelems", "cost", "RETIRED_INSTRUCTIONS"], inplace=True, ignore_index=True
#    )
    model = df[columns]
    tmp = (
        model.loc[model.groupby("signature").cost.idxmin()]
        .reset_index()
        .drop("index", axis=1)
    )
    tmp.to_csv(output_file, index_label="id")
    return df_model


if __name__ == "__main__":
    if len(sys.argv) != 6:
        print(
            "Wrong number of params: <input-recipes>, <input-gather>, <output>, <arch> and <isa> required, in that order"
        )
        exit(1)

    df = prepare_model(*sys.argv[1:])
