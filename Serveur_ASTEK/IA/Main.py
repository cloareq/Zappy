#!/usr/bin/env python
# -*- coding: utf-8 -*-#

import sys
from InitConnection import InitConnection
from Parsing import Parsing
from Error import MyException
from Algo import IA

##### Parsing #####
try:
    Team, Port, Host = Parsing()
    if Team == "" or Port == "":
        raise
except:
    print "Usage ./client -p Port -t Team_name -h Hostname"
    sys.exit()
print "PARSING OK"

#### InitConnection ####
try: 
    Socket = InitConnection(Host, Port, Team)
except MyException, Message:
    print Message
    sys.exit()
except:
    print "Can not connect to the server"
    sys.exit()
print "CONNECTION OK"

#### Algo IA ####
Player = IA(Socket, Port, Team)
Player.Inventaire()
Player.LevelOne()
Player.Run()
Player.__del__()
