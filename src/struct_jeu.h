#ifndef STRUCT_JEU
#define STRUCT_JEU

#include "plateau.h"
#include "partie.h"

typedef struct et_joueur{
    char nom[TAILLE_NOM];
    int role;
    int score;
}t_joueur;

typedef t_joueur * joueur;

typedef struct et_jeu {
    plateau p;
    joueur participant;
    partie g;
    int prochain_joueur;
}t_jeu;

typedef t_jeu * jeu_s;

#endif
