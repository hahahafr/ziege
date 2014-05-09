#ifndef STRUCT_JEU
#define STRUCT_JEU

#include "config.h"
#include "plateau.h"
#include "partie.h"

/*Structure représentant un joueur
    - le score représente, pour le joueur qui s'occupe des tigre, le nombre de chevre qu'il a prise
    - tandis que pour le joueur qui s'occupe des chèvre c'est le nombre de tigre bloqué
*/
typedef struct et_joueur{
    char nom[TAILLE_NOM];
    int role;
    int score;
}t_joueur;

typedef t_joueur * joueur;

/*structure représentant le jeu
    - participant tableau des joueurs rangé de cette manière :
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
