#include <string.h>

#include "serveur.h"

_treating_	gettreat(int n) {
  if (n == 0)
    return (&iaAvance);
  if (n == 1)
    return (&iaDroite);
  if (n == 2)
    return (&iaGauche);
  if (n == 3)
    return (&iaVoir);
  if (n == 4)
    return (&iaInventaire);
  if (n == 5)
    return (&iaPrend);
  if (n == 6)
    return (&iaPose);
  if (n == 7)
    return (&iaExpulse);
  if (n == 8)
    return (&iaBroadcast);
  if (n == 9)
    return (&iaIncantation);
  if (n == 10)
    return (&iaFork);
  if (n == 11)
    return (&iaConnect_nbr);
  return (NULL);
}

void	include_treatement(serveur* this) {
  char*	s;
  int	itt;

  itt = 0;
  s = strdup(REQUEST);
  while (itt < NTREAT && ((this->cmds)[itt] = strsep(&s, "|")) != NULL)
    {
      (this->treat)[itt] = gettreat(itt);
      itt++;
    }
}
