#include "jeu.h"
#include "sauvegarde.h"

void test_ia(jeu_s j,sauvegarde s){

    coup_s c;
    int erreur = 0;

    maj_score_chevre(j);
    maj_score_tigre(j);

    while(!is_end(j,c) && erreur == 0 && j->g->nb_chevre < NB_MAX_CHEVRE ){
        if( get_joueur(j) == 0 )
            c = choix_placement_chevre(j);
        else
            c = choix_deplacement_tigre(j);

        printf("PHASE : %d , nombre de chevre %d\n",j->g->phase,j->g->nb_chevre);
        printf("C'est le tour de : %d\n",get_joueur(j));
        printf("Coup : %d %d || %d %d\n",c->source[ORD],c->source[ABS],c->destination[ORD],c->destination[ABS]);
        erreur = jouer(j,c);
        printf("score chevre %d || score tigre = %d\n\n",j->participant[CHEVRE].score,j->participant[TIGRE].score);

        sauvegarde_fichier(j,s);

    }

    system("pause");

    printf("Et le gagnant est : %d\n",get_gagnant(j));

}
