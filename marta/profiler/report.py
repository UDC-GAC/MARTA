import os
import sys
import cpuinfo as cpu


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
        cpu_info += f"Architecture:\t\t{cpu.platform.architecture()[0]}\n"
        cpu_info += f"Memory:\t\t\t\t\n"
        cpu_info += f"Avail. Cores:\t\t{cpu.os.cpu_count()}\n"
        cpu_info += f"OS:\t\t\t\t\t"
        if cpu.platform.win32_ver()[0] != "":
            cpu_info += f"{cpu.platform.win32_ver()[0]}\n"
        elif cpu.platform.mac_ver()[0] != "":
            cpu_info += f"{cpu.platform.mac_ver()[0]}\n"
        else:
            cpu_info += f"{cpu.platform.uname()[3]}\n"

        return cpu_info

    @staticmethod
    def generate_report(params, verbose=True) -> str:
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
        content += f"# MARTA Configuration file report\n"
        content += f"#" * 80 + "\n"
        if verbose:
            content += f"# -- MACHINE INFO\n"
            content += Report.get_machine_info()
        content += f"# -- EXPERIMENT PARAMETERS\n"
        for p in params:
            if type(p) == dict:
                for k, v in p.items():
                    content += f"{str(k)}-> {str(v)}\n"
            else:
                content += f"{str(p)}\n"

        # TODO: get compilation flags and so
        content += f"\n# -- COMPILATION\n"
        with open("___tmp.stdout") as f:
            for l in f.readlines():
                content += l
        os.system("rm ___tmp.stdout")

        # TODO: generate errors
        content += f"\n# -- ERRORS\n"
        with open("___tmp.stderr") as f:
            for l in f.readlines():
                content += l
        os.system("rm ___tmp.stderr")
        # TODO: generate warnings
        # content += f"\n# -- WARNINGS\n"

        # TODO: generate issues
        # content += f"\n# -- ISSUES\n"

        return content
