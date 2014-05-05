#ifndef PLATEAU_H
#define PLATEAU_H

#include <stdio.h>
#include <stdlib.h>

typedef struct et_case {
    int pion;
}t_case;

typedef struct et_plateau{
    t_case grille[PLATEAU_HAUTEUR][PLATEAU_LARGEUR];
}t_plateau;

typedef struct et_coups {
    int destination[2];
    int source[2];
    int type;
}t_coups;

typedef t_coups * coups;


typedef t_plateau * plateau;

void init_plateau(plateau * plateau);
int ajouter_pion(plateau p,coups c);
#endif
