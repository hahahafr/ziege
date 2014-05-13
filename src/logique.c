#include "logique.h"

int validite_coup(jeu_s j,coup_s c){

    if( !test_limite(c) ){
        return(1);
    }

    if( c->source[ORD] != -1 && c->source[ABS] != -1 && est_vide_source(j,c) ){
        return(2);
    }

    if( !est_vide_destination(j,c) ){
        return(3);
    }

    if(c->source[ORD] != -1 && c->source[ABS] != -1 && c->type != get_pion(j->p,c->source[ORD],c->source[ABS])){
        return(4);
    }

    if( c->source[ORD] == VIDE && c->type == TIGRE ){
        return(5);
    }

    if( test_immobile(c)){
        return(6);
    }

    if( c->type ==  TIGRE && !test_deplacement(c) && ! test_deplacement_tigre(j,c) ){
        return(7);
    }

    /*Phase de placement*/
    if( j->g->phase == PHASE_PLACEMENT ){
        if( c->source[ORD] != VIDE && c->type == CHEVRE ){
            return(8);
        }

        return(0);
    }

    /*Phase de deplacement*/
    if( c->type == CHEVRE && c->source[ORD] == VIDE ){
        return(9);
    }

    if( c->type == CHEVRE && !test_deplacement(c) ){
        return(10);
    }

    return(0);
}

bool test_immobile(coup_s c){
    return( c->destination[ORD] == c->source[ORD] && c->destination[ABS] == c->source[ABS] );
}

bool hors_limite(int ord,int abs){
    if(abs >= PLATEAU_LARGEUR || abs < 0)
        return(true);

    if(ord >= PLATEAU_HAUTEUR || ord < 0)
        return(true);

    return(false);

}

bool test_limite(coup_s c){

    if( c->source[ORD] != c->source[ABS] && ( c->source[ORD] == -1 || c->source[ABS] == -1 ) ){
        return(false);
    }

    if( c->source[ORD] < VIDE || c->source[ORD] > PLATEAU_HAUTEUR ){
        return(false);
    }

    if( c->source[ABS] < VIDE || c->source[ABS] > PLATEAU_LARGEUR ){
        return(false);
    }

    if( c->destination[ORD] < 0 || c->destination[ORD] > PLATEAU_HAUTEUR ){
        return(false);
    }

    if( c->destination[ABS] < 0 || c->destination[ABS] > PLATEAU_LARGEUR ){
        return(false);
    }

    return(true);
}

bool test_utilise_diagonale(coup_s c){
    // test pour savoir si le coup utilise les diagonales
    coup_s tmp;

    tmp = (coup_s)malloc(sizeof(t_coup_s));

    tmp->source[ORD] = tmp->source[ABS] = 0;
    tmp->destination[ORD] = c->destination[ORD] - c->source[ORD];
    tmp->destination[ABS] = c->destination[ABS] - c->source[ABS];

    if( (fabs(tmp->destination[ABS]) - fabs(tmp->destination[ORD] )) != 0){
        // il n'utilise pas les diagonales
        return(false);
    }

    return(true);
}

bool test_diagonale(coup_s c){
    // il utilise les diagonales
    // test pour savoir si les diagonale sont disponnibles

    if(!test_utilise_diagonale(c)){
        return(true);
    }

    if( c->source[ORD] % 2 == 0 &&  c->source[ABS] % 2 == 0 ){
        //ligne paire, faut que la colonne soit paire aussi
        return(true);
    }

    if( ( c->source[ORD] % 2 == 1 ) && ( c->source[ABS] %2 == 1 ) ){
        // si ligne impaire = colonne impaire
        return(true);
    }

    return(false);
}

bool test_deplacement(coup_s c){
/*test si ça correspond à un deplacement basique correct*/
    if( fabs(c->source[ORD] - c->destination[ORD]) > 1 || fabs(c->source[ABS] - c->destination[ABS]) > 1 ){
        return(false);
    }

    if( !test_diagonale(c) ){
        return(false);
    }

    return(true);
}

bool test_deplacement_tigre(jeu_s j, coup_s c){
/*test si ça correspon à un deplacement de tigre qui mange un chèvre
  ce deplacement est valide que si il y a une chèvre à manger*/

    if( fabs(c->source[ORD] - c->destination[ORD]) > 2 || fabs(c->source[ABS] - c->destination[ABS]) > 2 ){
        return(false);
    }

    if( test_utilise_diagonale(c) && !test_diagonale(c)){
        return(false);
    }

    if( !test_eat_chevre(j,c) ){
        return(false);
    }

    return(true);
}

bool test_eat_chevre(jeu_s j, coup_s c){
    int ord,abs;

    ord = ( c->destination[ORD] + c->source[ORD] ) /2;
    abs = ( c->destination[ABS] + c->source[ABS] ) /2;

    if( get_pion(j->p,ord,abs) !=CHEVRE){
        set_supp_pion_ord(j->p,-1);
        set_supp_pion_abs(j->p,-1);
        return(false);
    }

    set_supp_pion_ord(j->p,ord);
    set_supp_pion_abs(j->p,abs);

    return(true);
}

bool est_vide_destination(jeu_s j, coup_s c){
    return( get_pion(j->p,c->destination[ORD],c->destination[ABS]) == -1 );
}

bool est_vide_source(jeu_s j, coup_s c){
    return( get_pion(j->p,c->source[ORD],c->source[ABS]) == -1 );
}

bool tigre_immobile(coup_s c){
    // si le type du pion est chevre alors on ne s'en occupe on renvoi faux
    // si le type du pion est tigre alors il faut que il faut que que la source soit != -1 pour renvoyer
    // faux sinon c'est que tout les tigres sont bloqués
    return( ! ( c->type == TIGRE && c->source[ORD] != -1 || c->type == CHEVRE ) );
}

bool test_deplacement_possible(jeu_s je, t_pion t){
    int i,j,limit_ord,limit_abs;
    bool possible = false;

    i=t.position[ORD]-1;
    j=t.position[ABS]-1;

    limit_ord=i+3;
    limit_abs=j+3;

    coup_s c;

    c =(coup_s)malloc(sizeof(t_coup_s));

    c->source[ORD] = t.position[ORD];
    c->source[ABS] = t.position[ABS];

    while( i < limit_ord && possible == false ){
        if(i >= 0 && i < PLATEAU_HAUTEUR){

            j = t.position[ABS] - 1;

            while(j < limit_abs && possible == false){
                c->destination[ORD] = i;
                c->destination[ABS] = j;

                if(j >= 0 && j < PLATEAU_LARGEUR && get_pion(je->p,i,j) == VIDE && test_diagonale(c)){
                        possible = true;
                }

                j++;
            }
        }
        i++;
    }
    return(possible);
}

bool chevres_immobiles(jeu_s j){
    bool immo = true;
    int i=0;

    while(immo == true && i< j->g->nb_chevre){
        if(test_deplacement_possible(j, j->g->c[i]))
            immo = false;
       i++;
    }

    if( i >= j->g->nb_chevre ){
        return(immo);
    }

    return(false);

}
