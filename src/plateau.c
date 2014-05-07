#include "plateau.h"

void init_plateau(plateau * p){
    *p = (plateau)malloc(sizeof(t_plateau));

    for(int i=0;i<PLATEAU_HAUTEUR;i++){
        for(int j=0;j<PLATEAU_LARGEUR;j++){
            (*p)->grille[i][j].pion = VIDE;
        }
    }
}

int action_pion(plateau p,coup_s c){
    p->grille[c->destination[ORD]][c->destination[ABS]].pion = p->grille[c->source[ORD]][c->source[ABS]].pion;
    return(0);

}

