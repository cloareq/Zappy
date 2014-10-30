#include <string.h>

#include "serveur.h"
#include "monitor.h"

void	iaAvance	(serveur* this, iaClients* ia, char* i) {
  (void) i;
  ia->_p.x +=
    (ia->_o == gauche) ? (+1) :
    (ia->_o == droite) ? (-1) :
    (0);
  ia->_p.y +=
    (ia->_o == haut) ? (-1) :
    (ia->_o == bas) ? (+1) :
    (0);
  if (ia->_p.y < 0)
    ia->_p.y = this->size.y - 1;
  if (ia->_p.x < 0)
    ia->_p.x = this->size.x - 1;
  if (ia->_p.y >= this->size.y)
    ia->_p.y = 0;
  if (ia->_p.x >= this->size.x)
    ia->_p.x = 0;
  ia->pause = 7;
  pushNode(ia->wrBuffer, strdup("ok\n"));
  avertMonitor(this, mPositionPlayer(ia->num, ia->_p.x, ia->_p.y, ia->_o));
}

void	iaDroite	(serveur* this, iaClients* ia, char* i) {
  (void) this;
  (void) i;
  ia->_o += 1;
  if (ia->_o == maxOrientation)
    ia->_o = haut;
  ia->pause = 7;
  pushNode(ia->wrBuffer, strdup("ok\n"));
  avertMonitor(this, mPositionPlayer(ia->num, ia->_p.x, ia->_p.y, ia->_o));
}

void	iaGauche	(serveur* this, iaClients* ia, char* i) {
  (void) this;
  (void) i;
  ia->_o -= 1;
  if (ia->_o == minOrientation)
    ia->_o = droite;
  ia->pause = 7;
  pushNode(ia->wrBuffer, strdup("ok\n"));
  avertMonitor(this, mPositionPlayer(ia->num, ia->_p.x, ia->_p.y, ia->_o));
}
