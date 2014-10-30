#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "serveur.h"
#include "ressource.h"

static char*	addS(char* r, char* ressource, int n) {
  char* rs;
  int	i;

  i = 0;
  rs = NULL;
  while (i < n)
    {
      asprintf(&rs, "%s %s", r, ressource);
      free(r);
      r = rs;
      i++;
    }
  return (rs);
}

char*	getRessourceOnMap(char* ressource) {
  char* r;

  r = strdup("");
  if (ressource[linemate])
    r = addS(r, " linemate", ressource[linemate]);
  if (ressource[deraumere])
    r = addS(r, " deraumere", ressource[deraumere]);
  if (ressource[sibur])
    r = addS(r, " sibur", ressource[sibur]);
  if (ressource[mendiane])
    r = addS(r, " mendiane", ressource[mendiane]);
  if (ressource[phiras])
    r = addS(r, " phiras", ressource[phiras]);
  if (ressource[thystame])
    r = addS(r, " thystame", ressource[thystame]);
  if (ressource[nourriture])
    r = addS(r, " nourriture", ressource[nourriture]);
  return (r);
}

ressource getRessourceId(char* ressource) {
  printf("ressource %s", ressource);
  if (!strcmp(ressource, "nourriture\n"))
    return (nourriture);
  if (!strcmp(ressource, "linemate\n"))
    return (linemate);
  if (!strcmp(ressource, "sibur\n"))
    return (sibur);
  if (!strcmp(ressource, "mendiane\n"))
    return (mendiane);
  if (!strcmp(ressource, "phiras\n"))
    return (phiras);
  if (!strcmp(ressource, "thystame\n"))
    return (thystame);
  if (!strcmp(ressource, "deraumere\n"))
    return (deraumere);
  return (-1);
}

void	iaInventaire	(serveur* this, iaClients* ia, char* i) {
  char* s;

  (void)this;
  (void)i;
  asprintf(&s, "{nourriture %d,linemate %d,deraumere %d\
,sibur %d,mendiane %d,phiras %d,thystame %d}\n",
	   (ia->stash)[nourriture],
	   (ia->stash)[linemate],
	   (ia->stash)[deraumere],
	   (ia->stash)[sibur],
	   (ia->stash)[mendiane],
	   (ia->stash)[phiras],
	   (ia->stash)[thystame]
	   );
  pushNode(ia->wrBuffer, s);
  ia->pause = 1;
}
