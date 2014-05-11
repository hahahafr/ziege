#include "jeu.h"

void init_jeu(jeu_s * j){
    *j = (jeu_s)malloc(sizeof(t_jeu));

    init_plateau(&((*j)->p));
    init_partie(&((*j)->g));
    init_tigres(*j);
    init_chevres(*j);

}

void init_chevres(jeu_s j){
    for(int i=0;i<NB_MAX_CHEVRE;i++)
        j->g->c[i].position[ORD] = j->g->c[i].position[ABS] = -1;
}

void init_tigres(jeu_s j){

    j->g->t[0].position[ORD] = 0;
    j->g->t[0].position[ABS] = 0;

    j->g->t[1].position[ORD] = 0;
    j->g->t[1].position[ABS] = PLATEAU_LARGEUR-1;

    j->g->t[2].position[ORD] = PLATEAU_HAUTEUR-1;
    j->g->t[2].position[ABS] = 0;

    j->g->t[3].position[ORD] = PLATEAU_HAUTEUR-1;
    j->g->t[3].position[ABS] = PLATEAU_LARGEUR-1;

//    //mise en place des tigres
    for(int i=0;i<NB_MAX_TIGRE;i++)
        j->p->grille[j->g->t[i].position[ORD]][j->g->t[i].position[ABS]].pion = TIGRE;
}

void init_player(jeu_s j, int rj1){

    int role = rj1;

    j->participant = (joueur)malloc(sizeof(t_joueur)*2);

    j->participant[CHEVRE].score = 0;
    j->participant[TIGRE].score = 0;

    j->participant[role].role = role;
    j->participant[1-role].role = 1 - j->participant[role].role;
}

int jouer(jeu_s j,coup_s c){
    /*boucle infini qui fait jouer les joueurs tours par tours*/

    int res = 0;

    res = traitement_action(j,c);

    if( res == 0 ){
        maj_jeu(j,c);
        return(0);
    }else{
        printf("%s\n",error[0]);
    }

    return(res);
}

bool is_end(jeu_s j){
    if( j->participant[TIGRE].score == 7 ){
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

void maj_jeu(jeu_s j,coup_s c){
        maj_plateau(j->p,c);
        maj_partie(j->g,c,j->p->sup_pion);
        maj_score(j);
}

void maj_score(jeu_s j){
    maj_score_chevre(j);
    maj_score_tigre(j);
}

void maj_score_chevre(jeu_s j){
    j->participant[CHEVRE].score = 0;

    for(int i=0;i<NB_MAX_TIGRE;i++){
        if(!test_deplacement_possible(j,j->g->t[i])){
            j->participant[CHEVRE].score++;
        }
    }
}

void maj_score_tigre(jeu_s j){
    if( j->p->sup_pion[ORD] != -1 ){
        //chevre prise
        j->participant[TIGRE].score++;

        j->p->sup_pion[ORD] = j->p->sup_pion[ABS] = -1;
    }

}

int get_phase(jeu_s j){
    return(get_parti_phase(j->g));
}

int get_joueur(jeu_s j){
    return(get_parti_joueur(j->g));
}
