import sys
import re
from abc import ABC, abstractmethod


class ASMParserFactory:
    @staticmethod
    def parse_asm(t, f):
        if t == "att":
            return ASMParserATT.parse_asm(f)
        elif t == "intel":
            return ASMParserIntel.parse_asm(f)
        else:
            print("Wrong mnemonics, quitting")
            sys.exit(1)


class ASMParser(ABC):
    @staticmethod
    @abstractmethod
    def parse_asm(asm_file):
        pass

    @staticmethod
    def skip_asm_instruction(ins):
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


class ASMParserATT(ASMParser):
    @staticmethod
    def operand_to_suffix(op):
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
    def get_raw_asm_type(ins):
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
    def parse_asm(asm_file):
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
                for l in lines:
                    if l[0] == "#" or l == "\n":
                        continue
                    tok = l.strip().split("#")
                    tok = tok[0].strip().split("\t")
                    if tok[0] == ".cfi_endproc":
                        return raw_inst
                    if tok[0] == ".cfi_startproc":
                        count = True
                        continue
                    if not count or ASMParser.skip_asm_instruction(tok):
                        continue
                    # Fix for Intel Compiler ASM output
                    if len(tok) == 1:
                        tok = tok[0].split(" ")
                        tok = [t for t in tok if t != "" and t[0] != "#"]
                    raw_asm = ASMParserATT.get_raw_asm_type(tok)
                    if raw_asm in raw_inst.keys():
                        raw_inst[raw_asm] += 1
                    else:
                        raw_inst[raw_asm] = 1
        except FileNotFoundError:
            print(f"[ERROR] ASM file {asm_file} not found.")
            print(f"[ERROR] Quitting...")
            sys.exit(1)
        return raw_inst


class ASMParserIntel(ASMParser):
    @staticmethod
    def operand_to_suffix(op):
        op = op.strip().replace(" ", "")
        if (op.startswith("zmm")) or (op.startswith("ymm")) or (op.startswith("xmm")):
            return op[1:4].upper()
        elif op.startswith("$"):
            return "IMM"
        elif re.match("^[-0-9]*\(", op):
            return "MEM"
        elif op.startswith("."):
            return "LABEL"
        else:
            return "GP"

    @staticmethod
    def get_raw_asm_type(ins):
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
    def parse_asm(asm_file):
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
                for l in lines:
                    if l[0] == "#" or l == "\n":
                        continue
                    tok = l.strip().split("#")
                    tok = tok[0].strip().split("\t")
                    if tok[0] == ".cfi_endproc":
                        return raw_inst
                    if tok[0] == ".cfi_startproc":
                        count = True
                        continue
                    if not count or ASMParser.skip_asm_instruction(tok):
                        continue
                    # Fix for Intel Compiler ASM output
                    if len(tok) == 1:
                        tok = tok[0].split(" ")
                        tok = [t for t in tok if t != "" and t[0] != "#"]
                    raw_asm = ASMParserIntel.get_raw_asm_type(tok)
                    if raw_asm in raw_inst.keys():
                        raw_inst[raw_asm] += 1
                    else:
                        raw_inst[raw_asm] = 1
        except FileNotFoundError:
            print(f"[ERROR] ASM file {asm_file} not found.")
            print(f"[ERROR] Quitting...")
            sys.exit(1)
        return raw_inst
