#!/usr/bin/env python
# -*- coding: utf-8 -*-#

import sys
import socket
from Error import MyException

def InitConnection(Host, Port, Team):
    print "Connect to {} on port {} with team {}".format(Host, Port, Team)
    MSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    MSocket.connect((Host, int(Port)))
    if MSocket.recv(1024).decode() != "BIENVENUE\n":
        raise MyException("Server did not sent\"BIENVENUE\".")
    MSocket.send(Team + "\n".encode())
    FreeSlot = MSocket.recv(1024).decode()
    if int(FreeSlot) < 0:
        raise MyException("No available slot on server.")
    SizeTab = MSocket.recv(1024).decode().split(" ")
    x = int(SizeTab[0])
    y = int(SizeTab[1])
    print "connection OK x = {}, y = {} free space = {}".format(x, y, FreeSlot)
    print "------------------------- START GAME --------------------------------"
    return MSocket
