#ifndef __GAMETYPES_H__
# define __GAMETYPES_H__

# include <netdb.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>

typedef int _port;

typedef enum eOrientation{
  minOrientation = -1,
  haut = 0,
  gauche = 1,
  bas = 2,
  droite = 3,
  maxOrientation,
}	orientation;

typedef struct s_position{
  int	x;
  int	y;
} position;

typedef enum etime{
  waiting = -1,
  READY = 0,
  pAvance = 7,
  pRotation = 7,
  pVoir = 7,
  pInventaire = 1,
  pPrendre = 7,
  pExpulse = 7,
  pBroadcast = 7,
  pIncatation = 300,
  pFork = 42,
  pBirth = 600,
  uLife = 126,
}		gtime;

typedef enum estate{
  egg = 0,
  unaffected,
  alive,
  deleting,
} state;

typedef struct sexpulse{
  position	_p;
  orientation	_o;
} expulse;
  
typedef struct sLife{
  gtime	time;
  int	amount;
} life;

#endif
