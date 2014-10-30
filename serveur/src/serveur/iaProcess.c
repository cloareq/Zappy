#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "serveur.h"
#include "monitor.h"

static void	_cmd(serveur* this, iaClients* ia, char* cmd) {
  int itt;

  if (!cmd)
    return ;
  itt = 0;
  while (itt < NTREAT)
    {
      if (!strncmp((this->cmds)[itt], cmd, strlen((this->cmds)[itt])))
	{
	  (this->treat)[itt](this, ia, cmd);
	  free(cmd);
	  return ;
	}
      itt++;
    }
  free(cmd);
}

static void	depletNut(serveur* this, iaClients* ia) {
  ia->depletingNut = uLife;
  (ia->stash)[nourriture] -= 1;
  avertMonitor(this,
	       mStashPlayer(ia->num, ia->_p.x, ia->_p.y,
			    (ia->stash)[nourriture],
			    (ia->stash)[linemate],
			    (ia->stash)[deraumere],
			    (ia->stash)[sibur],
			    (ia->stash)[mendiane],
			    (ia->stash)[phiras],
			    (ia->stash)[thystame]
			    ));
  if ((ia->stash)[nourriture] > 0)
    return ;
  ia->state = deleting;
  pushNode(ia->wrBuffer, strdup("mort\n"));
}

static iaClients*	_proc(serveur* this, iaClients* ia, teams* team) {
  if (!ia)
    return (NULL);
  if (ia->state == deleting && ia->wrBuffer->size)
    return (ia->next);
  else if (ia->state == deleting)
    return (delete_iaClient(team, ia));
  if (ia->state == unaffected)
    return (ia->next);
  ia->pause -= (ia->pause > 0);
  if (ia->pause)
    return (ia->next);
  ia->depletingNut -= 1;
  if (ia->state == egg)
    {
      avertMonitor(this, mPopEgg(ia->num));
      team->size += 1;
      team->unaff_size += 1;
    }
  ia->state = alive;
  if (!ia->depletingNut)
    depletNut(this, ia);
  _cmd(this, ia, popNode(ia->rdBuffer));
  return (ia->next);
}

void	iaProcess(serveur* this, teams* team) {
  iaClients*	node;

  if (!team)
    return ;
  node = team->list;
  while (node)
    node = _proc(this, node, team);  
  iaProcess(this, team->next);
}
