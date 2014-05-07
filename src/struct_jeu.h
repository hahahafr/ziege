#ifndef STRUCT_JEU
#define STRUCT_JEU

#include "plateau.h"


typedef struct et_tab_tigre {
    int position[2];
}t_tigre;

//Tableaux des positions des tigres
typedef t_tigre * tigres;

typedef struct et_partie {
    int phase;
    int nb_tigre;
    int nb_chevre;
    int joueur;
    tigres t;
}t_partie;

//structure representant l'état de la partie;
typedef t_partie * partie;

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
}t_jeu;

typedef t_jeu * jeu_s;


#endif
