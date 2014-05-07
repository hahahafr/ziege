#ifndef PLATEAU_H
#define PLATEAU_H

#include "config.h"

typedef struct et_case {
    int pion;
}t_case;

typedef struct et_plateau{
    t_case grille[PLATEAU_HAUTEUR][PLATEAU_LARGEUR];
}t_plateau;

/*destination 1 -> abs , destination 0 ->ord*/
typedef struct et_coup_s {
    int destination[2];
    int source[2];
    int type;
}t_coup_s;

typedef t_coup_s * coup_s;


typedef t_plateau * plateau;

void init_plateau(plateau * plateau);

/*
Fonction qui permert d'interagir avec les element sur le plateau
retourne :
    - 0, tout vas bien
    - -1 , Erreur
*/
int action_pion(plateau p,coup_s c);

#endif
