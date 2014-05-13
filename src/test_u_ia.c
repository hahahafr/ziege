#include "test_u_ia.h"

void test_ia_chevre(jeu_s * j){
    coup_s c;
    int sup_pion[] = {-1,-1};
    *j = (jeu_s)malloc(sizeof(t_jeu));

    init_plateau(&((*j)->p));
    init_partie(&((*j)->g));
    init_tigres(*j);

    for(int i=0;i<1;i++){

        c = choix_placement_chevre(*j);

        maj_plateau((*j)->p,c);
        maj_partie((*j)->g,c,sup_pion);

        printf("coordonne  :%d %d\n",c->destination[ORD],c->destination[ABS]);
    }

    printf("\nNB chevre placees : %d\n",(*j)->g->nb_chevre);
    printf("\nscore tigre : %d\n",(*j)->g->nb_tigre);
    printf("case 3 3  -> %d\n",(*j)->p->grille[3][3].pion);

    free(c);
}

void test_ia_tigre(jeu_s j,sauvegarde s){
    coup_s c;

    maj_score_chevre(j);
    maj_score_tigre(j);

    printf("info : chevre en 1 1\n");
    printf("\ninfo : chevre en 3 3\n");

    j->p->grille[1][1].pion = CHEVRE;
    j->p->grille[3][3].pion = CHEVRE;
    j->p->grille[3][4].pion = CHEVRE;
    j->p->grille[4][2].pion = CHEVRE;
    j->p->grille[0][4].pion = CHEVRE;

    while(j ->participant[TIGRE].score != 5 ){
        c = choix_deplacement_tigre(j);

        printf("Coup : %d %d || %d %d\n",c->source[ORD],c->source[ABS],c->destination[ORD],c->destination[ABS]);

        test_eat_chevre(j,c);

        maj_plateau(j->p,c);
        maj_partie(j->g,c,j->p->sup_pion);
        sauvegarde_fichier(j,s);
        maj_score(j);

    }
}

void test_choix_deplacement_chevre(jeu_s * j){
    coup_s c;
    int sup_pion[] = {-1,-1};

    *j = (jeu_s)malloc(sizeof(t_jeu));

    init_plateau(&((*j)->p));
    init_partie(&((*j)->g));
    init_tigres(*j);
    init_chevres(*j);

    c = (coup_s)malloc(sizeof(t_coup_s));

    c->type = CHEVRE;
    c->source[ORD] = -1;
    c->source[ABS] = -1;

    c->destination[ORD] = 0;
    c->destination[ABS] = 1;

    printf("Tigres initialis�s au 4 coins\n");

    printf("chevre en 0 1  :%d %d\n",c->destination[ORD],c->destination[ABS]);

    maj_plateau((*j)->p,c);
    maj_partie((*j)->g,c,sup_pion);

    c = choix_deplacement_chevre(*j,c);


    printf("\ncoordonne  :%d %d\n",c->destination[ORD],c->destination[ABS]);
}


void test_coordonnee(){
    //coordonn�e et oppos�
    int ord = 2;
    int abs = 1;

    int p_ord = 2;
    int p_abs = 2;

    int op_ord;
    int op_abs;

    int limit_abs = 3;
    int limit_ord = 3;

    op_ord = p_ord + (p_ord - ord);
    op_abs = p_abs + (p_abs - abs);

    printf("Coordonne : %d %d\n",ord,abs);
    printf("Opposee : %d %d\n",op_ord,op_abs);

}
