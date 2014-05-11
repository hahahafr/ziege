#include "partie.h"

void init_partie(partie * g){
    (*g) = (partie)malloc(sizeof(t_partie));

    (*g)->phase = PHASE_PLACEMENT;
    (*g)->nb_tigre = NB_MAX_TIGRE;
    (*g)->nb_chevre = 0;
    (*g)->tour = 0;
    (*g)->joueur = CHEVRE;

    (*g)->t = (tigres)malloc(sizeof(t_pion)*NB_MAX_TIGRE);

    (*g)->c = (chevres)malloc(sizeof(t_pion)*NB_MAX_CHEVRE);
}

void maj_partie(partie g,coup_s c,int sup_pion[]){

    int i=0;

    /*cas ou le deplacement du tigre implique la capture d'un chevre -> mise à jour du tableau des chevres*/
    if( c->type == TIGRE && sup_pion[ORD] != VIDE ){

        while( ! ( sup_pion[ORD] == g->c[i].position[ORD] && sup_pion[ABS] == g->c[i].position[ABS] ) && i < CHEVRE )
            i++;

        if( i >= NB_MAX_CHEVRE )
            return;

        g->c[i].position[ORD] = VIDE;
        g->c[i].position[ABS] = VIDE;
    }

    i=0;

    /*mise à jour de la position des pions dans leur liste respective*/
    if( c->type == TIGRE ){

        while( ! ( c->source[ORD] == g->t[i].position[ORD] &&  c->source[ABS] == g->t[i].position[ABS] ) && i < NB_MAX_TIGRE )
            i++;

        if( i >= NB_MAX_TIGRE )
            return;

        g->t[i].position[ORD] = c->destination[ORD];
        g->t[i].position[ABS] = c->destination[ABS];
    }

    if( c->type == CHEVRE ){
        while( ! ( c->source[ORD] == g->c[i].position[ORD] &&  c->source[ABS] == g->c[i].position[ABS] ) && i < NB_MAX_CHEVRE )
            i++;

        g->c[i].position[ORD] = c->destination[ORD];
        g->c[i].position[ABS] = c->destination[ABS];


        if(c->source[ORD] == VIDE){
            g->nb_chevre++;
        }


    }
    tour_suivant(g);
}

void tour_suivant(partie g){

    g->joueur = (g->joueur +1)% 2 ;
    g->tour++;

    if(NB_MAX_CHEVRE == g->nb_chevre){
        g->phase =  PHASE_DEPLACEMENT;
    }
}

int get_parti_joueur(partie p){
    return(p->joueur);
}

int get_parti_phase(partie p){
    return(p->phase);
}
