#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "monitor.h"
#include "serveur.h"

static int	retrieveDiff(int pmax, int p1, int p2) {
  int p;

  p = (N(p2 - p1) < N(pmax + p1 - p2)) ?
    (p2 - p1) : (pmax + p1 - p2);
  return (p);
}

static int	retrieveDist(position* mapSize, position *p1, position* p2, orientation o) {
  position	p;
  int		d;

  p.x = retrieveDiff(mapSize->x, p1->x, p2->x);
  p.y = retrieveDiff(mapSize->y, p1->y, p2->y);
  p.x = (p.x > 0) ? (5) : (p.x < 0) ? (1) : (0);
  p.y = (p.y > 0) ? (3) : (p.y < 0) ? (7) : (0);
  if (p.x == 1 && p.y == 7)
    d = (8);
  else if (p.y == 0)
    d = p.x;
  else if (p.x == 0)
    d = p.y;
  else
    d = ((p.y + p.x) / 2);
  if (d == 0)
    return (0);
  if (o == droite)
    return (d);
  if (o == haut)
    d = (d + 2) % 8;
  else if (o == gauche)
    d = (d + 2 + 2) % 8;
  if (o == bas)
    d = (d + 2 + 2 + 2) % 8;
  return ((d) ? (d) : (8));
}

static void	sendMsg(iaClients* ia, iaClients* ignored,
			position *size, char* msg) {
  char* k;

  asprintf(&k, "message %d,%s",
	   retrieveDist(size, &(ia->_p), &(ignored->_p), ia->_o),
	   msg);
  pushNode(ia->wrBuffer, k);
}

static void	dispatchMsg(teams* node, position* size,
			    iaClients* ignored, char* msg) {
  iaClients*	c;

  if (!node)
    return ;
  c = node->list;
  while (c) {
    if (c != ignored && c->iaClient != -1)
      sendMsg(c, ignored, size, msg);
    c = c->next;
  }
  dispatchMsg(node->next, size, ignored, msg);
}

void	iaBroadcast	(serveur* this, iaClients* ia, char* i) {
  char* msg;

  msg = i + strlen("broadcast ");
  dispatchMsg(this->teams, &(this->size), ia, msg);
  ia->pause = 7;
  pushNode(ia->wrBuffer, strdup("ok\n"));
  avertMonitor(this, mBroadcastPlayer(ia->num, msg));
}
