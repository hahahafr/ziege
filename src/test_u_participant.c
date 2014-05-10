#include "jeu.h"

void test_score(jeu_s * j){
    *j = (jeu_s)malloc(sizeof(t_jeu));

    init_plateau(&((*j)->p));
    init_partie(&((*j)->g));
    init_tigres(*j);
    init_chevres(*j);

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

    printf("Resultats :\n");

    printf("score tigre : %d\n",(*j)->participant[TIGRE].score);
    printf("score chevre : %d \n",(*j)->participant[CHEVRE].score);

    printf("Resultats (apres avoir bouger une chevre) :\n");

    (*j)->p->grille[0][1].pion = VIDE;

    maj_score(*j);

    printf("Resultats :\n");

    printf("score tigre : %d\n",(*j)->participant[TIGRE].score);
    printf("score chevre : %d \n",(*j)->participant[CHEVRE].score);
}
//
//int main()
//{
//    jeu_s j;
//
//    test_score(&j);
//
//    return 0;
//}
//
