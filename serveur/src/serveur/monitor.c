#define _GNU_SOURCE
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "serveur.h"
#include "monitor.h"
#include "get_line.h"

void	avertMonitor(serveur* this, char* s, ... ) {
  clients* monitor;
  va_list cpy;
  va_list ap;
  char*	si;

  monitor = this->monitor;
  va_start(ap, s);
  while (monitor)
    {
      va_copy(cpy, ap);
      vasprintf(&si, s, cpy);
      pushNode(monitor->rdBuffer, si);
      monitor = monitor->next;
    }
  va_end(ap);
}

static clients*	deleteMonitor(serveur* this, clients* monitor) {
  clients* pre;

  pre = this->monitor;
  while (pre && pre != monitor && pre->next != monitor)
    pre = pre->next;
  if (pre == this->monitor)
    this->monitor = pre->next;
  else if (pre)
    pre->next = monitor->next;
  if (pre == this->monitor)
    pre = NULL;
  else
    pre = pre->next;
  destroyBuffer(monitor->rdBuffer, true);
  close(monitor->client);
  free(monitor);
  return (pre);
}

static bool	getrd(serveur* this, clients* node, fd_set *rd) {
  char*	k;

  if (!FD_ISSET(node->client, rd))
    return (true);
  k = _get_socket(node->client);
  if (k == NULL)
    return (false);
  printf("received Message From Client[%d], %s\n", node->client, k);  
  calcCmd(this, node, k);
  free(k);
  return (true);
}

static bool     pushwr(clients* node, fd_set* wr) {
  char* k;

  if (!FD_ISSET(node->client, wr))
    return (true);
  while ((k = popNode(node->rdBuffer)) != NULL)
    {
      if (write(node->client, k, strlen(k)) <= 0)
	return (false);
      printf("pushed Message To Client[%d], %s", node->client, k);
      free(k);
    }
  return (true);
}

void	push_monitor(serveur* this, clients* node, fd_set* rd, fd_set* wr) {
  bool	oui;

  while (node) {
    oui = getrd(this, node, rd);
    if (oui)
      oui = pushwr(node, wr);
    if (!oui)
      node = deleteMonitor(this, node);
    else
      node = node->next;
  }
}
