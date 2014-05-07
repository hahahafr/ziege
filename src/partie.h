#ifndef PARTIE_H
#define PARTIE_H

#include "config.h"

typedef struct et_partie {
    int phase;
    int nb_tigre;
    int nb_chevre;
    int joueur;
}t_partie;

typedef t_partie * partie;

void init_partie(partie * g);
void tour_suivant(partie g);

#endif

