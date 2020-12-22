import os


class Project:
    """
    Project class, for generating new projects, template-based.
    """

    name = "new_project"
    lang = "c"
    build_system = "Unix Makefiles"
    path = "./"

    def __init__(self, name, lang, build_system):
        self.name = name
        self.lang = lang
        self.build_system = build_system

    def create_new_project(self):
        return

    @staticmethod
    def create_blank_project():
        return
