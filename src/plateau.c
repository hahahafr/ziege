#include "plateau.h"

void init_plateau(plateau * p){
    *p = (plateau)malloc(sizeof(t_plateau));

    for(int i=0;i<PLATEAU_HAUTEUR;i++){
        for(int j=0;j<PLATEAU_LARGEUR;j++){
            (*p)->grille[i][j].pion = VIDE;
        }
    }

    /*positionnement des tigres*/
    (*p)->grille[0][0].pion = TIGRE;
    (*p)->grille[0][PLATEAU_LARGEUR].pion = TIGRE;
    (*p)->grille[PLATEAU_HAUTEUR][0].pion = TIGRE;
    (*p)->grille[PLATEAU_HAUTEUR][PLATEAU_LARGEUR].pion = TIGRE;

}

int action_pion(plateau p,coup_s c){
    if(c->type == -1){
        /*Cas d'un placement*/
        if(p->grille[c->destination[ORD]][c->destination[ABS]].pion =! -1){
            /*Cas d'une case deja occupé*/
            return(-1);
        }
        p->grille[c->destination[ORD]][c->destination[ABS]].pion = c->type;
        return(0);
    }

    /*Cas d'un déplacement*/
    if(p->grille[c->destination[ORD]][c->destination[ABS]].pion == -1){
        /*Cas d'une case vide = deplacement impossible*/
        return(-2);
    }
    p->grille[c->destination[ORD]][c->destination[ABS]].pion = p->grille[c->source[ORD]][c->source[ABS]].pion;
    return(0);

}

