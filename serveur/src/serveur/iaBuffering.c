#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "serveur.h"
#include "get_line.h"

static iaClients* disable_iaClient(iaClients* node) {
  node->iaClient = -1;
  return (node->next);
}

iaClients* delete_iaClient(teams* team, iaClients* node) {
  iaClients* nn;

  destroyBuffer(node->rdBuffer, true);
  destroyBuffer(node->wrBuffer, true);
  nn = team->list;
  while (nn && nn != node && nn->next != node)
    nn = nn->next;
  if (nn == team->list)
    team->list = node->next;
  else if (nn)
    nn->next = node->next;
  nn = node->next;
  free(node);
  return (nn);
}

static int	actualizeByIa(teams* team, iaClients* node,
			      fd_set* rd, fd_set* wr)
{
  char* k;

  if (!node)
    return (0);
  if (node->iaClient == -1)
    return (actualizeByIa(team, node->next, rd, wr));
  if (FD_ISSET(node->iaClient, rd))
    {
      if ((k = _get_socket(node->iaClient)) == NULL)
	return (actualizeByIa(team, disable_iaClient(node), rd, wr));
      pushNode(node->rdBuffer, k);
      printf("received from iaClient[%d] > %s", node->iaClient, k);
    }
  if (FD_ISSET(node->iaClient, wr) && node->wrBuffer->size)
    while ((k = popNode(node->wrBuffer)) != NULL)
      {
	if (write(node->iaClient, k, strlen(k)) <= 0)
	  return (actualizeByIa(team, disable_iaClient(node), rd, wr));
	printf("send to iaClient[%d] > %s", node->iaClient, k);
	free(k);
      }
  return (actualizeByIa(team, node->next, rd, wr));
}

void	actualizeBuffering(teams* node, fd_set*rd, fd_set *wr) {
  if (!node)
    return ;
  actualizeByIa(node, node->list, rd, wr);
  actualizeBuffering(node->next, rd, wr);
}
