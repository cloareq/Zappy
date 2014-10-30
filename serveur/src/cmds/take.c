#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "serveur.h"
#include "ressource.h"
#include "monitor.h"

void	iaPrend		(serveur* this, iaClients* ia, char* i) {
  ressource n;
  char*	r;

  n = getRessourceId(i + strlen("prend "));
  if (n != -1 && (r = GET_SQUARE(this, ia->_p.x, ia->_p.y))[n])
    {
      (GET_SQUARE(this, ia->_p.x, ia->_p.y))[n] -= 1;
      ia->stash[n] += 1;
      avertMonitor(this, mPrendPlayer(ia->num, n));
      avertMonitor(this, mStashPlayer(ia->num, ia->_p.x, ia->_p.y,
				      (ia->stash)[nourriture], (ia->stash)[linemate],
				      (ia->stash)[deraumere], (ia->stash)[sibur],
				      (ia->stash)[mendiane], (ia->stash)[phiras],
				      (ia->stash)[thystame]));
      avertMonitor(this, mCaseMap(ia->_p.x, ia->_p.y,
				  r[nourriture], r[linemate], r[deraumere],
				  r[sibur], r[mendiane], r[phiras], r[thystame]
				  ));
      pushNode(ia->wrBuffer, strdup("ok\n"));
    }
  else
    pushNode(ia->wrBuffer, strdup("ko\n"));
}

void	iaPose		(serveur* this, iaClients* ia, char* i) {
  ressource n;
  char*	r;

  n = getRessourceId(i + strlen("pose "));
  if (n != -1 && (ia->stash)[n])
    {
      (r = GET_SQUARE(this, ia->_p.x, ia->_p.y))[n] += 1;
      ia->stash[n] -= 1;
      pushNode(ia->wrBuffer, strdup("ok\n"));
      avertMonitor(this, mPosePlayer(ia->num, n));
      avertMonitor(this, mStashPlayer(ia->num, ia->_p.x, ia->_p.y,
				      (ia->stash)[nourriture], (ia->stash)[linemate],
				      (ia->stash)[deraumere], (ia->stash)[sibur],
				      (ia->stash)[mendiane], (ia->stash)[phiras],
				      (ia->stash)[thystame]));
      avertMonitor(this, mCaseMap(ia->_p.x, ia->_p.y,
				  r[nourriture], r[linemate], r[deraumere],
				  r[sibur], r[mendiane], r[phiras], r[thystame]
				  ));
    }
  else
    pushNode(ia->wrBuffer, strdup("ko\n"));
}
