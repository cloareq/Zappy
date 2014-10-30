#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "lerror.h"
#include "serveur.h"
#include "monitor.h"

static void	iaForkInit(serveur* this, iaClients* _egg, iaClients* ia) {
  (void)this;
  _egg->iaClient = FD_NOSET;
  _egg->pause = READY;
  _egg->wrBuffer = createBuffer();
  _egg->rdBuffer = createBuffer();
  _egg->state = egg;
  _egg->depletingNut = pBirth + uLife;
  _egg->pause = pBirth;
  _egg->lvl = 1;
  _egg->_o = random() % maxOrientation;
  _egg->_p.x = ia->_p.x;
  _egg->_p.y = ia->_p.y;
}

void	iaFork		(serveur* this, iaClients* ia, char* i) {
  iaClients* node;

  (void)i;
  avertMonitor(this, mBegFork(ia->num));
  if ((node = malloc(sizeof(iaClients))) == NULL)
    lerror(MEMORY_ERROR(sizeof(iaClients)));
  node->next = ia->next;
  ia->next = node;
  node->num = this->num;
  this->num += 1;
  iaForkInit(this, node, ia);
  bzero(node->stash, sizeof(node->stash));
  (node->stash)[nourriture] = 10;
  ia->pause = pFork;
  pushNode(ia->wrBuffer, strdup("ok\n"));
  avertMonitor(this, mEndFork(node->num, ia->num, ia->_p.x, ia->_p.y));
}
