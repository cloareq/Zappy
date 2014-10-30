#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "lerror.h"
#include "serveur.h"
#include "monitor.h"

static	void	fillRequired(int* ressource, int lvl) {
  ressource[nourriture] = 0;
  ressource[linemate] =
    (lvl == 3 || lvl == 7)	? (2) : (1);
  ressource[deraumere] =
    (lvl >= 5)			? (2) :
    (lvl == 2 || lvl == 4)	? (1) : (0);
  ressource[sibur] =
    (lvl == 6)			? (3) :
    (lvl == 4 || lvl == 7)	? (2) :
    (lvl == 1)			? (0) : (1);
  ressource[mendiane] =
    (lvl == 5)			? (3) :
    (lvl == 7)			? (2) : (0);
  ressource[phiras] =
    (lvl == 3 || lvl == 7)	? (2) :
    (lvl == 4 || lvl == 6)	? (1) : (0);
  ressource[thystame] =
    (lvl == 7)			? (1) : (0);
}

bool	testForRessource(serveur* this, iaClients* ia, int* ressource) {
  int	itt;
  char*	r;

  (void)this;
  fillRequired(ressource, ia->lvl);
  itt = 0;
  r = (GET_SQUARE(this, ia->_p.x, ia->_p.y));
  while (itt < ressourceLength)
    {
      if (r[itt] != ressource[itt])
	{
	  printf("FAIIIIIL BY RESSSOURCEEEEE\n");
	  return (false);
	}
      itt++;
    }
  return (true);
}
