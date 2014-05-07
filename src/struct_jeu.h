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
    int tour;
    int nb_tigre;
    int nb_chevre;
    int joueur;
    tigres t;
}t_partie;

//structure representant l'�tat de la partie;
typedef t_partie * partie;

/*Structure repr�sentant un joueur
    - le score repr�sente, pour le joueur qui s'occupe des tigre, le nombre de chevre qu'il a prise
    - tandis que pour le joueur qui s'occupe des ch�vre c'est le nombre de tigre bloqu�
*/
typedef struct et_joueur{
    char nom[TAILLE_NOM];
    int role;
    int score;
}t_joueur;

typedef t_joueur * joueur;

/*structure repr�sentant le jeu
    - participant tableau des joueurs rang� de cette mani�re :
        - indice 0 : chevre
        - indice 1 : tigre
*/
typedef struct et_jeu {
    plateau p;
    joueur participant;
    partie g;
}t_jeu;

typedef t_jeu * jeu_s;


#endif
