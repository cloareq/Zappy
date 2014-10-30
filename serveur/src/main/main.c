#include <stdlib.h>

#include "serveur.h"
#include "argues.h"

int main(int ac, char** av)
{
  struct args*	arg;
  serveur*	serv;

  arg  = getArgs(ac, av);
  serv = factory(arg);
  while (1)
    actualize(serv);
  free(arg);
  destroy(serv);
  return (0);
}
