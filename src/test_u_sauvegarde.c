#include "jeu.h"
#include "sauvegarde.h"

void test_historique(jeu_s *j,sauvegarde * s){

    *j = (jeu_s)malloc(sizeof(t_jeu));

    init_plateau(&((*j)->p));
    init_partie(&((*j)->g));

    init_tigres(*j);
    init_sauvegarde(*s);

    (*j)->participant = (joueur)malloc(sizeof(t_joueur)*2);

    (*j)->participant[CHEVRE].score = 0;
    (*j)->participant[TIGRE].score = 10;

    (*j)->p->grille[0][0].pion = TIGRE;

    (*j)->p->grille[1][1].pion = CHEVRE;
    (*j)->p->grille[2][2].pion = CHEVRE;

    (*j)->p->grille[0][1].pion = CHEVRE;
    (*j)->p->grille[0][2].pion = CHEVRE;

    (*j)->p->grille[1][0].pion = CHEVRE;
    (*j)->p->grille[2][0].pion = CHEVRE;

    maj_score(*j);

    ajout_historique(*j,*s);

    printf("Destruction du jeu (par un free sur le pointeur du jeu)\n");

    free(*j);

    *j = revenir_arriere(*j,*s);

    printf("case 0 0 : %d\n",(*j)->p->grille[0][0].pion);
    printf("case 1 1 : %d\n",(*j)->p->grille[1][1].pion);

    printf("score des tigres : %d\n",(*j)->participant[TIGRE].score);

}

void test_fichier(jeu_s * j,sauvegarde *s){
    *j = (jeu_s)malloc(sizeof(t_jeu));

    init_plateau(&((*j)->p));
    init_partie(&((*j)->g));

    init_tigres(*j);
    init_sauvegarde(s);

    (*j)->participant = (joueur)malloc(sizeof(t_joueur)*2);

    (*j)->participant[CHEVRE].score = 0;
    (*j)->participant[TIGRE].score = 10;

    (*j)->p->grille[0][0].pion = TIGRE;

    (*j)->p->grille[1][1].pion = CHEVRE;
    (*j)->p->grille[2][2].pion = CHEVRE;

    (*j)->p->grille[0][1].pion = CHEVRE;
    (*j)->p->grille[0][2].pion = CHEVRE;

    (*j)->p->grille[1][0].pion = CHEVRE;
    (*j)->p->grille[2][0].pion = CHEVRE;

    maj_score(*j);

    sauvegarde_fichier(*j,*s);

    printf("Sauvegarde effectuee !\n");

    printf("Reset du jeu\n");

    free(*j);

    *j = (jeu_s)malloc(sizeof(t_jeu));

    init_sauvegarde(*s);
    init_plateau(&((*j)->p));

    (*j)->participant = (joueur)malloc(sizeof(t_joueur)*2);

    if( chargement_fichier(*j,*s) == -1 ){
        printf("Erreur pendant le chargement, il se peut que la sauvegarde soit corrompu!\n");
        return;
    }else
        printf("Chargement effectuee !\n");

    printf("Affichage de la case 0 0 :\n");
    printf("%d\n",(*j)->p->grille[0][0]);

    printf("Affichage de la case 1 1 :\n");
    printf("%d\n",(*j)->p->grille[1][1]);

    printf("Affichage du score de tigre:\n");
    printf("%d\n",(*j)->participant[TIGRE].score);
}

//int main(){
//
//    jeu_s j;
//    sauvegarde s;
//
//    printf("Test des la gestion de fichier :\n\n");
//
//    test_fichier(&j,&s);
//
//    system("pause");
//    system("cls");
//
//    printf("Test des la gestion de L'historique :\n\n");
//
//    test_historique(&j,&s);
//
//    return(0);
//}
