/******************************************************************/
/*
*MODULE DE PLATEAU
*/
/******************************************************************/
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

typedef t_plateau * plateau;

void init_plateau(plateau * plateau);

/*
Fonction qui permert d'interagir avec les element sur le plateau
retourne :
    - 0, tout vas bien
    - -1 , Erreur
*/

/*Mis à jour du plateau en conséquence du coup joué*/
int maj_plateau(plateau p,coup_s c);

/*Retour la valeur du pion présent à la source du coup*/
int get_pion(plateau p, int ord,int abs);

int get_supp_pion_ord(plateau p);

int get_supp_pion_abs(plateau p);

void set_supp_pion_ord(plateau p,int ord);

void set_supp_pion_abs(plateau p,int abs);

#endif
