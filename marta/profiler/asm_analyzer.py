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
import re
from abc import ABC, abstractmethod

# Local imports
from profiler.marta_utilities import perror, pwarning


class ASMParserFactory:
    @staticmethod
    def parse_asm(asm_type: str, asm_file: str):
        if asm_type != "att" and asm_type != "intel":
            asm_type = "att"
            pwarning(
                "Check the asm_syntax value, does not match 'att' nor 'intel'. Using 'att' by default."
            )
        if asm_type == "att":
            return ASMParserATT.parse_asm(asm_file)
        else:
            return ASMParserIntel.parse_asm(asm_file)


class ASMParser(ABC):
    @staticmethod
    @abstractmethod
    def parse_asm(asm_file):
        pass

    @staticmethod
    def skip_asm_instruction(ins: list[str]) -> bool:
        """
        Auxiliary function for skipping certain ASM operations

        :param ins: Instructions to analyze
        :type ins: str
        :return: `True` if assembly instruction must be skipped
        :rtype: bool
        """

        if ins[0] == "" or ins[0][0] == ".":
            return True
        for i in ins:
            if i == "ret" or i == "endbr64":
                return True
        return False

    @staticmethod
    def tokenize_instruction(tok: list[str]) -> list[str]:
        if len(tok) == 1:
            tok = tok[0].split(" ")
            tok = [t for t in tok if t != "" and t[0] != "#"]
        return tok


class ASMParserATT(ASMParser):
    @staticmethod
    def operand_to_suffix(op: str) -> str:
        op = op.strip().replace(" ", "")
        if (
            (op.startswith("%zmm"))
            or (op.startswith("%ymm"))
            or (op.startswith("%xmm"))
        ):
            return op[1:4].upper()
        elif op.startswith("$"):
            return "IMM"
        elif op.startswith("%"):
            return "GPR"
        elif re.match("^[-0-9]*\(", op):
            return "MEM"
        elif op.startswith("."):
            return "LABEL"
        else:
            return "GPR"

    @staticmethod
    def get_raw_asm_type(ins: str) -> str:
        """
        Get ASM variant, i.e. mnemonic[_operand_type], where operand_type can be a
        register, memory or a immediate value

        :param ins: List of strings, where the first token is the mnemonic
        :type ins: list
        :return: ASM mnemonic with its operands
        :rtype: str
        """

        op_name = ins[0]
        if len(ins) < 2:
            return op_name
        if len(ins) > 2:
            operands = [op[:-1] if op[-1] == "," else op for op in ins[1:]]
        else:
            operands = [
                op[:-1] if op[-1] == "," else op for op in ins[1].strip().split(" ")
            ]
        if len(operands) != 0:
            # XED format is for Intel's syntax. AT&T and Intel differ in the
            # arguments, and, therefore, it is needed to reverse AT&T's
            for op in operands:
                op_name += f"_{ASMParserATT.operand_to_suffix(op.strip())}"
                op = op.strip()
        return op_name

    @staticmethod
    def parse_asm(asm_file: str) -> dict:
        """
        Parse the assembly file and get instructions within ROI

        :param asm_file: File name containing assembly instructions
        :type asm_file: str
        :return: Dictionary containing number of occurrences for an ASM instruction
        :rtype: dict
        """
        raw_inst = {}
        count = False
        try:
            with open(asm_file, "r") as f:
                # Get the previous contents
                lines = f.readlines()
                for line in lines:
                    if ".string" in line or ".ascii" in line or line == "\n":
                        continue
                    tok = line.strip().split("#")
                    tok = tok[0].strip().split("\t")
                    if "LLVM-MCA-END kernel" in line:
                        return raw_inst
                    if "LLVM-MCA-BEGIN kernel" in line:
                        count = True
                        raw_inst = {}
                        continue
                    if not count or ASMParser.skip_asm_instruction(tok):
                        continue
                    # Fix for Intel Compiler ASM output
                    tok = ASMParser.tokenize_instruction(tok)
                    raw_asm = ASMParserATT.get_raw_asm_type(tok)
                    if raw_asm in raw_inst.keys():
                        raw_inst[raw_asm] += 1
                    else:
                        raw_inst[raw_asm] = 1
        except FileNotFoundError:
            perror(f"ASM file {asm_file} not found.")
        return raw_inst


class ASMParserIntel(ASMParser):
    @staticmethod
    def operand_to_suffix(op: str) -> str:
        op = op.strip().replace(" ", "")
        if (op.startswith("zmm")) or (op.startswith("ymm")) or (op.startswith("xmm")):
            return op[:-1].upper()
        elif op.startswith("0x") or re.match("^[0-9]+", op):
            return "IMM"
        elif re.match("^[-0-9]*\[", op) or "word" in op:
            return "MEM"
        elif op.startswith("."):
            return "LABEL"
        else:
            return "GPR"

    @staticmethod
    def get_raw_asm_type(ins: list[str]) -> str:
        """
        Get ASM variant, i.e. mnemonic[_operand_type], where operand_type can be a
        register, memory or a immediate value

        :param ins: List of strings, where the first token is the mnemonic
        :type ins: list
        :return: ASM mnemonic with its operands
        :rtype: str
        """

        op_name = ins[0]
        if len(ins) < 2:
            return op_name
        if len(ins) > 2:
            operands = [op[:-1] if op[-1] == "," else op for op in ins[1:]]
        else:
            operands = [
                op[:-1] if op[-1] == "," else op for op in ins[1].strip().split(" ")
            ]
        if len(operands) != 0:
            for op in operands:
                op_name += f"_{ASMParserIntel.operand_to_suffix(op.strip())}"
                op = op.strip()
        return op_name

    @staticmethod
    def parse_asm(asm_file: str) -> dict:
        """
        Parse the assembly file and get instructions within ROI

        :param asm_file: File name containing assembly instructions
        :type asm_file: str
        :return: Dictionary containing number of occurrences for an ASM instruction
        :rtype: dict
        """
        raw_inst = {}
        count = False
        try:
            with open(asm_file, "r") as f:
                # Get the previous contents
                lines = f.readlines()
                for line in lines:
                    if line[0] == "#" or line == "\n":
                        continue
                    tok = line.strip().split("#")
                    tok = tok[0].strip().split("\t")
                    if "LLVM-MCA-END kernel" in line:
                        return raw_inst
                    if "LLVM-MCA-BEGIN kernel" in line:
                        count = True
                        raw_inst = {}
                        continue
                    if not count or ASMParser.skip_asm_instruction(tok):
                        continue
                    # Fix for Intel Compiler ASM output
                    tok = ASMParser.tokenize_instruction(tok)
                    raw_asm = ASMParserIntel.get_raw_asm_type(tok)
                    if raw_asm in raw_inst.keys():
                        raw_inst[raw_asm] += 1
                    else:
                        raw_inst[raw_asm] = 1
        except FileNotFoundError:
            perror(f"ASM file {asm_file} not found.")
        return raw_inst
