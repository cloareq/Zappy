#ifndef __RESSOURCE_H__
# define __RESSOURCE_H__

typedef enum eRessource{
  error = -1,
  nourriture = 0,
  linemate,
  deraumere,
  sibur,
  mendiane,
  phiras,
  thystame,
  ressourceLength,
} ressource;

char*	getRessourceOnMap(char* ressource);
ressource getRessourceId(char* ressource);

#endif
