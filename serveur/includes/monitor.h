#ifndef __MONITOR_H__
# define __MONITOR_H__

typedef struct s_serveur serveur;
typedef struct s_clients clients;
void	avertMonitor	(serveur*, char*, ... );
void	avertThisMonitor(clients*, char*, ... );

void	calcCmd			(serveur*, clients*, char*);
void	avertMonitorByCmd	(serveur*, char*);


# define mSizeMap(x, y) "msz %d %d\n", x, y
# define mCaseMap(x, y, nourriture, i1, i2, i3, i4, i5, i6) "bct %d %d %d %d %d %d %d %d %d\n", x, y, nourriture, i1, i2, i3, i4, i5, i6
# define mNameTeam(s) "tna %s\n", s
# define mNewPlayer(n, x, y, orientation, lvl, team) "pnw %d %d %d %d %d %s", n, x, y, orientation + 1, lvl, team
# define mNewPlayerendl(n, x, y, orientation, lvl, team) "pnw %d %d %d %d %d %s\n", n, x, y, orientation + 1, lvl, team
# define mConnectEgg(e) "ebo %d\n", e
# define mPopEgg(n) "eht %d\n", n
# define mLvlPlayer(n, lvl) "plv %d %d\n", n, lvl
# define mStashPlayer(n, x, y, nourriture, i1, i2, i3, i4, i5, i6) "pin %d %d %d %d %d %d %d %d %d\n", n, x, y, nourriture, i1, i2, i3, i4, i5, i6
# define mBroadcastPlayer(n, m) "pbc %d, %s", n, m
# define mExpulsePlayer(n) "pex %d\n", n
# define mPosePlayer(n, r) "pdr %d %d\n", n, r
# define mPrendPlayer(n, r) "pgt %d %d\n", n, r
# define mIncantEPlayer(x, y) "pie %d %d 0\n", x, y
# define mIncantSPlayer(x, y) "pie %d %d 1\n", x, y
# define mPositionPlayer(n ,x, y, o) "ppo %d %d %d %d\n", n, x, y, (o) + 1
# define mBegFork(n) "pfk %d\n", n
# define mEndFork(e, n, x, y) "enw %d %d %d %d\n", e, n, x, y

# define cmdTeam "tna\n"
# define cmdMap "mct\n"
# define cmdMapSize "msz\n"

void	avertCase		(serveur*, clients*, char*);
void	avertMap		(serveur*, clients*);
void	avertTeam		(serveur*, clients*);
void	avertPlayerPosition	(serveur*, clients*, char*);
void	avertPlayerLevel	(serveur*, clients*, char*);
void	avertPlayerInventaire	(serveur*, clients*, char*);

#endif
