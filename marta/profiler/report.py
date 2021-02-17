import os
import cpuinfo as cpu
import datetime


class Report:
    cinfo = None
    errors = None

    @staticmethod
    def get_compilation_options():
        return ""

    @staticmethod
    def get_errors():
        return Report.errors

    @staticmethod
    def get_machine_info():
        """
        Get information regarding processor and SO of host machine
        """

        if Report.cinfo == None:
            Report.cinfo = cpu.get_cpu_info()

        cpu_info = f"CPU:\t\t\t{Report.cinfo['brand_raw']}\n"
        cpu_info += f"Architecture:\t{Report.cinfo['arch_string_raw']}\n"
        cpu_info += f"Avail. Cores:\t{cpu.os.cpu_count()}\n"
        cpu_info += f"Host OS:\t\t"
        if cpu.platform.win32_ver()[0] != "":
            cpu_info += f"{cpu.platform.win32_ver()[0]}"
        elif cpu.platform.mac_ver()[0] != "":
            cpu_info += f"{cpu.platform.mac_ver()[0]}"
        else:
            cpu_info += f"Kernel: {cpu.platform.uname()[2]}"

        return cpu_info + "\n"

    @staticmethod
    def generate_report(kernel, verbose=True) -> str:
        """
        Generate custom header for CSV file

        :param params: List of parameters to print in the file
        :type params: list
        :param verbose: If `True`, then outputs machine information
        :type verbose: bool
        :return: A string containing all data as a comment (all lines start with #)
        :rtype: str
        """
        content = f"#" * 80 + "\n"
        content += f"#\t\t\tMARTA file report: {kernel.basename}\n"
        content += f"#" * 80 + "\n"
        if verbose:
            content += f"\n# -- MACHINE INFO\n"
            content += Report.get_machine_info()

        content += f"\n# -- TIME ELAPSED : { str(datetime.timedelta(seconds=kernel.total_time))}\n"
        content += f"\t- Total Compilation time: {str(datetime.timedelta(seconds=kernel.compilation_time))}\n"
        content += f"\t- Total Execution time: {str(datetime.timedelta(seconds=kernel.execution_time))}\n"
        content += f"\n# -- EXPERIMENT PARAMETERS\n"
        content += f"- Kernel name: {kernel.basename}\n"
        content += f"- Description: {kernel.descr}\n"
        content += f"- Compilers used:\n"
        for compiler in kernel.compiler_flags:
            content += f"\t{compiler} -> {kernel.compiler_flags[compiler]}\n"
        content += f"- FLOPS: {kernel.flops}\n"
        content += f"- Loop iterations: {kernel.nruns}\n"
        content += f"- Number of repetitions: {kernel.nexec}\n"
        content += f"- CPU affinity (if any): {kernel.cpu_affinity}\n"
        content += f"- PAPI counters used (if any):\n"
        for l in kernel.papi_counters:
            content += f"\t{l}\n"

        # Get compilation flags and so
        content += f"\n# -- COMPILATION\n"
        try:
            with open("___tmp.stdout") as f:
                for l in f.readlines():
                    content += l
            os.system("rm ___tmp.stdout")
        except FileNotFoundError:
            content += "stdout was redirected manually.\n"

        # Generate errors
        content += f"\n# -- ERRORS\n"
        try:
            with open("___tmp.stderr") as f:
                for l in f.readlines():
                    content += l
            os.system("rm ___tmp.stderr")
        except FileNotFoundError:
            content += "stderr was redirected manually.\n"

        return content
