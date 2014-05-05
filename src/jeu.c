#include "jeu.h"

void init_jeu(jeu * j){
    *j = (jeu)malloc(sizeof(t_jeu));

    init_plateau(&((*j)->p));
    init_player(j);

}

void init_player(jeu j){

    j->participant = (joueur)malloc(sizeof(t_joueur)*2);

    j->participant[0].score = j->participant[1].score = 0;

    /*affichage*/
    printf("Veuillez saisir le nom du joueur 1 :\n");
    scanf("%s",j->participant[0].nom);

    printf("Veuillez saisir le nom du joueur2 :\n");
    scanf("%s",j->participant[1].nom);

    printf("Joueur 1, quel est votre role ? ( 0 = chevre, 1 tigre)\n");
    scanf("%d",&(j->participant[0].role));
    j->participant[0].role = 0;
    j->participant[1].role = 1 - j->participant[0].role;
}
