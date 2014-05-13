#include "plateau.h"

void init_plateau(plateau * p){
    *p = (plateau)malloc(sizeof(t_plateau));

    for(int i=0;i<PLATEAU_HAUTEUR;i++){
        for(int j=0;j<PLATEAU_LARGEUR;j++){
            (*p)->grille[i][j].pion = VIDE;
        }
    }

    (*p)->sup_pion[ORD] = (*p)->sup_pion[ABS] =  VIDE;
}

int maj_plateau(plateau p,coup_s c){

    if(c->source[ORD] == VIDE && c->source[ABS] == VIDE){
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

int get_pion(plateau p, int ord,int abs){
    return(p->grille[ord][abs].pion);
}

int get_supp_pion_ord(plateau p){
    return(p->sup_pion[ORD]);
}

int get_supp_pion_abs(plateau p){
    return(p->sup_pion[ABS]);
}

void set_supp_pion_ord(plateau p,int ord){
    p->sup_pion[ORD] = ord;
}

void set_supp_pion_abs(plateau p,int abs){
    p->sup_pion[ABS] = abs;
}

