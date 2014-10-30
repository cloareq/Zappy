#define _GNU_SOURCE
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "monitor.h"
#include "serveur.h"

static iaClients*	getClientByNum(teams* team, int num) {
  iaClients* ia;

  if (!team)
    return (NULL);
  ia = team->list;
  while (ia)
    {
      if (ia->num == num)
	return (ia);
      ia = ia->next;
    }
  return (getClientByNum(team->next, num));
}

void	avertPlayerPosition(serveur* this, clients* monitor, char* k) {
  int	num;
  iaClients* ia;

  sscanf(k, "ppo %d\n", &num);
  if ((ia = getClientByNum(this->teams, num)) == NULL)
    return ;
  avertThisMonitor(monitor, mPositionPlayer(num, ia->_p.x, ia->_p.y, ia->_o));
}

void	avertPlayerLevel(serveur* this, clients* monitor, char* k) {
  int	num;
  iaClients* ia;

  sscanf(k, "ppo %d\n", &num);
  if ((ia = getClientByNum(this->teams, num)) == NULL)
    return ;
  avertThisMonitor(monitor, mLvlPlayer(ia->num, ia->lvl));
}

void	avertPlayerInventaire(serveur* this, clients* monitor, char* k) {
  int	num;
  iaClients* ia;

  sscanf(k, "ppo %d\n", &num);
  if ((ia = getClientByNum(this->teams, num)) == NULL)
    return ;
  avertThisMonitor(monitor,
		   mStashPlayer(ia->num, ia->_p.x, ia->_p.y,
				(ia->stash)[nourriture], (ia->stash)[linemate],
				(ia->stash)[deraumere], (ia->stash)[sibur],
				(ia->stash)[mendiane], (ia->stash)[phiras],
				(ia->stash)[thystame]));
}
