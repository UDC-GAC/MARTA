import sys
import re
import copy


class Operation:
    """Operation: 
        { 
            OperationId, 
            (TypeOperand1, IdOperand1),
            (TypeOperand2, IdOperand2),
            Operand
        }
            OperationId: same as OperandId: a unique key.
            TypeOperandX: 1 if a memory operand, 2 if the result of a prior
                    computation
            IdOperandX: the corresponding id (in either the operands list or the
                    operators list) of the operand operation: + or *
    """

    id = 0
    d_id = {}
    d_prior_comp = {}

    @staticmethod
    def get_operation(op0, op1, type_op):
        return Operation(op0, op1, type_op)

    @staticmethod
    def get_type_and_id_operand(operand):
        type_operand = 1  # memory
        id_operand = -1
        if type(operand) == Operation:
            # Concatenation of operations
            type_operand = 2
            id_operand = operand.id
        else:
            # Previous save to memory or memory operand
            if operand in Operation.d_prior_comp.keys():
                type_operand = 2
                id_operand = Operation.d_prior_comp[operand].id
            else:
                id_operand = Operand.d_id[operand].id
        return type_operand, id_operand

    def __init__(self, op0, op1, type_op):
        self.id = Operation.id
        Operation.id += 1
        self.op0 = Operation.get_type_and_id_operand(op0)
        self.op1 = Operation.get_type_and_id_operand(op1)
        self.type_op = type_op
        if type_op == "+":
            Operation.d_prior_comp[op0] = self

    def __str__(self):
        return f"({self.id}, ({self.op0}), ({self.op1}), {self.type_op})"


class Operand:
    """Operand
    { 
        OperandId, 
        VirtualMemoryAddress, 
        VirtualCacheLineId,
        PositionInVirtualCacheLine
    }
        OperandId: from 1 to nb-operands (unique key, max(operandId) == nb
                    distinct operands to the program)
        VirtualMemoryAddress: &(operandX) literally, above I simplified to the
            equivalent &(y[0]) == 0, &(A[0]) == 15000 to compute the values in the
            example.
        VirtualCacheLineId: Virtual memory address / cachelinesize (it's
            integer division here, clsize = 64B is good) 
        PositionInVirtualCacheLine: (Virtual memory address % cachelinesize) /
            sizeof(float) (note I use floats in the example above).
    """

    id = 0
    d_id = {}
    base_addr = {
        "y": 0x0,
        "A": 0x4000000,
        "x": 0x8000000,
    }

    @staticmethod
    def get_operand(raw_op: str):
        if not raw_op in Operand.d_id.keys():
            Operand.d_id[raw_op] = Operand(raw_op)
            Operand.id += 1
        return Operand.d_id[raw_op]

    def __init__(self, raw_op: str):
        self.raw_op = raw_op
        self.id = Operand.id
        self.base_array = raw_op[0]
        pos = int(re.search("\[(.+)\]", raw_op).group(1))
        self.vaddr = Operand.base_addr[self.base_array] + pos * 4
        self.vcacheline = int(self.vaddr / 64)
        self.pos_vcacheline = int((self.vaddr % 64) / 4)

    def __str__(self):
        return f"{self.raw_op}\n\t[{self.id}; {self.base_array}; {self.vaddr}; {self.vcacheline}; {self.pos_vcacheline}]"


class Loop:
    def __init__(self, raw_str):
        #                      1         2        3          4            5
        g = re.search(
            "for \(([ij]) = ([0-9]+); ([ij]) <= ([0-9]+); \+\+([ij])", raw_str
        )
        if not g:
            print("Loop can not be parsed")
            sys.exit(1)
        self.dim = g.group(1)
        if g.group(1) != g.group(3) or g.group(1) != g.group(5):
            print("Wrong loop bounds")
            sys.exit(1)
        self.init_val = int(g.group(2))
        self.upper_bound = int(g.group(4))
        self.step = 1

    def __str__(self):
        return f"{self.dim}: [{self.init_val}, {self.upper_bound}, {self.step}]"


class Program:
    @staticmethod
    def unroll_aux(loops: list, replace: dict, sentence: str) -> list:
        if type(loops) == Loop or len(loops) > 0:
            if type(loops) == Loop:
                l = loops
                loops = []
            else:
                l = loops.pop(0)
            new_sentences = []
            for i in range(l.init_val, l.upper_bound + 1, l.step):
                replace.update({l.dim: i})
                new_sentences.extend(Program.unroll_aux(loops, replace, sentence))
            return new_sentences

        for key in replace.keys():
            sentence = sentence.replace(key, str(replace[key]))
        operands = re.findall("([Ayx]\[[0-9 \+*\(\)-]+\])", sentence)
        ops = []
        for op in operands:
            ops.append(
                re.sub(
                    "\[(.+)\]",
                    "[" + str(eval(re.search("\[(.+)\]", op).group(1))) + "]",
                    op,
                )
            )
        return [ops[0] + " = " + ops[0] + " + " + ops[1] + " * " + ops[2]]

    @staticmethod
    def unroll(loops: list, sentence: str) -> tuple:
        l = loops.pop(0)
        new_sentences = []
        for i in range(l.init_val, l.upper_bound + 1, l.step):
            new_sentences.extend(Program.unroll_aux(loops.copy(), {l.dim: i}, sentence))
        print("\nCode unrolled:")
        for s in new_sentences:
            print(s)
        return new_sentences

    @staticmethod
    def get_subprograms(lines: list) -> list:
        # find loops, get structure
        programs = []
        loops = []
        print("Input programs:")
        for line in lines:
            print(line, end="")
            if re.match("[ \t]*for", line):
                loops.append(Loop(line))
            elif line == "\n":
                return programs
            else:
                programs.append(Program(loops, line))
                loops = []
        return programs

    def get_operands(self):
        operands = []
        for s in self.unrolled_sentences:
            ops = re.findall("([Ayx]\[[0-9 \+*\(\)-]+\])", s)[1:]
            for op in ops:
                operands.extend([Operand.get_operand(op)])
        return operands

    def get_operations(self):
        operations = []
        for s in self.unrolled_sentences:
            ops = re.findall("([Ayx]\[[0-9 \+*\(\)-]+\])", s)[1:]
            mul = Operation.get_operation(ops[1], ops[2], "*")
            operations.extend([mul])
            operations.extend([Operation.get_operation(ops[0], mul, "+")])

        return operations

    @staticmethod
    def fuse_programs(programs: list):
        if type(programs) == Program:
            return programs
        fused = copy.deepcopy(programs[0])
        for pi in programs[1:]:
            fused.loops.extend(pi.loops)
            fused.unrolled_sentences.extend(pi.unrolled_sentences)
            fused.operands.extend(pi.operands)
            fused.operations.extend(pi.operations)
        return fused

    def __init__(self, loops: list, sentence: str):
        self.loops = loops
        self.sentence = sentence
        self.unrolled_sentences = Program.unroll(loops, sentence)
        self.operands = self.get_operands()
        # for op in self.operands:
        #     print(op)
        self.operations = self.get_operations()
        # for op in self.operations:
        #     print(op)


class CostModel:
    @staticmethod
    def operations_cost(program) -> int:
        # FIXME: for codelets every 2 ops = 1 FMADD, maximum vector size 8
        # floats
        from math import ceil

        n_operations = 1
        if type(program.operations) != Operation:
            n_operations = len(program.operations) / 2
        return ceil(n_operations / 8)

    @staticmethod
    def packing_cost(program, var: str) -> int:
        # Check table...
        import numpy as np

        cache_lines_used = np.array([])
        pos_vcacheline = np.array([])
        ops = []
        for op in program.operands:
            if op.base_array == var:
                ops.append(op)
                cache_lines_used = np.append(cache_lines_used, op.vcacheline)
                pos_vcacheline = np.append(pos_vcacheline, op.pos_vcacheline)
        n_cache_lines = np.unique(cache_lines_used).size
        vlen = 8 if len(ops) > 4 else 4
        contiguous = True
        for i in range(1, len(ops)):
            contiguous = contiguous & (
                ops[i - 1].pos_vcacheline + 1 == ops[i].pos_vcacheline
            )
        # In some cases, we do not pack y, we just add it at the end
        if var == "y":
            if np.unique(pos_vcacheline).size < len(ops):
                return 0
        query = {
            "CL": n_cache_lines,
            "V_LEN": vlen,
            "X_N": len(ops),
            "Cont": contiguous,
        }
        return CostModel.query("CPU_CLK_THREAD_UNHALTED:THREAD_P", query)

    @staticmethod
    def query(output, q) -> int:
        import numpy as np

        tmp = CostModel.data
        n_cl = f"({q['X_N']}, {q['CL']})"
        df_query = tmp[(tmp["N_CL"] == n_cl) & (tmp["V_LEN"] == q["V_LEN"])]
        found = df_query.size
        if not found:
            value = np.inf
        else:
            if q["Cont"]:
                value = round(df_query[output].min())
            else:
                value = round(df_query[output].max())
        return value

    @staticmethod
    def storing_cost(program, var: str) -> int:
        import numpy as np
        from math import log

        pos_vcacheline = np.array([])
        ops = []
        for op in program.operands:
            if op.base_array == var:
                ops.append(op)
                pos_vcacheline = np.append(pos_vcacheline, op.pos_vcacheline)

        experimental_bias_reduction = 1
        experimental_bias_masks = 1
        experimental_bias_scatter = 1

        # Are there any reductions?
        # In this case we could just apply:
        #   2 * log(n) (1x add + 1x mov/shuffle per iteration) + 1 (add)
        # where n is the number of elements to reduce. If there are two
        # reductions simultaneously it could just be: 2*log(n/2), since there
        # are half of steps
        n_reductions = np.unique(pos_vcacheline).size
        if n_reductions != len(ops) / 2:
            print(
                (
                    2 * log(len(ops) / n_reductions, 2)
                    + n_reductions
                    + experimental_bias_reduction
                )
            )
            return (
                2 * log(len(ops) / n_reductions, 2)
                + n_reductions
                + experimental_bias_reduction
            )

        # Are there any masks? This is more expensive than a typical mov
        if len(ops) != 4 and len(ops) != 8:
            return 8 + experimental_bias_masks  # mask cost

        # Is it a scatter? This requires N+N movs + adds, instead of 1
        # Empirically, this is very expensive: difference up to 8 cycles
        # comparing
        contiguous = [
            True if ops[i - 1].pos_vcacheline + 1 == ops[i].pos_vcacheline else False
            for i in range(1, len(ops))
        ]
        if not np.all(contiguous):
            return len(ops) * 2 + experimental_bias_scatter

        # Is it a simple store? Due to buffer store forwarding this could even
        # be zero for this cost model, lets say it is 0
        return 0

    @staticmethod
    def compute_cost_program(program: list) -> int:
        cost = 0
        # Cost of packing
        print(f"packing x = {CostModel.packing_cost(program, 'x')}")
        print(f"packing y = {CostModel.packing_cost(program, 'y')}")
        print(f"packing A = {CostModel.packing_cost(program, 'A')}")
        cost += CostModel.packing_cost(program, "x")
        cost += CostModel.packing_cost(program, "A")
        cost += CostModel.packing_cost(program, "y")

        # Cost of operations
        cost += CostModel.operations_cost(program)

        # Cost of storing
        cost += CostModel.storing_cost(program, "y")

        return cost

    @staticmethod
    def load_table():
        import pandas as pd

        df = pd.read_csv("info.csv")
        # Is any further cleaning or check needed?
        CostModel.data = df

    @staticmethod
    def compute_cost(program: list) -> tuple:
        c0 = 0
        c1 = 0

        # Load table into class
        CostModel.load_table()

        # Cost is basically: packing + FMA + store
        c0 = CostModel.compute_cost_program(Program.fuse_programs(program))
        if type(program) == Program:
            # only one program
            return (c0, c0)
        # If there is a list of programs, compute values individually
        for pi in program:
            c1 += CostModel.compute_cost_program(pi)

        return (c0, c1)


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Nothing to do here")
        sys.exit(1)

    with open(sys.argv[1]) as f:
        subprograms = Program.get_subprograms(f.readlines())
        c0, c1 = CostModel.compute_cost(subprograms)
        if len(subprograms) == 1:
            print(f"\n\tSingle program cost = {c0}")
        else:
            print(f"\n\tFused cost = {c0}\n\tIndividual program costs added = {c1}")
