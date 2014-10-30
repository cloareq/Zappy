#define _GNU_SOURCE
#include <stdio.h>
#include "serveur.h"
#include "monitor.h"

void	sendingIAData(serveur *this, iaClients* ia, teams* team) {
  char*		sending;

  asprintf(&sending, "%d\n", team->unaff_size);
  pushNode(ia->wrBuffer, sending);
  asprintf(&sending, "%d %d\n", this->size.x, this->size.y);
  pushNode(ia->wrBuffer, sending);
}

void	push_in_waiting(serveur* this, wclients* node) {
  teams*	team;
  iaClients*	ia;

  while (node)
    {
      team = getTeamById(this, node->team);
      ia = team->list;
      while (ia && ia->iaClient != -1 && (ia = ia->next) != NULL);
      if (!ia)
	node = (wclients*)node->_.next;
      else
	{
	  ia->iaClient = node->_.client;
	  ia->rdBuffer = node->_.rdBuffer;
	  ia->state = (ia->state == unaffected) ? (alive) : (ia->state);
	  team->unaff_size -= 1;
	  sendingIAData(this, ia, team);
	  if (ia->state == egg)
	    avertMonitor(this, mConnectEgg(ia->num));
	  avertMonitor(this, mNewPlayerendl(ia->num, ia->_p.x, ia->_p.y, ia->_o,
					ia->lvl, team->name));
	  node = del_waiting(this, node, false);
	}
    }
}

void	delToMuch(serveur* this, wclients* node)
{
  int i;

  i = 0;
  while (node)
    {
      if (i < 5000)
	node = (wclients*)node->_.next;
      else
	node = del_waiting(this, node, true);
    }
}

void	actualize_IA(serveur* this, fd_set* rd, fd_set* wr, bool buffered) {
  if (this->waiting)
    delToMuch(this, this->waiting);
  if (this->waiting)
    push_in_waiting(this, this->waiting);
  actualizeBuffering(this->teams, rd, wr);
  if (buffered)
    iaProcess(this, this->teams);
}
