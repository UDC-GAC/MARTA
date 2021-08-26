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

from sklearn.tree import _tree
from sklearn.tree import _criterion
from sklearn.tree._export import _BaseTreeExporter
import numpy as np


def node_to_str_custom(self, tree, node_id, criterion):
    # Generate the node content string
    if tree.n_outputs == 1:
        value = tree.value[node_id][0, :]
    else:
        value = tree.value[node_id]

    # Should labels be shown?
    labels = (self.label == "root" and node_id == 0) or self.label == "all"

    characters = self.characters
    node_string = characters[-1]

    # Write node ID
    if self.node_ids:
        if labels:
            node_string += "node "
        node_string += characters[0] + str(node_id) + characters[4]

    # Write decision criteria
    if tree.children_left[node_id] != _tree.TREE_LEAF:
        # Always write node decision criteria, except for leaves
        if self.feature_names is not None:
            feature = self.feature_names[tree.feature[node_id]]
        else:
            feature = "X%s%s%s" % (characters[1], tree.feature[node_id], characters[2],)
        node_string += "%s %s %s%s" % (
            feature,
            characters[3],
            round(tree.threshold[node_id], self.precision),
            characters[4],
        )
        node_string += "\n"

    # Write impurity
    if self.impurity:
        if isinstance(criterion, _criterion.FriedmanMSE):
            criterion = "friedman_mse"
        elif isinstance(criterion, _criterion.MSE) or criterion == "squared_error":
            criterion = "squared_error"
        elif not isinstance(criterion, str):
            criterion = "impurity"
        if labels:
            node_string += "%s = " % criterion
        node_string += (
            str(round(tree.impurity[node_id], self.precision)) + characters[4]
        )

    # Write node sample count
    # if labels:
    #     node_string += "samples = "
    if self.proportion:
        percent = 100.0 * tree.n_node_samples[node_id] / float(tree.n_node_samples[0])
        node_string += str(round(percent, 1)) + "%" + characters[4]
    # else:
    #     node_string += str(tree.n_node_samples[node_id]) + characters[4]

    # Write node class distribution / regression value
    # if self.proportion and tree.n_classes[0] != 1:
    #     # For classification this will show the proportion of samples
    #     value = value / tree.weighted_n_node_samples[node_id]
    # if labels:
    #     node_string += "value = "
    # if tree.n_classes[0] == 1:
    #     # Regression
    #     value_text = np.around(value, self.precision)
    # elif self.proportion:
    #     # Classification
    #     value_text = np.around(value, self.precision)
    # elif np.all(np.equal(np.mod(value, 1), 0)):
    #     # Classification without floating-point weights
    #     value_text = value.astype(int)
    # else:
    #     # Classification with floating-point weights
    #     value_text = np.around(value, self.precision)
    # # Strip whitespace
    # value_text = str(value_text.astype("S32")).replace("b'", "'")
    # value_text = value_text.replace("' '", ", ").replace("'", "")
    # if tree.n_classes[0] == 1 and tree.n_outputs == 1:
    #     value_text = value_text.replace("[", "").replace("]", "")
    # value_text = value_text.replace("\n ", characters[4])
    # node_string += value_text + characters[4]

    # Write node majority class
    if self.class_names is not None and tree.n_classes[0] != 1 and tree.n_outputs == 1:
        # Only done for single-output classification trees
        if labels:
            node_string += "class = "
        if self.class_names is not True:
            class_name = self.class_names[np.argmax(value)]
        else:
            class_name = "y%s%s%s" % (characters[1], np.argmax(value), characters[2],)
        node_string += class_name

    # Clean up any trailing newlines
    if node_string.endswith(characters[4]):
        node_string = node_string[: -len(characters[4])]

    return node_string + characters[5]


_BaseTreeExporter.node_to_str = node_to_str_custom
