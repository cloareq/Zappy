import os, sys
import socket
import random

class iaClass:
	def __init__(self):
		self.connexion = 0
		self.food = 10
		self.listBroadcast = []
		self.servReturn = False
		self.listVoir = []
		self.myBroadcast = ""
		self.lvl = 1
		self.id = 0
		self.listlvl2 = [1, "linemate"]
		self.listlvl3 = [2, "linemate", "deraumere", "sibur"]
		self.listlvl4 = [2, "linemate", "linemate", "sibur", "phiras", "phiras"]
		self.listlvl5 = [4, "linemate", "deraumere", "sibur", "sibur", "phiras"]
		self.listlvl6 = [4, "linemate", "deraumere", "deraumere", "sibur", "mendiane", "mendiane", "mendiane"]
		self.listlvl7 = [6, "linemate", "deraumere", "deraumere", "sibur", "sibur", "sibur", "phiras"]
		self.listlvl8 = [6, "linemate", "linemate", "deraumere", "deraumere", "sibur", "sibur", "mendiane", "mendiane", "phiras", "phiras", "thystame"]
		self.listNbPlayer = [1, 2, 2, 4, 4, 6, 6]
		self.dictionnaireLvl = {}
		self.listInventaire = []
		self.linemate = 0
		self.deraumere = 0
		self.sibur = 0
		self.mendiane = 0
		self.phiras = 0
		self.thystame = 0
		self.fork = 0
		self.id = 0

	def connect(self, serv, port, team):
		try:
			self.connexion = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
			self.connexion.connect((serv, int(port)))
		except:
			print("Connexion Error")
			sys.exit()
		team += "\n"
		self.connexion.send(team.encode())
		self.dictionnaireLvl[1] = self.listlvl2
		self.dictionnaireLvl[2] = self.listlvl3
		self.dictionnaireLvl[3] = self.listlvl4
		self.dictionnaireLvl[4] = self.listlvl5
		self.dictionnaireLvl[5] = self.listlvl6
		self.dictionnaireLvl[6] = self.listlvl7
		self.dictionnaireLvl[7] = self.listlvl8
		self.listInventaire.insert(0, "{nourriture 10")
		self.id = random.randint(1, 100000)

	def sendCmd(self, cmd):
		cmd += "\n"
		self.connexion.send(cmd.encode())
		self.servReturn = False
		b = False
		while b != True:
			msg = self.connexion.recv(4096).decode()
			tmplist = msg.split('\n')
			for tmp in tmplist:
				if tmp == "ok" or tmp == "ko":
					b = True
				elif tmp == "mort":
					print("LE JOUEUR EST MORT")
					sys.exit(0)
				else:
					if len(tmp) > 1:
						self.listBroadcast.insert(0, tmp)
		
	
	def voir(self):
		self.connexion.send(b"voir\n")
		b = False
		while b != True:
			msg = self.connexion.recv(4096).decode()
			tmplist = msg.split('\n')
			for tmp in tmplist:
				if tmp.find("{ ") != -1:
					self.listVoir = tmp.split(',')
					b = True
				elif tmp == "mort":
					print("LE JOUEUR EST MORT")
					sys.exit(0)
				else:
					if len(tmp) > 1:
						self.listBroadcast.insert(0, tmp)

	def inventaire(self):
		self.connexion.send(b"inventaire\n")
		b = False
		while b != True:
			msg = self.connexion.recv(4096).decode()
			tmplist = msg.split('\n')
			for tmp in tmplist:
				if tmp.find("{n") != -1:
					tmp = tmp.replace(", ", ",")
					self.listInventaire = tmp.split(',')
					self.linemate = int(self.listInventaire[1][8:])
					self.deraumere = int(self.listInventaire[2][10:])
					self.sibur = int(self.listInventaire[3][6:])
					self.mendiane = int(self.listInventaire[4][8:])
					self.phiras = int(self.listInventaire[5][7:])
					self.thystame = int(self.listInventaire[6][9:10])
					b = True
				elif tmp == "mort":
					print("LE JOUEUR EST MORT")
					sys.exit(0)
			else:
				if len(tmp) > 1:
					self.listBroadcast.insert(0, tmp)

	def incantation(self):
		self.connexion.send(b"incantation\n")
		b = False
		c = 0
		while b != True:
			msg = self.connexion.recv(4096).decode()
			tmplist = msg.split('\n')
			for tmp in tmplist:
				if tmp == "elevation en cours":
					b = True
					c = 1
				elif tmp == "ko":
					print("INCANTATION KO")
					return -1
				elif tmp == "mort":
					print("LE JOUEUR EST MORT")
					sys.exit(0)
				else:
					if len(tmp) > 1:
						self.listBroadcast.insert(0, tmp)
		b = False
		msg = ""
		while b != True and c == 1:
			msg = self.connexion.recv(4096).decode()
			tmplist = msg.split('\n')
			for tmp in tmplist:
				if tmp.find("niveau actuel") != -1:
					self.lvl += 1
					b = True
				elif tmp == "ko":
					print("INCANTATION KO")
					return -1
				elif tmp == "mort":
					print("LE JOUEUR EST MORT")
					sys.exit(0)
				else:
					if len(tmp) > 1:
						self.listBroadcast.insert(0, tmp)


	def pose(self, obj):
		pose = "pose " + obj + '\n'
		self.connexion.send(pose.encode())
		b = False
		while b != True:
			msg = self.connexion.recv(4096).decode()
			tmplist = msg.split('\n')
			for tmp in tmplist:
				if tmp.find("ok") != -1:
					b = True
				elif tmp == "mort":
					print("LE JOUEUR EST MORT")
					sys.exit(0)
				else:
					if len(tmp) > 1:
						self.listBroadcast.insert(0, tmp)

	def prend(self, obj):
		pose = "prend " + obj + '\n'
		self.connexion.send(pose.encode())
		b = False
		while b != True:
			msg = self.connexion.recv(4096).decode()
			tmplist = msg.split('\n')
			for tmp in tmplist:
				if tmp.find("ok") != -1 or tmp.find("ko") != -1:
					b = True
				elif tmp == "mort":
					print("LE JOUEUR EST MORT")
					sys.exit(0)
				else:
					if len(tmp) > 1:
						self.listBroadcast.insert(0, tmp)