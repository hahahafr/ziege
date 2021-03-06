#ifndef UI_MODULE
#define UI_MODULE

#include <ncurses.h>
#include <string.h>

#include "main.h"
#include "struct_jeu.h"
#include "jeu.h"

#define TIGRE_CH 'T'
#define CHEVRE_CH 'C'
#define VIDE_CH ' '

#define TAILLE_ETAT_L 40
#define TAILLE_CIM_L 40

// la hauteur de 1 caractère est la même que la longeur de 2 caractères
#define TAILLE_PLATEAU_H (((PLATEAU_HAUTEUR+(PLATEAU_HAUTEUR-1))*3)+2) // 27+2=29
#define TAILLE_PLATEAU_L (((PLATEAU_LARGEUR+(PLATEAU_LARGEUR-1))*5)+4) // 47+4=49

typedef struct et_affichage_s {
    int plateau_orig_x;
    int plateau_orig_y;
    WINDOW *plateau;
    WINDOW *etat;
    WINDOW *cimetiere;
    WINDOW *message;
    int* tabindcoord[PLATEAU_HAUTEUR][PLATEAU_LARGEUR];
} t_affichage_s;

typedef t_affichage_s * aff_s;

void
init_affichage(jeu_s jeu, aff_s * aff);

void
maj_affichage(jeu_s jeu, aff_s aff);

void
retracer_case(aff_s aff, int y, int x, int p);

int
return_ch_plateau(int y, int x);

/* 
   in: y, x
  out: x, y
*/
int
coord_aff_vers_jeu(aff_s aff, int iny, int inx, int *outx, int *outy);

/* 
   in: x, y
  out: y, x
*/
void
coord_jeu_vers_aff(aff_s aff, int inx, int iny, int *outy, int *outx);

coup_s
saisir_coups(jeu_s jeu, aff_s aff);

#endif