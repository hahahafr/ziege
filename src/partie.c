#include "partie.h"

void init_partie(jeu_s j){
    j->g = (partie)malloc(sizeof(t_partie));

    j->g->phase = PHASE_PLACEMENT;
    j->g->nb_tigre = NB_MAX_TIGRE;
    j->g->nb_chevre = 0;
    j->g->tour = 0;
    j->g->joueur = CHEVRE;

    j->g->t = (tigres)malloc(sizeof(t_tigre)*NB_MAX_TIGRE);
}

void init_tigres(jeu_s j){

    //allocation du tableau de tigre
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
//        printf("%d %d\n",j->g->t[i].position[ORD],j->g->t[i].position[ABS]);
        j->p->grille[j->g->t[i].position[ORD]][j->g->t[i].position[ABS]].pion = TIGRE;
}

void tour_suivant(partie g){
    g->joueur = (g->joueur +1)% 2 ;
    g->tour++;

    if(NB_MAX_CHEVRE == g->nb_chevre){
        g->phase =  PHASE_DEPLACEMENT;
    }
}
