#!/usr/bin/env python
# -*- coding: utf-8 -*-
# File              : utilities.py
# Author            : Marcos Horro <marcos.horro@udc.gal>
# Date              : Lun 04 Nov 2019 21:45:52 MST
# Last Modified Date: Xov 07 Nov 2019 13:56:06 MST
# Last Modified By  : Marcos Horro <marcos.horro@udc.gal>
import argparse
import os

DEBUG = True


class StoreDictKeyPair(argparse.Action):
    '''
    StoreDictKeyPair class for parsing
    '''

    def __init__(self, option_strings, dest, nargs=None, **kwargs):
        self._nargs = nargs
        super(StoreDictKeyPair, self).__init__(
            option_strings, dest, nargs=nargs, **kwargs)

    def __call__(self, parser, namespace, values, option_string=None):
        my_dict = {}
        for kv in values:
            k, v = kv.split("=")
            my_dict[k] = int(v)
        setattr(namespace, self.dest, my_dict)


class colors:
    '''
    Colors class: reset all colors with colors.reset; two
    sub classes fg for foreground
    and bg for background; use as colors.subclass.colorname.
    i.e. colors.fg.red or colors.bg.greenalso, the generic bold, disable,
    underline, reverse, strike through,
    and invisible work with the main class i.e. colors.bold
    '''
    reset = '\033[0m'
    bold = '\033[01m'
    disable = '\033[02m'
    underline = '\033[04m'
    reverse = '\033[07m'
    strikethrough = '\033[09m'
    invisible = '\033[08m'

    class fg:
        black = '\033[30m'
        red = '\033[31m'
        green = '\033[32m'
        orange = '\033[33m'
        blue = '\033[34m'
        purple = '\033[35m'
        cyan = '\033[36m'
        lightgrey = '\033[37m'
        darkgrey = '\033[90m'
        lightred = '\033[91m'
        lightgreen = '\033[92m'
        yellow = '\033[93m'
        lightblue = '\033[94m'
        pink = '\033[95m'
        lightcyan = '\033[96m'

    class bg:
        black = '\033[40m'
        red = '\033[41m'
        green = '\033[42m'
        orange = '\033[43m'
        blue = '\033[44m'
        purple = '\033[45m'
        cyan = '\033[46m'
        lightgrey = '\033[47m'


# print with color

def prRed(msg): print((colors.fg.red + '{}' + colors.reset) .format(msg))


def prGreen(msg): print((colors.fg.green + '{}' + colors.reset) .format(msg))


def prYellow(msg): print((colors.fg.yellow + '{}' + colors.reset) .format(msg))


def prDebug(msg):
    if DEBUG:
        print((colors.fg.purple + '[DEBUG] {}' + colors.reset) .format(msg))


def grep_file2file(string, infile, outfile):
    os.system("grep -m 1 -n \"%s\" %s /dev/null >> %s" %
              (string, infile, outfile))
    with open(outfile, 'r') as f:
        for l in f:
            if string in l:
                return l.replace("%", "").split()[-1]
    return None
