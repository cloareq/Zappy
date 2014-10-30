#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "monitor.h"
#include "serveur.h"

static orientation	deductO(orientation o)
{
  if (o == gauche)
    return (droite);
  if (o == droite)
    return (gauche);
  if (o == haut)
    return (bas);
  if (o == bas)
    return (haut);
  return (0);
}

static void	deductP(serveur* this, position pp,
			orientation o, position *p) {
  p->x = pp.x;
  p->y = pp.y;
  p->x +=
    (o == gauche) ? (+1) :
    (o == droite) ? (-1) :
    (0);
  p->y +=
    (o == haut) ? (-1) :
    (o == bas)  ? (+1) :
    (0);
  if (p->y < 0)
    p->y = this->size.y;
  if (p->x < 0)
    p->x = this->size.x;
  if (p->y >= this->size.y)
    p->y = 0;
  if (p->x >= this->size.x)
    p->x = 0;
}

static void	updatePos(serveur*this,
			  iaClients* node, iaClients* exp,
			  expulse* e) {
  char* d;

  if (node->_p.x != exp->_p.x ||
      node->_p.y != exp->_p.y)
    return ;
  asprintf(&d, "deplacement %d\n", e->_o);
  pushNode(node->wrBuffer, d);
  node->_p.x = e->_p.x;
  node->_p.y = e->_p.y;
  if (node->_p.x < 0)
    node->_p.x = this->size.x -1;
  if (node->_p.y < 0)
    node->_p.y = this->size.y -1;
  if (node->_p.x >= this->size.x)
    node->_p.x = 0;
  if (node->_p.y >= this->size.y)
    node->_p.y = 0;
  avertMonitor(this, mPositionPlayer(node->num,
				     node->_p.x, node->_p.y,
				     node->_o));
}

static bool	dispatchNewPosition(serveur* this,
				    teams* node, iaClients* ignored,
				    expulse* e) {
  iaClients*	c;
  bool		test1;
  bool		test2;

  if (!node)
    return (false);
  test1 = false;
  c = node->list;
  while (c)
    {
      if (c != ignored && c->iaClient != -1)
	{
	  updatePos(this, c, ignored, e);
	  test1 = true;
	}
      c = c->next;
    }
  test2 = dispatchNewPosition(this, node->next, ignored, e);
  return (test1 || test2);
}

void	iaExpulse	(serveur* this, iaClients* ia, char* i) {
  expulse	e;

  (void)i;
  e._o = deductO(ia->_o);
  deductP(this, ia->_p, ia->_o, &(e._p));
  avertMonitor(this, mExpulsePlayer(ia->num));
  dispatchNewPosition(this, this->teams, ia, &e);
  pushNode(ia->wrBuffer, strdup("ok\n"));
  ia->pause = 7;
}
