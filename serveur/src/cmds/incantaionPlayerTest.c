#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "lerror.h"
#include "serveur.h"
#include "monitor.h"

static void	testIa(iaClients* ia, iaClients* p, char** s, int* n) {
  char*	s2;

  if (!(ia->_p.x == p->_p.x && ia->_p.y == p->_p.y && ia->lvl == p->lvl) ||
      ia->state != alive)
    return ;
  *n -= 1;
  s2 = *s;
  asprintf(s, "%s %d", *s, ia->num);
  free(s2);
}

static void	testPlayer(teams* node, iaClients* ia, char** s, int* n) {
  iaClients*	_n;

  if (!node)
    return ;
  _n = node->list;
  while (_n)
    {
      testIa(_n, ia, s, n);
      _n = _n->next;
    }
  testPlayer(node->next, ia, s, n);
}

bool	testForPlayer(serveur* this, iaClients* ia) {
  int n;
  char*	s;
  bool	test;

  asprintf(&s, "pic %d %d %d", ia->_p.x, ia->_p.y, ia->lvl);
  n =
    (ia->lvl == 1) ? (1) :
    (ia->lvl == 2 || ia->lvl == 3) ? (2) :
    (ia->lvl == 4 || ia->lvl == 5) ? (4) :
    (ia->lvl == 6 || ia->lvl == 7) ? (6) : (0);
  testPlayer(this->teams, ia, &s, &n);
  test = (n == 0);
  if (test)
    avertMonitor(this, "%s\n", s);
  if (!test)
    printf ("FAIL BY    PLAYYYYYYYYERRRRRRR!!!!!\n");
  free(s);
  return (test);
}
