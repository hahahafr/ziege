/******************************************************************/
/*
*MODULE DE PARTIE
*/
/******************************************************************/

#ifndef PARTIE_H
#define PARTIE_H

#include "config.h"

typedef struct et_pion {
    int position[2];
}t_pion;

//Tableaux des positions des tigres
typedef t_pion * tigres;

typedef t_pion * chevres;

/* Structure représentant la partie
    - nbchèvre = nombre de chèvre total placé sur le plateau
    - tigres t = tableau des tigres sur le terain
    - chevres c = tableau des chevres sur le terrain
*/
typedef struct et_partie {
    int phase;
    int tour;
    int nb_tigre;
    int nb_chevre;
    int joueur;
    tigres t;
    chevres c;
}t_partie;

typedef t_partie * partie;

//initialise la partie
void init_partie(partie * g);

void tour_suivant(partie g);

void maj_partie(partie g,coup_s c,int sup_pion[]);

#endif

