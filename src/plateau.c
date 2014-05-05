#include "plateau.h"

void init_plateau(plateau * p){
    *p = (plateau)malloc(sizeof(t_plateau));

    for(int i=0;i<PLATEAU_HAUTEUR;i++){
        for(int j=0;j<PLATEAU_LARGEUR;j++){
            (*p)->grille[i][j].pion = VIDE;
        }
    }
}

int ajouter_pion(plateau p,coups c){

}
