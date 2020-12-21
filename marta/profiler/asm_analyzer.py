import os


class ASMParser:
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
        operands = ins[1].strip().split(",")
        if len(operands) != 0:
            op_name += "_"
            for op in operands:
                op = op.strip()
                if ("%zmm" in op) or ("%ymm" in op) or ("%xmm" in op):
                    op_name += "r"
                else:
                    op_name += "m"
        return op_name

    @staticmethod
    def skip_asm_instruction(ins):
        """
        Auxiliary function for skipping certain ASM operations

        :param ins: Instructions to analyze
        :type ins: str
        :return: `True` if assembly instruction must be skipped
        :rtype: bool
        """

        if ins[0][0] == ".":
            return True
        for i in ins:
            if i == "ret" or i == "endbr64":
                return True
        return False

    @staticmethod
    def parse_asm(asm_file):
        """
        Parse the

        :param asm_file: File name containing assembly instructions
        :type asm_file: str
        :return: Dictionary containing number of occurrences for an ASM instruction
        :rtype: dict
        """

        raw_inst = {}
        count = False
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
                raw_asm = ASMParser.get_raw_asm_type(tok)
                if raw_asm in raw_inst.keys():
                    raw_inst[raw_asm] += 1
                else:
                    raw_inst[raw_asm] = 1

        return raw_inst
