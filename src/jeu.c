#include "jeu.h"

void init_jeu(jeu_s * j){
    *j = (jeu_s)malloc(sizeof(t_jeu));

    init_plateau(&((*j)->p));
    init_player(*j);
    init_partie(&((*j)->g));
    init_tigres(*j);

}

void init_player(jeu_s j){

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

int jouer(jeu_s j){
    /*boucle infini qui fait jouer les joueurs tours par tours*/
    coup_s c;
    while(is_end(j)){
        c = saisi_action(j);
        if(traitement_action(j,c)){
            maj_plateau(j,c);
            tour_suivant(j->g);
        }

    }
    return(0);
}

bool is_end(jeu_s j){
    if(j->g->nb_chevre == 0 && tigre_immobile(j)){
        return(true);
    }
    return(false);
}

coup_s saisi_action(jeu_s j){
    coup_s c;

    c = (coup_s)malloc(sizeof(t_coup_s));

    //fonction interface utilisateur de saisie de coup
    return(c);
}

bool traitement_action(jeu_s j, coup_s c){
    return(validite_coup(j,c));
}

int maj_plateau(jeu_s j, coup_s c){
    return(action_pion(j,c));
}
