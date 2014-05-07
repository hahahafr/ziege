#include "partie.h"

void init_partie(partie * g){
    *g = (partie)malloc(sizeof(t_partie));

    (*g)->phase = PHASE_PLACEMENT;
    (*g)->nb_tigre = NB_MAX_TIGRE;
    (*g)->nb_chevre = 0;
    (*g)->joueur = CHEVRE;

}

void init_tigres(jeu_s j){

    //allocation du tableau de tigre
    j->g->t = (tigres)malloc(sizeof(t_tigre)*NB_MAX_TIGRE);

    j->g->t[0].position[ORD] = j->g->t[0].position[ABS] =  1;

    j->g->t[1].position[ORD] = 0;
    j->g->t[1].position[ABS] =  PLATEAU_LARGEUR;

    j->g->t[2].position[ORD] = PLATEAU_HAUTEUR;
    j->g->t[2].position[ABS] =  0;

    j->g->t[3].position[ORD] = j->g->t[3].position[ABS] =  PLATEAU_HAUTEUR;

    //mise en place des tigres
    for(int i=0;i<NB_MAX_TIGRE;i++)
        j->p->grille[j->g->t[i].position[ORD]][j->g->t[i].position[ABS]].pion = TIGRE;

}

void tour_suivant(partie g){
    g->joueur = (g->joueur +1)% 2 ;

    if(NB_MAX_CHEVRE == g->nb_chevre){
        g->phase =  PHASE_DEPLACEMENT;
    }
}
