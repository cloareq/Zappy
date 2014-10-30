#!/usr/bin/python
# -*- coding: utf-8 -*-#

import sys

def Parsing():
    i = 1
    Team = ""
    Port = ""
    Host = "localhost"
    while (i < len(sys.argv)):
        if (sys.argv[i] == "-p"):
            i = i + 1
            Port = sys.argv[i]
        elif (sys.argv[i] == "-h"):
            i = i + 1
            Host = sys.argv[i]
        elif (sys.argv[i] == "-t"):
            i = i + 1
            Team = sys.argv[i]
        else:
            i = i + 1
    return Team, Port, Host
