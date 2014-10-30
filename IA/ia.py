#!/usr/bin/python3.4

import os, sys
import socket
from iaClass import *
from algo import *
	
def main():
	if len(sys.argv) is not 4:
		print("USAGE : ./ia.py [serv] [port] [team]")
	else:
		ia = iaClass()
		ia.connect(sys.argv[1], sys.argv[2])
		ia.launchGame(sys.argv[3])
		algo(ia)

if __name__ == '__main__':
	main()
