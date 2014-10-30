#define _GNU_SOURCE
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "monitor.h"
#include "serveur.h"

void	avertCase(serveur* this, clients* monitor, char* k) {
  position p;
  char*		r;

  sscanf(k, "bct %d %d\n", &(p.x), &(p.y));
  r = GET_SQUARE(this, p.x, p.y);
  avertThisMonitor(monitor,
		   mCaseMap(p.x, p.y,
			    r[nourriture], r[linemate], r[deraumere],
			    r[sibur], r[mendiane], r[phiras],
			    r[thystame]
			    ));
}

void	avertMap(serveur* this, clients* monitor) {
  position	p;
  char* r;

  p.x = 0;
  while (p.x < this->size.x)
    {
      p.y = 0;
      while (p.y < this->size.y)
	{
	  r = GET_SQUARE(this, p.x, p.y);
	  avertThisMonitor(monitor,
			   mCaseMap(p.x, p.y,
				    r[nourriture], r[linemate], r[deraumere],
				    r[sibur], r[mendiane], r[phiras],
				    r[thystame]));
	  p.y += 1;
	}
      p.x += 1;
    }
}
