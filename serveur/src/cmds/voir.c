#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "serveur.h"

static void	updatePosition(iaClients* ia,
			       int front, int side, position *p) {
  p->x = ia->_p.x;
  p->y = ia->_p.y;
  p->x += 
    -(ia->_o == haut  ) * side +
    +(ia->_o == gauche) * front +
    +(ia->_o == bas   ) * side +
    -(ia->_o == droite) * front;
  p->y += 
    -(ia->_o == haut  ) * front +
    -(ia->_o == gauche) * side +
    +(ia->_o == bas   ) * front +
    +(ia->_o == droite) * side;
}

static void	seeForPlayer(teams* node, iaClients* ignored, position *p, char** r) {
  iaClients* _node;
  char* rs;

  if (!node)
    return ;
  _node = node->list;
  while (_node)
    {
      if (_node->_p.x == p->x && _node->_p.y == p->y && _node->state == alive)
	{
	  asprintf(r, "%s joueur", rs = *r);
	  free(rs);
	}
      _node = _node->next;
    }
  seeForPlayer(node->next, ignored, p, r);
}

static char*	seeAt(serveur* this, iaClients* ia, int front, int side) {
  position	p;
  char*		r;
  char*		rs;
  char*		rp;

  updatePosition(ia, front, -side, &p);
  if (p.y < 0)
    p.y = this->size.y - 1;
  if (p.x < 0)
    p.x = this->size.x - 1;
  if (p.y >= this->size.y)
    p.y = 0;
  if (p.x >= this->size.x)
    p.x = 0;
  rp = strdup("");
  seeForPlayer(this->teams, ia, &p, &rp);
  asprintf(&r, "%s%s", rp, rs = getRessourceOnMap(GET_SQUARE(this, p.x, p.y)));
  free(rp);
  free(rs);
  return (r);
}

static char* concatSee(char* s1, char* s2, bool b) {
  char *rs;

  if (!b)
    asprintf(&rs, "%s%s,", s1, s2);
  else
    asprintf(&rs, "%s%s}\n", s1, s2);
  free(s1);
  free(s2);
  return (rs);
}

void	iaVoir		(serveur* this, iaClients* ia, char* ign) {
  int i;
  int ik;
  char* r;
  char* rs;

  (void)ign;
  i = 0;
  rs = strdup("{");
  while (i <= ia->lvl) {
    ik = -i;
    while (ik <= i) {
      r = seeAt(this, ia, i, ik);
      rs = concatSee(rs, r, i == ia->lvl && ik == i);
      ik += 1;
    }
    i += 1;
  }
  ia->pause = 7;
  pushNode(ia->wrBuffer, rs);
}
