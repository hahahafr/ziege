#include "jeu.h"

void init_jeu(jeu_s * j){
    *j = (jeu_s)malloc(sizeof(t_jeu));

    init_plateau(&((*j)->p));
    init_player(*j);
    init_partie(*j);
    init_tigres(*j);

}

void init_player(jeu_s j){

    int role;

    j->participant = (joueur)malloc(sizeof(t_joueur)*2);

    j->participant[CHEVRE].score = 0;
    j->participant[TIGRE].score = 0;

    do{
        printf("Joueur 1, quel est votre role ? ( 0 = chevre, 1 tigre)\n");
        scanf("%d",&role);
    }while(role !=1 && role != 0);

    /*affichage*/

    printf("Veuillez saisir le nom du joueur 1 :\n");
    scanf("%s",j->participant[role].nom);

    printf("Veuillez saisir le nom du joueur2 :\n");
    scanf("%s",j->participant[1-role].nom);

    j->participant[role].role = 1 - j->participant[1-role].role;
}

int jouer(jeu_s j){
    /*boucle infini qui fait jouer les joueurs tours par tours*/
    coup_s c;

    while(!is_end(j)){
        system("cls");

        printf("%s a vous de jouer !\n",j->participant[j->g->joueur].nom);

        c = saisi_action(j);
        if(traitement_action(j,c)){
            maj_plateau(j,c);
            maj_score(j);
            tour_suivant(j->g);
        }
        free(c);
        system("pause");
    }
    return(0);
}

bool is_end(jeu_s j){
    if(j->g->nb_chevre == 0 && tigre_immobile(j)  && j->g->phase == PHASE_DEPLACEMENT ){
        return(true);
    }
    return(false);
}

coup_s saisi_action(jeu_s j){
    coup_s c;

    c = (coup_s)malloc(sizeof(t_coup_s));

    c->type = j->g->joueur;

    // fabrication d'un coup manuel
    printf("Veuillez saisir l'ordonne source :\n");
    scanf("%d",&(c->source[ORD]));

    printf("Veuillez saisir l'abscisse source :\n");
    scanf("%d",&(c->source[ABS]));

    printf("Veuillez saisir l'ordonne destination :\n");
    scanf("%d",&(c->destination[ORD]));

    printf("Veuillez saisir l'abscisse destination :\n");
    scanf("%d",&(c->destination[ABS]));



    //fonction interface utilisateur de saisie de coup
    return(c);
}

bool traitement_action(jeu_s j, coup_s c){
    return(validite_coup(j,c));
}

int maj_plateau(jeu_s j, coup_s c){
    return(action_pion(j->p,c));
}

void maj_score(jeu_s j){
    int i;
    if( j->p->sup_pion[ORD] != -1 ){
        //chevre prise
        j->participant[TIGRE].score++;
        j->p->sup_pion[ORD] = j->p->sup_pion[ABS] = -1;
    }

        for(i=0;i<NB_MAX_TIGRE;i++){
            if(!test_deplacement_possible(j->p,j->g->t[i])){
                j->participant[CHEVRE].score++;
            }
        }
}

// fonction de test
void deplacement_tigre(jeu_s * j){
    coup_s c;

    *j = (jeu_s)malloc(sizeof(t_jeu));

    init_plateau(&((*j)->p));

    (*j)->participant = (joueur)malloc(sizeof(t_joueur)*2);

    (*j)->participant[CHEVRE].score = 0;
    (*j)->participant[TIGRE].score = 0;

    (*j)->p->grille[0][0].pion = TIGRE;

    (*j)->p->grille[1][1].pion = CHEVRE;

    (*j)->g = (partie)malloc(sizeof(t_partie));
    (*j)->g->joueur = TIGRE;

    while(true){

        c = (coup_s)malloc(sizeof(t_coup_s));

        c->type = TIGRE;

        //fabrication d'un coup manuel
        printf("Veuillez saisir l'ordonne source :\n");
        scanf("%d",&(c->source[ORD]));

        printf("Veuillez saisir l'abscisse source :\n");
        scanf("%d",&(c->source[ABS]));

        printf("Veuillez saisir l'ordonne destination :\n");
        scanf("%d",&(c->destination[ORD]));

        printf("Veuillez saisir l'abscisse destination :\n");
        scanf("%d",&(c->destination[ABS]));

        if(traitement_action(*j,c)){
            maj_plateau(*j,c);
            maj_score(*j);
            tour_suivant((*j)->g);
        }

        printf("score tigre : %d\n",(*j)->participant[TIGRE].score);
        printf("score chevre : %d \n",(*j)->participant[CHEVRE].score);
    }

}

void test_score(jeu_s * j){
    *j = (jeu_s)malloc(sizeof(t_jeu));

    init_plateau(&((*j)->p));
    init_partie(*j);
    init_tigres(*j);

    (*j)->participant = (joueur)malloc(sizeof(t_joueur)*2);

    (*j)->participant[CHEVRE].score = 0;
    (*j)->participant[TIGRE].score = 0;

    (*j)->p->grille[0][0].pion = TIGRE;

    (*j)->p->grille[1][1].pion = CHEVRE;
    (*j)->p->grille[2][2].pion = CHEVRE;

    (*j)->p->grille[0][1].pion = CHEVRE;
    (*j)->p->grille[0][2].pion = CHEVRE;

    (*j)->p->grille[1][0].pion = CHEVRE;
    (*j)->p->grille[2][0].pion = CHEVRE;

    maj_score(*j);

    printf("score tigre : %d\n",(*j)->participant[TIGRE].score);
    printf("score chevre : %d \n",(*j)->participant[CHEVRE].score);



}
