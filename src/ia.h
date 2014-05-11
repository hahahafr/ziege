#ifndef IA_H
#define IA_H

#include "jeu.h"
#include "config.h"
#include "logique.h"

/*
    schema d analyse des possibilite :
        * *
        * X
        *
            - X case analysée
            - * case testée pour le placement


    top placement chèvre :
                            - je protège une congénère = 2
                            - il n'y a pas de tigre = 1
                            - a la casserole = 0

    top placement tigre :
                            - manger = 1
                            - se deplacer aléatoirement = 0
*/

//typedef struct et_arbre {
//    struct et_arbre * tree[];
//}t_arbres;
//
//
//IA des chevres, version 2

coup_s choix_placement_chevre(jeu_s j);

coup_s choix_deplacement_chevre(jeu_s j);

int test_position_chevre(jeu_s j,coup_s c);

coup_s choix_deplacement_tigre(jeu_s j);

int test_position_tigre(jeu_s j,coup_s c);

#endif
