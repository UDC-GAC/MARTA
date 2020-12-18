import os
import sys
import cpuinfo as cpu


def get_machine_info():
    """
    Get information regarding processor and SO of host machine
    """

    cinfo = cpu.get_cpu_info()

    cpu_info = f"CPU\t{cinfo['brand_raw']}\n"
    cpu_info += f"Arch\t{cpu.platform.architecture()[0]}\n"
    cpu_info += f"Avail Cores\t{cpu.os.cpu_count()}\n"
    cpu_info += f"OS\t"
    if cpu.platform.win32_ver()[0] != "":
        cpu_info += f"{cpu.platform.win32_ver()[0]}\n"
    elif cpu.platform.mac_ver()[0] != "":
        cpu_info += f"{cpu.platform.mac_ver()[0]}\n"
    else:
        cpu_info += f"{cpu.platform.uname()[3]}\n"

    return cpu_info


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
    content = "MARTA Configuration file report"
    if verbose:
        content = f"-- machine info\n"
        content += get_machine_info()
        content += f"-- machine info\n\n"
    content += f"-- parameters info\n"
    for p in params:
        if type(p) == dict:
            for k, v in p.items():
                content += f"\t{str(k)}-> {str(v)}\n"
        else:
            content += f"\t{str(p)}\n"
    content += f"-- parameters info\n"

    # TODO: generate errors
    # TODO: generate warnings
    # TODO: generate issues

    return content