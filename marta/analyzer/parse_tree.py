#!/usr/bin/env python
# -*- coding: utf-8 -*-
# File              : parse_tree.py
# Author            : Marcos Horro <marcos.horro@udc.gal>
# Date              : Mar 04 Nov 2019 11:08:25 MST
# Last Modified Date: Mar 12 Nov 2019 11:59:51 MST
# Last Modified By  : Marcos Horro <marcos.horro@udc.gal>
#
# Copyright (c) 2019 Computer Architecture Group, Universidade da Coruña
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
# Authors: Marcos Horro

import re
import os
import sys
import numpy as np
from utils.utilities import pr_col
from utils.utilities import colors as c

alg_template = {
    "REPTree": (re.compile("REPTree"), re.compile("^=*\n$"), re.compile("^[\t\n]*$")),
    "J48": (
        re.compile("J48 (un)?pruned tree"),
        re.compile("^-*\n$"),
        re.compile("^[ \t\n]*$"),
    ),
}


class InfoNode:
    def __init__(self, feature, comparator, value):
        self.feature = feature
        self.comparator = comparator
        self.value = value

    def __str__(self):
        return "[%s %s %s]" % (str(self.feature), str(self.comparator), str(self.value))

    def get_values(self):
        return self.feature, self.comparator, self.value


class InfoCat:
    def __init__(self, value):
        self.value = value

    def __str__(self):
        return "cat = %s" % self.value


class Node:
    """Definition of node"""

    def __init__(self):
        self.info = None
        self.child = []
        self.parent = None

    def __str__(self):
        """Debugging purposes mostly"""
        string = "node: %s\n" % (str(self.info))
        if self.child != []:
            for c in self.child:
                cline = str(c).strip().split("\n")
                for l in cline:
                    string += " %s\n" % str(l)
        return string

    def set_info(self, info):
        """Setting info of node, can be whatever"""
        self.info = info

    def is_leave(self):
        """Leaves do not have children"""
        return self.child == []

    def get_leaves(self, leaves):
        """Recursive method for getting all the leaves.
        Returns a list of Node objects"""
        if self.is_leave():
            leaves += [self]
            return leaves
        else:
            for c in self.child:
                leaves = c.get_leaves(leaves)
            return leaves

    def append_node(self, node):
        """When appending node, need to track its parent"""
        node.parent = self
        self.child += [node]


class ClassTree:
    def __init__(self):
        self.root = Node()
        self.depth = 1

    def get_root(self):
        return self.root

    def get_leaves(self):
        return self.root.get_leaves([])

    def __str__(self):
        return str(self.root)


# parsing based on https://github.com/rudi-c/weka-json-parser/


class DTTree(ClassTree):
    """
    DTTree class, which generates a tree from an input file
    """

    def __init__(self, file, alg):
        super().__init__()
        lines = ""
        with open(file, "r") as f:
            lines = f.readlines()
        tree_lines = self.get_tree_lines(lines, alg)
        tree = self.parse_tree(tree_lines, self.root)
        self.root = tree

    def get_value_range(self, value):
        leaves = self.root.get_leaves([])
        cand = np.arange(0)
        for leaf in leaves:
            leaf_range = (leaf.info.value).strip().replace("I-", "")
            cand = np.append(cand, leaf_range)
            min_val, max_val = leaf_range.split("-")
            if eval("%s <= %s" % (min_val, value)) and eval(
                "%s <= %s" % (value, max_val)
            ):
                return leaf.info.value
        pr_col(
            c.fg.red,
            "[ERROR] Interest value out of range: %s\n\tPossible"
            " values: %s" % (value, np.unique(cand)),
        )
        exit(-1)

    def get_parents_compressed_by_value(self, value):
        """
        Get leaves of the tree according to a given value
        """
        leaves = self.root.get_leaves([])
        new_leaves = []
        for leaf in leaves:
            if leaf.info.value != value:
                continue
            new_leaves += [leaf]
        return self.aux_reverse_tree_compressed(new_leaves, {})

    def print_parents_compressed_by_value(self, value):
        """
        Print parent nodes of leaves with a certain value
        """
        leaves = self.get_parents_compressed_by_value(value)
        self.print_reverse_tree_compressed(leaves)

    def print_reverse_tree_compressed(self, leaves):
        """
        Print reversed tree of a set of leaves
        """
        for leaf, d in leaves:
            print("for leaf = %s" % str(leaf.info))
            for k, v in d.items():
                print("\t%s: %s" % (k, v))

    def print_reverse_tree(self):
        """
        Print full reversed tree
        """
        leaves = self.root.get_leaves([])
        for leaf in leaves:
            parent = leaf.parent
            print("for leaf = %s" % str(leaf.info))
            sep = " "
            while parent != None:
                print("%snode = %s" % (sep, str(parent.info)))
                sep += " "
                parent = parent.parent

    @staticmethod
    def reduce_expression(d):
        # TODO:
        return d

    @staticmethod
    def evaluate_expression(feat, comp, val, d):
        if feat in d:
            if comp in d[feat]:
                val_1 = d[feat][comp]
                if eval(val + comp + val_1):
                    d[feat][comp] = val
                else:
                    d[feat][comp] = val_1
            else:
                d[feat][comp] = val
        else:
            d[feat] = {}
            d[feat][comp] = val
        return d

    @staticmethod
    def aux_reverse_tree_compressed(leaves, cond):
        """
        Auxiliar method for generating a reversed tree according to
        conditions
        """

        def cond_not_compatible(c1, c2):
            """
            Checks whether user and node conditions are compatible
            """
            op1, v1 = c1
            op2, v2 = c2
            return eval("%s %s %s" % (str(round(float(v1))), str(op2), str(v2)))

        leaves_tree = []
        for leaf in leaves:
            d = {}
            parent = leaf.parent
            cond_valid = True
            while parent.parent != None:
                feat, comp, val = parent.info.get_values()
                if feat in cond:
                    c, v = cond[feat]
                    if DTTree.cond_not_compatible((comp, val), (c, v)):
                        cond_valid = False
                        break
                d = DTTree.evaluate_expression(feat, comp, val, d)
                parent = parent.parent
            if cond_valid:
                d = DTTree.reduce_expression(d)
                leaves_tree += [(leaf, d)]
        return leaves_tree

    @staticmethod
    def parse_line(line):
        """
        Split the line into a tuple
        (depth, feature, comparator, value, classification/None)
        """
        # Avoid empty strings from double whitespaces and the likes.
        re_splitter = re.compile("[ :]")
        split = [l for l in re_splitter.split(line) if len(l) > 0]
        depth = 0
        for part in split:
            if part == "|":
                depth += 1
            else:
                break
        return (
            depth,
            split[depth],
            split[depth + 1],
            split[depth + 2],
            split[depth + 3] if len(split) > depth + 3 else None,
        )

    @staticmethod
    def parse_tree(lines, root):
        """
        Parses input lines into a decision tree
        """
        current_index = [0]  # need mutable container because of closure limitationssvg

        def parse(current_depth, root):
            """Helper recursive function"""
            node_feature = None
            while current_index[0] < len(lines):
                line = lines[current_index[0]]
                depth, feature, comparator, value, cat = DTTree.parse_line(line)
                if depth < current_depth:
                    # Finished parsing this node.
                    break
                elif depth == current_depth:
                    node = Node()
                    if node_feature is None:
                        node_feature = feature
                    elif node_feature != feature:
                        raise ValueError(
                            "Error : Feature mismatch - expected %s"
                            "but got : \n%s" % (node_feature, line)
                        )
                    # Another branch
                    current_index[0] += 1
                    info = InfoNode(node_feature, comparator, value)
                    node.set_info(info)
                    if cat is None:
                        parse(current_depth + 1, node)
                    else:
                        leaf = Node()
                        leaf.set_info(InfoCat(cat))
                        node.append_node(leaf)
                    root.append_node(node)
                else:
                    raise ValueError(
                        "Error : Input jumps two levels at once\n%s." % line
                    )
            return root

        try:
            parse(0, root)
        except ValueError:
            print("Something went wrong when parsing tree, quitting...")
            exit(1)
        root.set_info("ROOT")
        return root

    @staticmethod
    def get_tree_lines(lines, alg):
        """
        Return the lines of the input that correspond to the decision tree
        """
        re_head, re_divider_line, re_blank_line = alg_template[alg]
        tree_lines = []
        for i in range(len(lines) - 2):
            if re_head.match(lines[i]):
                assert re_divider_line.match(lines[i + 1]) and re_blank_line.match(
                    lines[i + 2]
                ), "Input not in expected format."
                for l in lines[i + 3 :]:
                    if re_blank_line.match(l):
                        return tree_lines
                    else:
                        tree_lines.append(l[:-1])  # remove newline at the end