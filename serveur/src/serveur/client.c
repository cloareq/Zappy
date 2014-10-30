#include <stdlib.h>

#include "lerror.h"
#include "serveur.h"

void	addClient(serveur* this, fd_set* rd) {
  clients*	node;
  _fd		newClient;

  if (FD_ISSET(this->serv, rd)) {
    if ((newClient = accept(this->serv, NULL, NULL)) == -1)
      lerror(FUNCTION_ERROR("accept()"));
    if ((node = malloc(sizeof(clients))) == NULL)
      lerror(MEMORY_ERROR(sizeof(iaClients)));
    node->next = this->unaffecteds;
    node->client = newClient;
    node->rdBuffer = createBuffer();
    this->unaffecteds = node;
    node->welcome = false;
  }
}
