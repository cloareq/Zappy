#include <string.h>

#include "serveur.h"

teams*	getTeamById(serveur* this, char* k) {
  teams* node;

  if (!k)
    return (NULL);
  node = this->teams;
  while (node && node->name && !(!strncmp(node->name, k, strlen(k) - 1)
				 && strlen(node->name) == strlen(k) - 1))
    node = node->next;
  if (!node || !node->name)
    return (NULL);
  return (node);
}
