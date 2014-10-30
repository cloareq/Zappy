#define _GNU_SOURCE
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "monitor.h"
#include "serveur.h"

void	avertTeam(serveur* this, clients* monitor) {
  teams*	team;

  team = this->teams;
  while (team)
    {
      avertThisMonitor(monitor, mNameTeam(team->name));
      team = team->next;
    }
}
