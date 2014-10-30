#!/usr/bin/python3.4

import os, sys
import socket
from iaClass import *

def findResources(ia, obj):
	ia.voir()
	i = 0;
	for fullCase in ia.listVoir:
		splitCase = fullCase.split(' ')
		for item in splitCase:
			if (item == obj):
				if (i == 0):
					ia.prend(obj)
					return 1
				if (i == 1):
					ia.sendCmd("avance")
					ia.sendCmd("gauche")
					ia.sendCmd("avance")
					ia.prend(obj)
					return 1
				if (i == 2):
					ia.sendCmd("avance")
					ia.prend(obj)
					return 1
				if (i == 3):
					ia.sendCmd("avance")
					ia.sendCmd("droite")
					ia.sendCmd("avance")
					ia.prend(obj)
					return 1
				if (i == 4):
					ia.sendCmd("avance")
					ia.sendCmd("avance")
					ia.sendCmd("gauche")
					ia.sendCmd("avance")
					ia.sendCmd("avance")
					ia.prend(obj)
					return 1
				if (i == 5):
					ia.sendCmd("avance")
					ia.sendCmd("avance")
					ia.sendCmd("gauche")
					ia.sendCmd("avance")
					ia.prend(obj)
					return 1
				if (i == 6):
					ia.sendCmd("avance")
					ia.sendCmd("avance")
					ia.prend(obj)
					return 1
				if (i == 7):
					ia.sendCmd("avance")
					ia.sendCmd("avance")
					ia.sendCmd("droite")
					ia.sendCmd("avance")
					ia.prend(obj)
					return 1
				if (i == 8):
					ia.sendCmd("avance")
					ia.sendCmd("avance")
					ia.sendCmd("droite")
					ia.sendCmd("avance")
					ia.sendCmd("avance")
					ia.prend(obj)
					return 1
		i = i + 1
	ia.sendCmd("avance")
	return -1

def checkFood(ia):
	ia.inventaire()
	ia.food = int(ia.listInventaire[0][12:len(ia.listInventaire[0])])
	if ia.food < 8:
		return -1
	return 0

def checkNbPlayer(ia):
	ia.voir()
	nbPlayer = 1
	for tmp in ia.listBroadcast:
		if tmp.find("here") != -1 and int(tmp[8]) == 0 and int(tmp[15]) == ia.lvl:
			nbPlayer += 1
	if nbPlayer == ia.listNbPlayer[ia.lvl - 1]:
		return 0
	return -1

def checkCalled(ia):
	checkReady(ia)
	ia.voir()
	if ia.onWay == True:
		for tmp in ia.listBroadcast:
			if "come" in tmp and int(tmp[15]) == ia.lvl and int(tmp[17:len(tmp)]) == ia.id:
				ia.myBroadcast = tmp
				return 0
			if "stop" in tmp and int(tmp[15]) == ia.lvl and int(tmp[17:len(tmp)]) == ia.id:
				ia.myBroadcast = ""
				ia.listBroadcast.clear()
				ia.onWay = False
				return -1
		ia.onWay = False
	else:
		return -1

def sayReady(ia):
	broadcast = "broadcast ready " + str(ia.lvl)
	ia.sendCmd(broadcast)

def checkReady(ia):
	ia.voir()
	if ia.onWay == False:
		for tmp in ia.listBroadcast:
			if "ready" in tmp:
				if int(tmp[16]) == ia.lvl:
					broadcast = "broadcast moi " + str(ia.id)
					ia.sendCmd(broadcast)
					ia.onWay = True
					return 0

def callOthers(ia):
	ia.voir()
	if checkCalled(ia) != 0:
		tabCall = []
		for tmp in ia.listBroadcast:
			if "moi" in tmp:
				if (len(tabCall)) < ia.listNbPlayer[ia.lvl - 1] - 1:
					tabCall.insert(0, int(tmp[14:len(tmp)]))
		i = 0
		if len(tabCall) > 0:
			while checkNbPlayer(ia) != 0:
				if i == len(tabCall):
					i = 0
				if checkFood(ia) == -1:
					return -1
				broadcast = "broadcast come " + str(ia.lvl) + "-" + str(tabCall[i])
				ia.sendCmd(broadcast)
				i += 1

	mess = "broadcast stop " + str(ia.lvl) + "-" + str(ia.id)
	ia.sendCmd(mess)

def waitNextLvl(ia):
	b = False
	msg = ""
	while b != True:
		if checkFood(ia) == -1:
			return -1
		msg = ia.connexion.recv(4096).decode()
		tmplist = msg.split('\n')
		for tmp in tmplist:
			if tmp.find("niveau actuel") != -1:
				ia.lvl += 1
				b = True
			elif tmp == "ko":
				return -1
			elif tmp == "mort":
				sys.exit(0)
			else:
				if len(tmp) > 1:
					ia.listBroadcast.insert(0, tmp)

def getCloser(ia):
	ia.voir()
	pos = int(ia.myBroadcast[8])
	if (pos == 0):
		mess = "broadcast here " + str(ia.lvl)
		ia.sendCmd(mess)
		ia.onWay = False
		waitNextLvl(ia)
		return 0
	if (2 <= pos <= 4):
		ia.sendCmd("gauche")
		ia.sendCmd("avance")
		if pos == 2:
			ia.sendCmd("droite")
			ia.sendCmd("avance")
		elif pos == 4:
			ia.sendCmd("gauche")
			ia.sendCmd("avance")
	elif (6 <= pos <= 8):
		ia.sendCmd("droite")
		ia.sendCmd("avance")
		if pos == 6:
			ia.sendCmd("droite")
			ia.sendCmd("avance")
		elif pos == 8:
			ia.sendCmd("gauche")
			ia.sendCmd("avance")
	else:
		if (pos == 1):
			ia.voir()
			ia.inventaire()
			ia.sendCmd("avance")
		else:
			ia.sendCmd("droite")
			ia.sendCmd("droite")
			ia.sendCmd("avance")
	ia.myBroadcast = ""
	ia.listBroadcast.clear()
	if checkCalled(ia) == 0:
		getCloser(ia)
	return 1

def checkStone(ia):
	ia.inventaire()
	linemate = 0
	deraumere = 0
	sibur = 0
	mendiane = 0
	phiras = 0
	thystame = 0
	i = 1
	while i != len(ia.dictionnaireLvl[ia.lvl]):
		if ia.dictionnaireLvl[ia.lvl][i] == "linemate":
			linemate += 1
		if ia.dictionnaireLvl[ia.lvl][i] == "deraumere":
			deraumere += 1
		if ia.dictionnaireLvl[ia.lvl][i] == "sibur":
			sibur += 1
		if ia.dictionnaireLvl[ia.lvl][i] == "mendiane":
			mendiane += 1
		if ia.dictionnaireLvl[ia.lvl][i] == "phiras":
			phiras += 1
		if ia.dictionnaireLvl[ia.lvl][i] == "thystame":
			thystame += 1
		i += 1
	if ia.linemate >= linemate and ia.deraumere >= deraumere and ia.sibur >= sibur and ia.mendiane >= mendiane and ia.phiras >= phiras and ia.thystame >= thystame:
		return 0
	return -1


def getStone(ia):
	i = 1
	while i != len(ia.dictionnaireLvl[ia.lvl]):
		findResources(ia, ia.dictionnaireLvl[ia.lvl][i])
		if checkCalled(ia) == 0:
			getCloser(ia)
			return -1
		i += 1

def poseStone(ia):
	i = 1
	while i != len(ia.dictionnaireLvl[ia.lvl]):
		ia.pose(ia.dictionnaireLvl[ia.lvl][i])
		i += 1

def takeAll(ia):
	ia.prend("nourriture")
	ia.prend("linemate")
	ia.prend("deraumere")
	ia.prend("sibur")
	ia.prend("mendiane")
	ia.prend("phiras")
	ia.prend("thystame")

def emptyCase(ia):
	ia.voir()
	while 42:
		ia.voir()
		if ia.listVoir[0].find("nourriture") == -1 and ia.listVoir[0].find("linemate") == -1 and ia.listVoir[0].find("deraumere") == -1 and ia.listVoir[0].find("sibur") == -1 and ia.listVoir[0].find("mendiane") and ia.listVoir[0].find("phiras") == -1 and ia.listVoir[0].find("thystame") == -1:
			return 0
		takeAll(ia)

def algo(ia, ip, port, team):
	while ia.lvl != 8:
		if checkFood(ia) == -1:
			while ia.food < 20:
				checkFood(ia)
				findResources(ia, "nourriture")
		if checkCalled(ia) == 0:
			getCloser(ia)
		else:
			if checkStone(ia) == 0:
				emptyCase(ia)
				poseStone(ia)
				if checkNbPlayer(ia) == 0:
					ia.incantation()
				else:
					if checkCalled(ia) != 0:
						sayReady(ia)
						callOthers(ia)
						if checkNbPlayer(ia) == 0:
							ia.incantation()
					else:
						getCloser(ia)
			else:
				getStone(ia)

def main():
		ia = iaClass()
		i = 1
		host = "null"
		team = "null"
		port = "null"
		while i < len(sys.argv):
			if sys.argv[i] == "-h":
				i += 1
				host = sys.argv[i]
			elif sys.argv[i] == "-p":
				i += 1
				port = sys.argv[i]
			elif sys.argv[i] == "-n":
				i += 1
				team = sys.argv[i]
			i += 1
		if team == "null" or port == "null":
			print("USAGE : ./ia -h host -p port -n team")
			sys.exit()
		if host == "null":
			host = "localhost"
		ia.connect(host, port, team)
		algo(ia, host, port, team)

if __name__ == '__main__':
	main()