#include "jeu.h"

void deplacement_tigre(jeu_s * j){
    coup_s c;

    *j = (jeu_s)malloc(sizeof(t_jeu));

    init_plateau(&((*j)->p));

    (*j)->participant = (joueur)malloc(sizeof(t_joueur)*2);

    (*j)->participant[CHEVRE].score = 0;
    (*j)->participant[TIGRE].score = 0;

    (*j)->p->grille[0][0].pion = TIGRE;

    (*j)->p->grille[1][1].pion = CHEVRE;

    (*j)->p->grille[2][2].pion = VIDE;

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
            maj_plateau((*j)->p,c);
            maj_score_tigre(*j);
        }

        printf("score tigre : %d\n",(*j)->participant[TIGRE].score);
        printf("score chevre : %d \n",(*j)->participant[CHEVRE].score);
    }

}

//int main()
//{
//    jeu_s j;
//    deplacement_tigre(&j);
//
//    return 0;
//}
