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

from marta.utils.marta_utilities import pwarning, pinfo, perror


class Logger:
    warning_l = []
    error_l = []
    info_l = []
    msg = []

    @staticmethod
    def warning(msg: str):
        Logger.warning_l.append([msg])

    @staticmethod
    def error(msg: str):
        Logger.error_l.append([msg])

    @staticmethod
    def info(msg: str):
        Logger.info_l.append([msg])

    @staticmethod
    def print_msg():
        for msg in Logger.msg:
            if msg[0].lower() == "info":
                pinfo(msg[1])
            if msg[0].lower() in ["warning", "warn"]:
                pwarning(msg[1])
            if msg[0].lower() == "error":
                perror(msg[1])

    @staticmethod
    def write_to_file(file: str, msg: str = ""):
        with open(file, "w") as log:
            log.write(f"MARTA log: {msg}\n")
            log.write("errors:\n")
            for err in Logger.error_l:
                log.write(f"{err}\n")
            log.write("=" * 80 + "\n")
            log.write("warnings:\n")
            for warn in Logger.warning_l:
                log.write(f"{warn}\n")
            log.write("=" * 80 + "\n")
            log.write("info:\n")
            for inf in Logger.info_l:
                log.write(f"{inf}\n")

