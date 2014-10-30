#!/usr/bin/python
# -*- coding: utf-8 -*-#

import sys
import socket
import time
import os

#NOTE
#call destructor when received mort\n

class IA():

    def __init__(self, S, P, T):
        self.c =  ['\033[95m', '\033[94m', '\033[92m', '\033[93m', '\033[91m', '\033[0m', '\033[95m', '\033[94m']
        self.Socket = S
        self.Team = T
        self.Port = P
        self.Level = 0
        self.Id = str(time.time())
        print 'id = ', self.Id
        self.Historical = ['']
        self.Player = [0, 1, 1, 3, 3, 5, 5] 
        self.Need = {'linemate': 0, 'deraumere': 0, 'sibur': 0, 'mendiane': 0, 'phiras': 0, 'thystame': 0}
        self.L = [['linemate'],
                  ['linemate', 'deraumere', 'sibur'],
                  ['linemate', 'linemate', 'sibur', 'phiras', 'phiras'],
                  ['linemate', 'deraumere', 'sibur', 'sibur', 'phiras'],
                  ['linemate', 'deraumere', 'deraumere', 'sibur', 'mendiane', 'mendiane', 'mendiane'],
                  ['linemate', 'deraumere', 'deraumere', 'sibur', 'sibur', 'sibur', 'phiras'],
                  ['linemate', 'linemate', 'deraumere', 'deraumere', 'sibur', 'sibur', 'mendiane', 'mendiane', 'phiras', 'phiras','thystame']]

    def __del__(self):
        print 'Close connection.'
        self.Socket.close()
        sys.exit()

    def ClearHistorical(self, Id, TmpLevel):
        print self.c[0], 'Supprime les truc du level ', TmpLevel, ' envoyer par ', Id, self.c[4]
        tmp = len(self.Historical)
        for Elem in self.Historical:
            if '-'+ str(self.Level - 1) + '-' in Elem:
                self.Historical.remove(Elem)
            elif ('wait-' + str(TmpLevel) in Elem and Id in Elem) \
                    or ('ready-' + str(TmpLevel) in Elem and Id in Elem) \
                    or ('ignore-' + str(TmpLevel) in Elem and Id in Elem) \
                    or ('arrived-' + str(TmpLevel) in Elem and Id in Elem) \
                    or ('me-' + str(TmpLevel) in Elem and Id in Elem) \
                    or ('stop-' + str(TmpLevel) in Elem and Id in Elem):
                print 'del une truc'
                self.Historical.remove(Elem)
        print self.c[0], 'Delete  ', tmp - len(self.Historical), 'broadcast', self.c[4]

######################## GOTO ####################

    def GoToIncantation(self, Pos):
        if Pos == 1:
            self.SendMsg('avance\n')
        elif Pos == 2:
            self.SendMsg('avance\n')
            self.SendMsg('gauche\n')
            self.SendMsg('avance\n')
        elif Pos == 3:
            self.SendMsg('gauche\n')
            self.SendMsg('avance\n')
        elif Pos == 4:
            self.SendMsg('gauche\n')
            self.SendMsg('avance\n')
            self.SendMsg('gauche\n')
            self.SendMsg('avance\n')
        elif Pos == 5:
            self.SendMsg('gauche\n')
            self.SendMsg('gauche\n')
            self.SendMsg('avance\n')
        elif Pos == 6:
            self.SendMsg('droite\n')
            self.SendMsg('avance\n')
            self.SendMsg('droite\n')
            self.SendMsg('avance\n')
        elif Pos == 7:
            self.SendMsg('droite\n')
            self.SendMsg('avance\n')
        elif Pos == 8:
            self.SendMsg('avance\n')
            self.SendMsg('droite\n')
            self.SendMsg('avance\n')
        return 0

    def GoToStone(self, Where):
        if Where >= 1 and Where <= 3:
            self.SendMsg('avance\n')
            if Where == 1:
                self.SendMsg('gauche\n')
            if Where == 3:
                self.SendMsg('droite\n')
            if Where == 1 or Where == 3:
                self.SendMsg('avance\n')
    
        if Where >= 4 and Where <= 8:
            self.SendMsg('avance\n')
            self.SendMsg('avance\n')
            if Where == 4 or Where == 5:
                self.SendMsg('gauche\n')
            if Where == 7 or Where == 8:
                self.SendMsg('droite\n')
            if Where == 5 or Where == 7:
                self.SendMsg('avance\n')
            if Where == 4 or Where == 8:
                self.SendMsg('avance\n')
                self.SendMsg('avance\n')

        if Where >= 9 and Where <= 15:
            self.SendMsg('avance\n')
            self.SendMsg('avance\n')
            self.SendMsg('avance\n')
            if Where == 9 or Where == 10 or Where == 11:
                self.SendMsg('gauche\n')
            if Where == 13 or Where == 14 or Where == 15:
                self.SendMsg('droite\n')
            if Where == 11 or Where == 13:
                self.SendMsg('avance\n')
            if Where == 10 or Where == 14:
                self.SendMsg('avance\n')
                self.SendMsg('avance\n')
            if Where == 9 or Where == 15:
                self.SendMsg('avance\n')
                self.SendMsg('avance\n')
                self.SendMsg('avance\n')

        if Where >= 16 and Where <= 24:
            self.SendMsg('avance\n')
            self.SendMsg('avance\n')
            self.SendMsg('avance\n')
            self.SendMsg('avance\n')
            if Where == 16 or Where == 17 or Where == 18 or Where == 19:
                self.SendMsg('gauche\n')
            if Where == 21 or Where == 22 or Where == 23 or Where == 24:
                self.SendMsg('droite\n')
            if Where == 19 or Where == 21:
                self.SendMsg('avance\n')
            if Where == 18 or Where == 22:
                self.SendMsg('avance\n')
                self.SendMsg('avance\n')
            if Where == 17 or Where == 23:
                self.SendMsg('avance\n')
                self.SendMsg('avance\n')
                self.SendMsg('avance\n')
            if Where == 16 or Where == 24:
                self.SendMsg('avance\n')
                self.SendMsg('avance\n')
                self.SendMsg('avance\n')
                self.SendMsg('avance\n')

######################### TAKE #######################
    def HowManyFood(self):
        Invent = self.SendMsg('inventaire\n').replace('{', '').replace('}', '').replace('\n', '').split(',')
        for Elem in Invent:
            Food = Elem.split(' ')            
            if Food[0] == 'nourriture':
                print self.c[0], 'jai ', Food[1], ' de bouffe', self.c[4]
                return int(Food[1])

    def LookingForFood(self, num):
        while self.HowManyFood() < num:
            Vision = self.GetVision()
            i = 0
            while i < len(Vision):
                if 'nourriture' in Vision[i]:
                    self.Take('nourriture', i)
                    break
                i += 1
        return 0

    def TakeFood(self):
        Vision = self.GetVision()
        if 'nourriture' in Vision[0]:
            self.Take('nourriture')

    def Take(self, What, Where = 0):
        if Where != 0:
            self.GoToStone(Where)
        if self.SendMsg('prend ' + What + '\n') == 'ok\n':
            if What != 'nourriture':
                self.Need[What] -= 1
            return 0
        else:
            return 1

    def TakeAll(self):
        print 'Prend toutes les pierres et nourriture sur la case'
        CurrentCase = self.SendMsg('voir\n').replace('{', '').replace('}', '').replace('\n', '').split(',')[0]
        if ' ' in CurrentCase:
            SubCurrentCase = CurrentCase.split(' ')
            for Elem in SubCurrentCase:
                if Elem != 'joueur' and Elem != '' and self.Take(Elem, 0) == 0:
                    if Elem != 'nourriture':
                        self.Need[Elem] -= 1
        else:
            if CurrentCase != 'joueur' and CurrentCase != '' and self.Take(CurrentCase, 0) == 0:
                if Currentcase != 'nourriture':
                    self.Need[CurrentCase] -= 1

    def TakeAllOne(self):
        CurrentCase = self.SendMsg('voir\n').replace('{', '').replace('}', '').replace('\n', '').split(',')[0]
        if ' ' in CurrentCase:
            SubCurrentCase = CurrentCase.split(' ')
            for Elem in SubCurrentCase:
                if Elem != 'joueur' and Elem != '' and Elem != 'linemate' and self.Take(Elem) == 0:
                    if Elem != 'nourriture':
                        self.Need[Elem] -= 1
        else:
            if CurrentCase != 'joueur' and CurrentCase != '' and CurrentCase != 'linemate' and self.Take(CurrentCase) == 0:
                if Currentcase != 'nourriture':
                    self.Need[CurrentCase] -= 1

######################## SIMPLE CMD ########################

    def See(self):
        Vision = self.GetVision()
        Pos = 0
        for Elem in Vision:
            if ' ' in Elem:
                SubVision = Elem.split(' ')
                for SubElem in SubVision:
                    if SubElem != 'joueur' and SubElem != '' and SubElem != 'nourriture' and self.Need[SubElem] > 0:
                        return (SubElem, Pos)
            else:
                if Elem != 'joueur' and Elem != '' and Elem != 'nourriture' and self.Need[Elem] > 0:
                    return (Elem, Pos)
            Pos += 1
        return ('nothing', -1)

    def Put(self):
        print 'Pose les pierres necessaire a l incantation'
        Tmp = self.L[self.Level]
        for Elem in Tmp:
            if self.SendMsg('pose ' + Elem + '\n') == 'ko\n':
                print 'ERROR PAUSE !'
        return 0

    def Fork(self):
        Slot = self.SendMsg('connect_nbr\n')
        for Elem in range(int(Slot)):
            print 'execute ./Main.py -p {} -t {} &'.format(self.Port, self.Team)
            os.system('./Main.py -p {} -t {} &'.format(self.Port, self.Team))

    def Inventaire(self):
        self.UpdateNeeds()
        Invent = self.SendMsg('inventaire\n').replace('{', '').replace('}', '').replace('\n', '').split(',')
        for Elem in Invent:
            SubInvent = Elem.split(' ')
            if SubInvent[0] != 'nourriture':
                print SubInvent
                self.Need[SubInvent[0]] -= int(SubInvent[1])
            else:
                print self.c[5], 'nourriture : ', SubInvent[1], self.c[4]

    def Incantation(self):
        print '-> ', self.GetVision()
        print 'Incantation ..... to level ', self.Level + 1 #
        self.Socket.send('incantation\n'.encode())
        while True:
            A = self.Socket.recv(4096).decode()
            tmp = A.split('\n')
            for Elem in tmp:
                if Elem == 'mort':
                    sys.exit()##
                elif Elem == 'ko':
                    print '/!\ ERROR Incation'#
                    return 1
                elif Elem != 'elevation en cours':
                    self.Historical.insert(0, Elem + '\n')
                else:
                    print 'boss attent niveau actuel ', self.Level + 1, ' id = ', self.Id
                    while True:
                        A = self.Socket.recv(4096).decode()
                        tmp = A.split('\n')
                        print self.c[4], A, self.c[5],
                        for Elem in tmp:
                            if Elem == 'mort':
                                sys.exit()
                            elif 'niveau actuel' in Elem:
                                return 0
                            elif Elem == 'ko':
                                print '/!\ ERROR Incation'#
                                return 1
                            else:
                                self.Historical.insert(0, Elem + '\n')

    def SendMsg(self, Message):
        self.Socket.send(Message.encode())
        print self.c[self.Level], 'envois >', self.c[1], Message, self.c[5], #
        while True:
            A = self.Socket.recv(4096).decode()
            print A,
            if A == 'mort\n':
                sys.exit()
            elif Message == 'inventaire\n':
                plop = 1
                tmp = A.split('\n')
                for Elem in tmp:
                    if 'nourriture' in Elem and \
                            'linemate' in Elem and \
                            'deraumere' in Elem and \
                            'sibur' in Elem and \
                            'mendiane' in A and \
                            'phiras' in Elem and \
                            'thystame' in Elem and \
                            Elem[0] == '{' and \
                            Elem[-1] == '}' and \
                            Elem.count(',') == 6:
                        plop = 0
                        ret = Elem
                    else:
                        if Elem != '':
                            self.Historical.insert(0, Elem + '\n')
                if plop == 0:
                    break
            elif Message == 'voir\n':
                plop = 1
                tmp = A.split('\n')
                for Elem in tmp:
                    if Elem != '' and (Elem[0] == '{' and Elem[-1] == '}') and (Elem.count(',') >= 3):
                        plop = 0
                        ret = Elem
                    else:
                        if Elem != '':
                            self.Historical.insert(0, Elem + '\n')
                if plop == 0:
                    break
            elif (Message == 'avance\n' or Message == 'droite\n' or Message == 'gauche\n' or Message == 'fork\n' or 'broadcast ' in Message):
                plop = 1
                tmp = A.split('\n')
                for Elem in tmp:
                    if Elem == 'ok':
                        plop = 0
                        ret = Elem
                    else:
                        if Elem != '':
                            self.Historical.insert(0, Elem + '\n')
                if plop == 0:
                    if (Message == 'avance\n'):
                        self.TakeFood()
                    break
            elif 'prend ' in Message  or 'pose ' in Message or 'expulse ' in Message:
                plop = 1
                tmp = A.split('\n')
                for Elem in tmp:
                    if Elem  == 'ok' or Elem == 'ko':
                        plop = 0
                        ret = Elem
                    else:
                        if Elem != '':
                            self.Historical.insert(0, Elem + '\n')
                if plop == 0:
                    break
            else:
                print 'pass dans le truc chelou'
                self.Historical.insert(0, A)
        print self.c[self.Level], 'recois >', self.c[1], ret, self.c[5] #
        return ret + '\n'

    def IsReady(self):
        return (0 if (self.Need['linemate'] <= 0 and
                      self.Need['deraumere'] <= 0 and
                      self.Need['sibur'] <= 0 and
                      self.Need['mendiane'] <= 0 and
                      self.Need['phiras'] <= 0 and
                      self.Need['thystame'] <= 0) else 1)

    def UpdateNeeds(self):
        self.Need['linemate'] = 0
        self.Need['deraumere'] = 0
        self.Need['sibur'] = 0
        self.Need['mendiane'] = 0
        self.Need['phiras'] = 0
        self.Need['thystame'] = 0
        if self.Level == 0:
            self.Need['linemate'] = 1
        elif self.Level == 1:
            self.Need['linemate'] = 1
            self.Need['deraumere'] = 1
            self.Need['sibur'] = 1
        elif self.Level == 2:
            self.Need['linemate'] = 2
            self.Need['sibur'] = 1
            self.Need['phiras'] = 2
        elif self.Level == 3:
            self.Need['linemate'] = 1
            self.Need['deraumere'] = 1
            self.Need['sibur'] = 2
            self.Need['phiras'] = 1
        elif self.Level == 4:
            self.Need['linemate'] = 1
            self.Need['deraumere'] = 2
            self.Need['sibur'] = 1
            self.Need['mendiane'] = 3
        elif self.Level == 5:
            self.Need['linemate'] = 1
            self.Need['deraumere'] = 2
            self.Need['sibur'] = 3
            self.Need['phiras'] = 1
        elif self.Level == 6:
            self.Need['linemate'] = 2
            self.Need['deraumere'] = 2
            self.Need['sibur'] = 2
            self.Need['mendiane'] = 2
            self.Need['phiras'] = 2
            self.Need['thystame'] = 1

    def LevelOne(self):
        Count = 0
        #        self.SendMsg('fork\n')
        while True:
            What, Where = self.See()
            if Where != -1:
                if Where != 0:
                    self.GoToStone(Where)
                self.TakeAllOne()
                if self.Incantation() == 0:
                    self.Level += 1
                    print ' --> LEVEL 1 <--'
                    return
            self.SendMsg('avance\n')
            Count += 1
            if Count == 10:
                self.SendMsg('droite\n')
                Count = 0

    def GetVision(self):
         Vision = self.SendMsg('voir\n').replace('{', '').replace('}', '').replace('\n', '').split(',')
         return Vision


    def CheckBroadcast(self):
        for Elem in self.Historical:
            if Elem == '':
                print 'pas de mec qui attend pour sincanter'
                return 'ko'
            if 'stop-' in Elem:
                Level = Elem.split('stop-')[1].split('-')[0]
                Id2 = Elem.split('-')[2]
                print 'clear1 level ', Level
                self.ClearHistorical(Id2, Level)
            elif 'ignore-' in Elem:
                Level = Elem.split('ignore-')[1].split('-')[0]
                Id2 = Elem.split('-')[2]
                print 'clear2 level ', Level
                self.ClearHistorical(Id2, Level)
            elif 'ready-'+ str(self.Level + 1) in Elem:
                ItsId = Elem.replace('\n', '').split('-')[-1]
                print 'ya un mec pres, au meme niveau que moi son id est :', ItsId
                return ItsId
        print 'pas de mec pret'
        return 'ko'

    def FindWay(self, ItsId):
        while True:
            print  self.Id, ' attend que ', ItsId, ' me dise ou aller'
            A = self.Socket.recv(4096).decode()# check each answer
            print self.c[5], 'Way', A, self.c[4] 
            tmp = A.split('\n')
            for Elem in tmp:
                if 'wait-'+ str(self.Level + 1) + '-' + ItsId in Elem and self.Id in Elem:
                    Pos = int(Elem.replace(',', ' ').split(' ')[1])
                    if Pos == 0:
                        self.SendMsg('broadcast arrived-'+ str(self.Level + 1) + '-' + ItsId + '-' + self.Id + '\n')
                        print 'shit attent niveau actuel ', self.Level + 1, ' id = ', self.Id
                        while True:
                            A = self.Socket.recv(4096).decode()
                            tmp2 = A.split('\n')
                            for Elem2 in tmp2:
                                if 'niveau actuel' in Elem2:
                                    self.Level += 1
                                    print ' --> LEVEL ', self.Level, ' <--'#
                                    self.Inventaire()
                                    return 0
                                else:
                                    self.Historical.insert(0, Elem2 + '\n')
                    else:
                        print self.c[1], 'avance vers mec', self.c[4]
                        self.GoToIncantation(Pos)
                else:
                    if 'stop-'+ str(self.Level + 1) + '-' + ItsId in Elem and self.Id in Elem:
                        print 'j abandonne le mec ma dit stop'
                        self.ClearHistorical(ItsId, self.Level + 1)
                        return 1
                    else:
                        self.Historical.insert(0, Elem + '\n')
        
    def Me(self, ItsId):
        while True:
            self.SendMsg('broadcast me-'+ str(self.Level + 1) + '-' + ItsId + '-' + self.Id + '\n')
            for Elem in self.Historical:
                if 'wait-'+ str(self.Level + 1) + '-' + ItsId in Elem and self.Id in Elem:
                    print 'le mec m a accepter'
                    return 0
                elif ('stop-'+ str(self.Level + 1) + '-' + ItsId in Elem) or ('ignore-'+ str(self.Level + 1) + '-' + ItsId in Elem and self.Id in Elem):
                    self.ClearHistorical(ItsId, self.Level + 1)
                    print 'le mec m a refuse'
                    return 1
        return 1

    def WaitCollegue(self):
        print 'READY to level-up'
        self.SendMsg('broadcast ready-' + str(self.Level + 1) + '-' + self.Id + '\n')
        IdConcerned = []
        CountArrived = 0
        i = 0
        while True:
            i += 1
            #if i == 20 and len(IdConcerned) == 0:
            #   print 'cest mort...\n\n'
            #  self.SendMsg('broadcast stop-'+ str(self.Level + 1) + '-' + self.Id + '\n')
            # return 1
            self.SendMsg('broadcast wait-'+ str(self.Level + 1) + '-' + self.Id + '-' + str(IdConcerned) + '\n')
            for Elem in self.Historical:
                if 'me-'+ str(self.Level + 1) + '-' + self.Id in Elem:
                    TmpId = Elem.replace('\n', '').split('-')[-1]
                    print 'ya un mec qui m a envoyer me et son id est ', TmpId
                    if len(IdConcerned) < self.Player[self.Level] and TmpId not in str(IdConcerned):
                        IdConcerned.append(TmpId)
                    elif TmpId not in str(IdConcerned):
                        self.SendMsg('broadcast ignore-'+ str(self.Level + 1) + '-' + self.Id + '-' + TmpId + '\n')
                    self.Historical.remove(Elem)
                elif 'arrived-'+ str(self.Level + 1) + '-' + self.Id in Elem:
                    TmpId = Elem.replace('\n', '').split('-')[-1]
                    if TmpId in str(IdConcerned):
                        print '-------------------un mec de plus darrive sur ma case--------------------------'
                        CountArrived += 1
                        self.Historical.remove(Elem)
                """
                elif 'me-' in Elem and  '-' + self.Id + '-' in Elem:
                    print self.c[5], '\n\n le mec se plante de niveau', self.c[4]
                    TmpId = Elem.replace('\n', '').split('-')[-1]
                    TmpLevel = Elem.split('me-')[1].split('-')[0]
                    self.SendMsg('broadcast ignore-'+ str(TmpLevel) + '-' + self.Id + '-' + TmpId + '\n')
                    self.Historical.remove(Elem)"""
            if CountArrived == self.Player[self.Level]:
                print 'assez de mec que ma case pour mincanter'
                return 0

    def Run(self):
        self.Inventaire()
        while True:
            self.LookingForFood(8 + self.Level)
            ItsId = self.CheckBroadcast()
            if ItsId != 'ko':
                print self.c[5], 'its id ', ItsId, self.c[4]
                Pos = self.Me(ItsId)
                if Pos == 1:
                    continue
                else:
                    self.FindWay(ItsId)
                    continue
            else:
                if self.IsReady() == 0:
                    self.LookingForFood(15)
                    self.WaitCollegue()
                    self.SendMsg('broadcast stop-'+ str(self.Level + 1) + '-' + self.Id + '\n')
                    self.TakeAll()
                    self.Put()
                    if self.Incantation() == 0:
                        self.Level += 1
                        print ' --> LEVEL ', self.Level, ' <--'#
                        self.Inventaire()
                        #self.Fork()
                        continue
            What, Where = self.See()
            if Where != -1:
                self.Take(What, Where)
            self.SendMsg('avance\n')
 
