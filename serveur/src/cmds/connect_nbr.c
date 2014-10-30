#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "lerror.h"
#include "serveur.h"

teams* getTeam(teams* node, iaClients* ia) {
  iaClients* i;

  if (!node)
    return (NULL);
  i = node->list;
  while (i)
    {
      if (i == ia)
	return (node);
      i = i->next;
    }
  return (getTeam(node->next, ia));
}

void	iaConnect_nbr	(serveur* this, iaClients* ia, char* i) {
  teams* t;
  char*	s;

  (void)i;
  t = getTeam(this->teams, ia);
  asprintf(&s, "%d\n", t->unaff_size);
  pushNode(ia->wrBuffer, s);
}
