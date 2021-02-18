import os
import sys
import time
import pickle
from report import Report
from asm_analyzer import ASMParser as asm
from timing import Timing


class Kernel:
    debug = False
    total_time = time.time()
    compilation_time = 0
    execution_time = 0

    @staticmethod
    def dprint(msg):
        if Kernel.debug:
            print(f"[MARTA DEBUG]: {msg}")

    @staticmethod
    def start_timer():
        return time.time()

    def accm_timer(self, timer_type, t0):
        if timer_type == "compilation":
            self.compilation_time += time.time() - t0
        else:
            self.execution_time += time.time() - t0

    def save_results(self, df, filename):
        """
        Save data as a pandas.DataFrame

        :param df:
        :type df: class:pandas.DataFrame
        :param common_flags: List of flags used for compilation
        :type common_flags: str
        :param exec_args: List of arguments to pass when executing benchmark
        :type exec_args: str
        :param nruns: Number of times to execute the kernel
        :type nruns: int
        :param nexec: Number of time to execute whole experiment
        :type nexec: int
        :param filename: Name of the output file
        :type filename: str
        """
        # storing results with metadata
        df = df.fillna(0.0)
        df.to_csv(filename, index=False)

        # saving all data to file
        self.total_time = time.time() - self.total_time
        report_filename = filename.replace(".csv", ".log")
        with open(report_filename, "w") as f:
            f.write(Report.generate_report(self))

    @staticmethod
    def compile_parse_asm(
        kname, kpath, comp, common_flags, kconfig, other_flags="", suffix_file="", debug=""
    ):
        """
        Compile benchmark according to a set of flags, suffixes and so

        :param common_flags: Flags which are common for all versions
        :type common_flags: str
        :param custom_flags: Flags which are target-dependent
        :type custom_flags: str
        :param suffix_file: Suffix
        :type suffix_file: str
        :param debug: Suffix for execution command in order to redirect output if any
        :type debug: str
        :return: Dictionary of ASM occurrences
        :rtype: dict
        """
        comp_str = (
            f"make -B -C {kpath} COMP={comp}"
            f" KERNEL_CONFIG='{kconfig}' "
            f" COMMON_FLAGS='{common_flags}' "
            f" SUFFIX_ASM='{suffix_file}' "
            f" {other_flags} "
            f" {debug}"
        )
        Kernel.dprint(comp_str)
        ret = os.system(comp_str)

        if ret != 0:
            print(f"Error {str(ret)} compiling in {kpath}, quitting...")
            return {}
        return asm.parse_asm(f"asm_codes/{kname}_{suffix_file}_{comp}.s")

    def define_papi_counters(self):
        """
        Define PAPI counters in a new file recognized by PolyBench/C
        """
        papi_counter_file = "kernels/utilities/papi_counters.list"
        with open(papi_counter_file, "w") as f:
            for ctr in self.papi_counters:
                f.write("\"" + str(ctr) + "\",\n")

    @staticmethod
    def compute_flops(flops, nruns, avg_time):
        """
        Evaluate FLOPS expression provided by user as string and return a floating
        point value

        :param flops: Expression provided by user, e.g. "X/42", where "X" is a parameter
        :type flops: str
        :param nruns: Number of times to execute the kernel
        :type nruns: int
        :param avg_time: Average time to execute the kernel
        :type avg_time: float
        :return: Dynamic number of FLOPS
        :rtype: float
        """
        try:
            flops_eval = eval(flops)
        except TypeError:
            flops_eval = flops
        except NameError:
            print("FLOPS formula is not valid; please review it!")
            sys.exit(1)

        if avg_time > 0:
            return (flops_eval * nruns) / avg_time
        else:
            return 0

    @staticmethod
    def get_dict_from_params(params):
        params = pickle.loads(params)
        return params

    @staticmethod
    def get_suffix_and_flags(kconfig, params):
        custom_flags = ""
        suffix_file = ""
        params = Kernel.get_dict_from_params(params)
        # Parsing parameters
        for pname in params.keys():
            try:
                param_val_parsed = int(params[pname])
            except ValueError:
                param_val_parsed = "\\\"" + params[pname] + "\\\""
            custom_flags += f" -D{pname}={param_val_parsed}"
            suffix_file += f"_{pname}{params[pname]}"
        suffix_file = suffix_file.split("/")[-1].replace(".c", "")
        # Parsing kconfig
        for kparam in kconfig.strip().replace("-", "").split(" "):
            suffix_file += f"_{kparam}"
        return suffix_file, custom_flags

    def compile(self, kconfig, params_str, compiler, debug,  quit_on_error=False):
        """[summary]

        Args:
            kconfig ([type]): [description]
            params ([type]): [description]
            compiler ([type]): [description]
            debug ([type]): [description]
            quit_on_error (bool, optional): [description]. Defaults to False.

        Returns:
            [type]: [description]
        """
        suffix_file, custom_flags = Kernel.get_suffix_and_flags(
            kconfig, params_str)

        # FIXME
        custom_flags += self.compiler_flags[compiler]
        local_common_flags = self.common_flags + custom_flags
        local_common_flags += f" -DNRUNS={self.nruns} "
        if self.cpu_affinity != -1:
            local_common_flags += f" -DMARTA_CPU_AFFINITY={self.cpu_affinity} "

        other_flags = ""
        if "MACVETH" in kconfig:
            kconfig = kconfig.replace("MACVETH", "")
            other_flags = " MACVETH=true "
            suffix_file += "_macveth"
            other_flags += " MVPATH=" + self.mvpath + " MACVETH_FLAGS='" + \
                self.macveth_flags + "'"

        asm_cols = Kernel.compile_parse_asm(
            self.basename,
            self.path_kernel,
            compiler,
            local_common_flags,
            kconfig,
            other_flags,
            suffix_file,
            debug,
        )
        if asm_cols == {} and quit_on_error:
            return None
        return []

    def run(self, kconfig, params, compiler):
        tmp_dict = {}
        avg_papi_counters = dict.fromkeys(self.papi_counters)
        avg_time = {}
        name_bin, _ = Kernel.get_suffix_and_flags(kconfig, params)
        name_bin = self.basename + "_" + name_bin
        # Average papi counters
        if len(self.papi_counters) > 0:
            self.define_papi_counters()
            avg_papi_counters, discarded_papi_values = Timing.measure_benchmark(
                name_bin, self.papi_counters, self.exec_args, compiler, self.nexec,
                self.threshold_outliers, self.mean_and_discard_outliers)
            if discarded_papi_values != -1:
                tmp_dict.update(avg_papi_counters)

        # Average time
        avg_time, discarded_time_values = Timing.measure_benchmark(
            name_bin, "time", self.exec_args, compiler, self.nexec,
            self.threshold_outliers, self.mean_and_discard_outliers)
        if discarded_time_values != -1:
            tmp_dict.update(avg_time)

        tmp_dict.update(Kernel.get_dict_from_params(params))
        tmp_dict.update(
            {
                "CFG": kconfig,
                "Compiler": compiler,
                "DiscardedTimeValues": discarded_time_values,
                "DiscardedPapiValues": discarded_papi_values,
            }
        )
        if self.mean_and_discard_outliers:
            tmp_dict.update({"FLOPSs": Kernel.compute_flops(
                self.flops, self.nruns, avg_time["time"])})
            return tmp_dict
        list_rows = []
        for execution in range(self.nexec):
            new_dict = tmp_dict.copy()
            new_dict.update({"FLOPSs": Kernel.compute_flops(
                self.flops, self.nruns, avg_time[execution])})
            new_dict.update({"time": avg_time[execution], "nexec": execution})
            new_dict.update(
                dict(zip(self.papi_counters, avg_papi_counters[execution])))
            list_rows += [new_dict]
        return list_rows

    def __init__(self, cfg):
        """[summary]

        Args:
            cfg ([type]): [description]
        """
        # General configuration
        self.kernel = cfg["kernel"]["name"]
        self.descr = cfg["kernel"]["description"]
        self.path_kernel = cfg["kernel"]["path"]
        self.show_progress_bars = cfg["kernel"]["show_progress_bars"]
        Kernel.debug = cfg["kernel"]["debug"]

        # compilation:
        config_comp = cfg["kernel"]["compilation"]
        # configuration:
        config_cfg = cfg["kernel"]["configuration"]
        # execution:
        config_exec = cfg["kernel"]["execution"]

        # Compilation configuration
        self.compilation_enabled = config_comp["enabled"]
        try:
            self.processes = int(config_comp["processes"])
            if self.processes < 1:
                raise ValueError
            if self.processes > 16:
                print(
                    "[WARNING] Careful with high degree of processes for compilation")
        except ValueError:
            print("[ERROR] processes must be an integer greater or equal to one")
            sys.exit(1)
        except KeyError:
            self.processes = 1
        self.compilers_list = list(config_comp["compiler_flags"].keys())
        self.common_flags = config_comp["common_flags"]
        self.compiler_flags = config_comp["compiler_flags"]
        self.comp_debug = config_comp["debug"]

        # Configuration
        self.kernel_cfg = config_cfg["kernel_cfg"]
        self.feat = config_cfg["features"]
        self.flops = config_cfg["flops"]
        try:
            self.mvpath = config_cfg["macveth_path_build"]
        except KeyError:
            self.mvpath = ""
        try:
            self.macveth_flags = config_cfg["macveth_flags"]
        except KeyError:
            self.macveth_flags = ""

        # Execution arguments
        self.execution_enabled = config_exec["enabled"]
        self.threshold_outliers = config_exec["threshold_outliers"]
        self.mean_and_discard_outliers = config_exec["mean_and_discard_outliers"]
        self.nexec = config_exec["nexec"]
        self.nruns = int(config_exec["nruns"])
        self.cpu_affinity = int(config_exec["cpu_affinity"])
        self.papi_counters = config_exec["papi_counters"]
        self.exec_args = config_exec["prefix"]
        self.basename = self.kernel
