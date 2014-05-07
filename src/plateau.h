#ifndef PLATEAU_H
#define PLATEAU_H

#include "config.h"

typedef struct et_case {
    int pion;
}t_case;

/*Structure représentant le plateau
sup_pion est un champs qui prend la position d'un pion affecté par le déplacement d'un autre pions
    - par defaut sup_pion[0] = sup_pion[1] = VIDE
*/
typedef struct et_plateau{
    t_case grille[PLATEAU_HAUTEUR][PLATEAU_LARGEUR];
    int sup_pion[2];
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
