#!/usr/bin/python3.4

import os, sys
import socket

def main():
	connexion = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	connexion.connect(("localhost", 1212))
	connexion.send(b"toto\n")
	while 42:
		connexion.send(b"broadcast stop 1\n")

if __name__ == '__main__':
	main()