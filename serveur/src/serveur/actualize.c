#include <stdio.h>

#include "serveur.h"

static int	fetchIAClient(iaClients* node, fd_set *rd, fd_set *wr) {
  int	max;
  int	tmax;

  if (!node)
    return (0);
  if (node->iaClient >= 0) {
    max = node->iaClient;
    FD_SET(max, rd);
    FD_SET(max, wr);
    max += 1;
  }
  else
    max = 0;
  tmax = fetchIAClient(node->next, rd, wr);
  return ((tmax > max) ? (tmax) : (max));
}

static int	fetchTeam(teams* node, fd_set *rd, fd_set *wr) {
  int	max;
  int	tmax;

  if (!node)
    return (0);
  max = fetchIAClient(node->list, rd, wr);
  tmax = fetchTeam(node->next, rd, wr);
  return ((tmax > max) ? (tmax) : (max));
}

static int	fetchClient(clients* node, fd_set *rd, bool doWr, fd_set *wr) {
  int	max;
  int	tmax;

  if (!node)
    return (0);
  FD_SET(node->client, rd);
  max = node->client + 1;
  if (doWr)
    FD_SET(node->client, wr);
  tmax = fetchClient(node->next, rd, doWr, wr);
  if (tmax > max)
    max = tmax;
  return (max);
}

static int	fetchFDS(serveur* this, fd_set *rd, fd_set *wr) {
  int max;
  int tmax;

  FD_SET(this->serv, rd);
  max = this->serv + 1;
  if ((tmax = fetchClient(this->unaffecteds, rd, true, wr)) > max)
    max = tmax;
  if ((tmax = fetchClient(this->monitor, rd, true, wr)) > max)
    max = tmax;
  if (this->waiting)
    if ((tmax = fetchClient(&(this->waiting->_), rd, false, NULL)) > max)
      max = tmax;
  tmax = fetchTeam(this->teams, rd, wr);
  if (tmax > max)
    max = tmax;
  return (max);
}

void	actualize(serveur* this)
{
  fd_set rd;
  fd_set wr;
  int	mx;
  int	k;
  struct timeval tv;

  k = 0;
  while (k <= 10)
    {
      FD_ZERO(&rd);
      FD_ZERO(&wr);
      mx = fetchFDS(this, &rd, &wr);
      tv.tv_sec = 0;
      tv.tv_usec = 0;
      select(mx, &rd, &wr, NULL, &tv);
      if (this->time)
	usleep((1.f/this->time * 1000000.f) / 50.f);
      else
	usleep(100000.f / 50.f);
      addClient(this, &rd);
      actualize_unaff(this, &rd, &wr);
      actualize_waiting(this, &rd, &wr);
      actualize_IA(this, &rd, &wr, k == 10);
      push_monitor(this, this->monitor, &rd, &wr);
      k++;
    }
}
