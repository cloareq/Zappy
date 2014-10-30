import os, sys
import socket
from algo import *

class iaClass:
	def __init__(self):
		self.lvl = 1
		self.listVoir = []
		self.listInventaire = []
		self.listMsgRecv = []
		self.nbMsg = 0
		self.connexion = 0
		self.mode = ""
		self.food = 10
		self.connectNbr = 0
		self.listlvl2 = [1, "linemate"]
		self.listlvl3 = [2, "linemate", "deraumere", "sibur"]
		self.listlvl4 = [2, "linemate", "linemate", "sibur", "phiras", "phiras"]
		self.listlvl5 = [4, "linemate", "deraumere", "sibur", "sibur", "phiras"]
		self.listlvl6 = [4, "linemate", "deraumere", "deraumere", "sibur", "mendiane", "mendiane", "mendiane"]
		self.reached = 1
		self.listlvl7 = [6, "linemate", "deraumere", "deraumere", "sibur", "sibur", "sibur", "phiras"]
		self.listlvl8 = [6, "linemate", "linemate", "deraumere", "deraumere", "sibur", "sibur", "mendiane", "mendiane", "phiras", "phiras", "thystame"]
		self.dictionnaireLvl = {}
		self.listNbPlayers = [1, 2, 2, 4, 4, 6, 6]
		self.linemate = 0
		self.deraumere = 0
		self.sibur = 0
		self.mendiane = 0
		self.phiras = 0
		self.thystame = 0
		self.fork = 0

	def connect(self, serv, port):
		try:
			self.connexion = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
			self.connexion.connect((serv, int(port)))
		except:
			print("connexion error")
			sys.exit()

	def launchGame(self, team):
		game = True
		t = 0
		self.team = team + '\n'
		self.connexion.send(self.team.encode())
		self.listMsgRecv.append("")
		self.connectNbr = int(self.connexion.send(b"connect_nbr\n"))
		self.dictionnaireLvl[1] = self.listlvl2
		self.dictionnaireLvl[2] = self.listlvl3
		self.dictionnaireLvl[3] = self.listlvl4
		self.dictionnaireLvl[4] = self.listlvl5
		self.dictionnaireLvl[5] = self.listlvl6
		self.dictionnaireLvl[6] = self.listlvl7
		self.dictionnaireLvl[7] = self.listlvl8
		
	def avance(self):
		self.connexion.send(b"avance\n")
		msg_recu = ""
		while (msg_recu.find("ok") == -1):
			msg_recu = self.connexion.recv(1024).decode()

	def droite(self):
		self.connexion.send(b"droite\n")
		msg_recu = ""
		while (msg_recu.find("ok") == -1):
			msg_recu = self.connexion.recv(1024).decode()
			self.nbMsg += 1

	def gauche(self):
		self.connexion.send(b"gauche\n")
		msg_recu = ""
		while (msg_recu.find("ok") == -1):
			msg_recu = self.connexion.recv(1024).decode()
			self.nbMsg += 1

	def prend(self, objet):
		prend = "prend " + objet + '\n'
		self.connexion.send(prend.encode())
		msg_recu = ""
		while (msg_recu.find("ok") == -1 and msg_recu.find("ko") == -1):
			msg_recu = self.connexion.recv(1024).decode()		
			self.listMsgRecv.insert(0, msg_recu)
			self.nbMsg += 1
		if msg_recu == "ok\n":
			return 0
		return -1

	def pose(self, objet):
		pose = "pose " + objet + '\n'
		self.connexion.send(pose.encode())
		msg_recu = ""
		while (msg_recu.find("ok") == -1 and msg_recu.find("ko") == -1):
			msg_recu = self.connexion.recv(1024).decode()
			self.listMsgRecv.insert(0, msg_recu)
			self.nbMsg += 1

	def expulse(self):
		self.connexion.send(b"expulse\n")
		msg_recu = ""
		while (msg_recu.find("ok") == -1 and msg_recu.find("ko") == -1):
			msg_recu = self.connexion.recv(1024).decode()
			self.listMsgRecv.insert(0, msg_recu)
			self.nbMsg += 1


	def broadcast(self, msg):
		broadcast = "broadcast " + msg + '\n'
		self.connexion.send(broadcast.encode())
		msg_recu = ""
		while (msg_recu.find("ok") == -1):
			msg_recu = self.connexion.recv(1024).decode()
			self.listMsgRecv.insert(0, msg_recu)
			self.nbMsg += 1

	def incantation(self):
		self.connexion.send("incantation\n".encode())
		msg_recu = ""
		while (msg_recu.find("elevation en cours") == -1 and msg_recu.find("ko") == -1):
			msg_recu = self.connexion.recv(1024).decode()
			self.listMsgRecv.insert(0, msg_recu)
			self.nbMsg += 1
			if (msg_recu.find("elevation en cours") != -1):
				while (msg_recu.find("niveau actuel") == -1):
					msg_recu = self.connexion.recv(1024).decode()
					self.listMsgRecv.insert(0, msg_recu)
					self.nbMsg += 1
				self.lvl += 1
				return(self.lvl)
		return -1

	def expulse(self):
		self.connexion.send(b"expulse\n")
		msg_recu = ""
		while (msg_recu.find("ok") == -1):
			msg_recu = self.connexion.recv(1024).decode()
			self.listMsgRecv.insert(0, msg_recu)
			self.nbMsg += 1
	
	def voir(self):
		self.connexion.send(b"voir\n")
		msg_recu = "v"
		while (msg_recu.find("{") == -1):
			msg_recu = self.connexion.recv(1024).decode()
		self.listVoir = msg_recu.split(',')

	def inventaire(self):
		self.connexion.send(b"inventaire\n")
		msg_recu = "v"
		while msg_recu.find("{") == -1:
			msg_recu = self.connexion.recv(1024).decode()
			if (msg_recu.find("message") != -1):
				find = msg_recu.find("message")
				self.listMsgRecv.insert(0, msg_recu)
				# print("CATCH")
				# print("--> " + msg_recu)
				if msg_recu.find("stop") != -1 and msg_recu.find(str(self.lvl)) != -1:
					self.reached = 0
					
		self.listInventaire = msg_recu.split(',')
		self.linemate = int(self.listInventaire[1][8:])
		self.deraumere = int(self.listInventaire[2][10:])
		self.sibur = int(self.listInventaire[3][6:])
		self.mendiane = int(self.listInventaire[4][8:])
		self.phiras = int(self.listInventaire[5][7:])
		self.thystame = int(self.listInventaire[6][9:10])
		

	def fork(self):
		self.connexion.send(b"fork\n")
		msg_recu = ""
		while (msg_recu.find("ok") == -1):
			msg_recu = self.connexion.recv(1024).decode()
			self.listMsgRecv.insert(0, msg_recu)
			self.nbMsg += 1
		self.fork = 1
