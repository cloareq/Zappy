#ifndef __SERVEUR_H__
# define __SERVEUR_H__

#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

# include "teams.h"
# include "argues.h"

typedef struct s_serveur serveur;

# define NTREAT 12
# define REQUEST "avance|droite|gauche|voir|inventaire|prend |pose |expulse|broadcast |incantation|fork|connect_nbr"
typedef void	(*_treating_)(serveur*, iaClients*, char*);

typedef struct s_clients{
  struct s_clients	*next;
  _fd			client;
  circularBuffer	*rdBuffer;
  bool			welcome;
}clients;

typedef struct s_wclients{
  struct s_clients	_;
  char*			team;
}wclients;

# define GET_SQUARE(this, _x_, _y_) (&(((this)->ressources)[_x_ * (this)->size.y + _y_]))
# define N(_p_) ((_p_ < 0) ? (-_p_) : (_p_))

typedef struct s_serveur{
  /*	time		*/
  double	time;
  _fd		serv;

  /*	unaffected Clients	*/
  clients*	unaffecteds;

  /*	Monitors		*/
  clients*	monitor;

  /*	Clients		*/
  int			num;
  wclients*		waiting;		

  
  char*			cmds[NTREAT];
  _treating_		treat[NTREAT];
  teams*		teams;

  /*	map		*/
  position		size;
  char*		ressources;
}serveur;

serveur* factory(struct args*);
void	destroy(serveur*);
void	include_treatement(serveur*);

void	actualize(serveur*);
/* refresh */
iaClients* delete_iaClient(teams* team, iaClients* node);
void	addClient		(serveur*, fd_set*);
void	actualize_unaff		(serveur*, fd_set*, fd_set*);
void	actualize_waiting	(serveur*, fd_set*, fd_set*);
void	actualize_IA		(serveur*, fd_set*, fd_set*, bool);
void	push_monitor		(serveur*, clients*, fd_set*, fd_set*);
void	actualizeBuffering	(teams*, fd_set*, fd_set *);

/* teams */
teams*	getTeamById(serveur*, char*);
teams*  getTeam(teams*, iaClients*);

/* waiting */
wclients* del_waiting(serveur* this, wclients* node, bool);
void	iaProcess(serveur* this, teams* team);

void	iaAvance	(serveur* this, iaClients* ia, char*);
void	iaDroite	(serveur* this, iaClients* ia, char*);
void	iaGauche	(serveur* this, iaClients* ia, char*);
void	iaVoir		(serveur* this, iaClients* ia, char*);
void	iaInventaire	(serveur* this, iaClients* ia, char*);
void	iaPrend		(serveur* this, iaClients* ia, char*);
void	iaPose		(serveur* this, iaClients* ia, char*);
void	iaExpulse	(serveur* this, iaClients* ia, char*);
void	iaBroadcast	(serveur* this, iaClients* ia, char*);
void	iaIncantation	(serveur* this, iaClients* ia, char*);
void	iaFork		(serveur* this, iaClients* ia, char*);
void	iaConnect_nbr	(serveur* this, iaClients* ia, char*);

/* incantation */
bool	testForPlayer(serveur* this, iaClients* ia);
bool	testForRessource(serveur* this, iaClients* ia, int*);

#endif
