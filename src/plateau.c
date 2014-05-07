#include "plateau.h"

void init_plateau(plateau * p){
    *p = (plateau)malloc(sizeof(t_plateau));

    for(int i=0;i<PLATEAU_HAUTEUR;i++){
        for(int j=0;j<PLATEAU_LARGEUR;j++){
            (*p)->grille[i][j].pion = VIDE;
        }
    }

    (*p)->sup_pion[ORD] = (*p)->sup_pion[ABS] = -1;
}

int action_pion(plateau p,coup_s c){

    printf("source : %d %d\n",c->source[ORD],c->source[ABS]);

    printf("destination : %d %d\n",c->destination[ORD],c->destination[ABS]);

    if(c->source[ORD] == VIDE && c->source[ABS] == -1){
        //placement de chevre
        p->grille[c->destination[ORD]][c->destination[ABS]].pion = c->type;
        return(0);
    }
    p->grille[c->destination[ORD]][c->destination[ABS]].pion = p->grille[c->source[ORD]][c->source[ABS]].pion;

    p->grille[c->source[ORD]][c->source[ABS]].pion = VIDE;

    if( p->sup_pion[ORD] != -1 ){
        p->grille[p->sup_pion[ORD]][p->sup_pion[ABS]].pion = -1;
    }
    return(0);

}

