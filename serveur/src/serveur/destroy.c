#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "lerror.h"
#include "serveur.h"


static  void	clearClient(iaClients* t) {
  if (!t)
    return ;
  free(t->rdBuffer);
  free(t->wrBuffer);
  clearClient(t->next);
  free(t);
}

static  void	clearTeam(teams* t) {
  if (!t)
    return ;
  clearClient(t->list);
  clearTeam(t->next);
  free(t);
}

void	destroy(serveur* this) {
  free(this->ressources);
  clearTeam(this->teams);
  close(this->serv);
  free(this);
}
