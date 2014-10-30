#include <stdlib.h>
#include <string.h>

#include "get_line.h"
#include "lerror.h"
#include "serveur.h"

wclients* del_waiting(serveur* this, wclients* node, bool buffer) {
  wclients* pnod;
  wclients* nn;

  nn = (wclients*)node->_.next;
  free(node->team);
  if (this->waiting == node)
    this->waiting = (wclients*)node->_.next;
  else
    {
      pnod = (wclients*)this->waiting;
      while (pnod && pnod->_.next != (clients*)node)
	pnod = (wclients*)pnod->_.next;
      if (pnod)
	pnod->_.next = node->_.next;
    }
  if (buffer)
    destroyBuffer(node->_.rdBuffer, false);
  free(node);
  return (nn);
}

static int	propagate_buffer(serveur* this, wclients* node, fd_set* wr) {
  char* k;

  if (!node)
    return (0);
  if (FD_ISSET(node->_.client, wr))
    {
      if ((k = popNode(node->_.rdBuffer)))
	{
	  if (write(node->_.client, k, strlen(k)) < (int)strlen(k))
	    return (propagate_buffer(this, del_waiting(this, node, true), wr));
	}
    }
  return (propagate_buffer(this, (wclients*)node->_.next, wr));
}

static int	getcmd(serveur* this, wclients* node, fd_set* rd) {
  char* k;

  if (!node)
    return (0);
  if (FD_ISSET(node->_.client, rd))
    {
      if ((k = _get_socket(node->_.client)))
	return (getcmd(this, del_waiting(this, node, true), rd));
      pushNode(node->_.rdBuffer, k);
    }
  return (getcmd(this, (wclients*)node->_.next, rd));
}

static void	match_wrong(serveur* this, wclients* node) {
  while (node)
    {
      if (!getTeamById(this, node->team))
	node = del_waiting(this, node, true);
      else
	node = (wclients*)node->_.next;
    }
}

void	actualize_waiting(serveur* this, fd_set* rd, fd_set* wr) {
  match_wrong(this, this->waiting);
  getcmd(this, this->waiting, rd);
  propagate_buffer(this, this->waiting, wr);
}
