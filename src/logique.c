#include "logique.h"

bool validite_coup(jeu_s j,coup_s c){
    if( !test_limite(c) ){
        printf("Coup hors limite !\n");
        return(false);
    }

    if( c->source[ORD] != -1 && c->source[ABS] != -1 && est_vide_source(j,c) ){
        printf("Erreur, deplacement d'une case vide!\n");
        return(false);
    }

    if( !est_vide_destination(j,c) ){
        printf("Case prise!\n");
        return(false);
    }

    if(c->source[ORD] != -1 && c->source[ABS] != -1 && c->type != get_pion(j->p,c->source[ORD],c->source[ABS])){
        printf("Deplacement des pions d'un adversaire, incorrect!(tricheur)\n");
        return(false);
    }

    if( c->source[ORD] == VIDE && c->type == TIGRE ){
        printf("On ne peut pas placer plus de tigre!\n");
        return(false);
    }

    if( test_immobile(c)){
        printf("Deplacement incorrect!\n");
        return(false);
    }

    if( c->type ==  TIGRE && !test_deplacement(c) && ! test_deplacement_tigre(j,c) ){
        printf("Deplacement de tigre incorrect!\n");
        return(false);
    }

    /*Phase de placement*/
    if( j->g->phase == PHASE_PLACEMENT ){
        if( c->source[ORD] != VIDE && c->type == CHEVRE ){
            printf("Deplacement des chevres impossible tant qu'elles ne sont pas toute pos�es!\n");
            return(false);
        }

        return(true);
    }

    /*Phase de deplacement*/
    if( c->type == CHEVRE && c->source[ORD] == VIDE ){
        printf("Toute les chevres sont pos�es!\n");
        return(false);
    }

    if( c->type == CHEVRE && !test_deplacement(c) ){
        printf("Deplacement de chevre incorect!\n");
        return(false);
    }

    return(true);
}

bool test_immobile(coup_s c){
    return( c->destination[ORD] == c->source[ORD] && c->destination[ABS] == c->source[ABS] );
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

bool test_diagonale(coup_s c){
    // test pour savoir si le coup utilise les diagonales
    coup_s tmp;

    tmp = (coup_s)malloc(sizeof(t_coup_s));

    tmp->source[ORD] = tmp->source[ABS] = 0;
    tmp->destination[ORD] = c->destination[ORD] - c->source[ORD];
    tmp->destination[ABS] = c->destination[ABS] - c->source[ABS];

    if( (fabs(tmp->destination[ABS]) - fabs(tmp->destination[ORD] )) != 0){
        // il n'utilise pas les diagonales
        return(true);
    }
    // il utilise les diagonales
    // test pour savoir si les diagonale sont disponnibles
    if( c->destination[ORD] % 2 == 0 ){
        //ligne paire, faut que la colonne soit paire aussi
        return( c->destination[ABS] % 2 == 0 );
    }

    if( c->destination[ORD] % 2 == 1 ){
        //ligne impaire = colonne impaire
        return( c->destination[ABS] % 2 == 1 );
    }

    return(false);
}

bool test_deplacement(coup_s c){
/*test si �a correspond � un deplacement basique correct*/
    if( fabs(c->source[ORD] - c->destination[ORD]) > 1 || fabs(c->source[ABS] - c->destination[ABS]) > 1 ){
        return(false);
    }

    if( !test_diagonale(c) ){
        return(false);
    }

    return(true);
}

bool test_deplacement_tigre(jeu_s j, coup_s c){
/*test si �a correspon � un deplacement de tigre qui mange un ch�vre
  ce deplacement est valide que si il y a une ch�vre � manger
*/
    if( fabs(c->source[ORD] - c->destination[ORD]) > 2 || fabs(c->source[ABS] - c->destination[ABS]) > 2 ){
        return(false);
    }

    if(!test_diagonale(c) ){
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

bool tigre_immobile(jeu_s je){
    bool immo = true;
    int i=0;
    while(immo == true && i<NB_MAX_TIGRE){
        if(test_deplacement_possible(je, je->g->t[i]))
            immo = false;
       i++;
    }

    return(immo);
}

bool test_deplacement_possible(jeu_s je, t_pion t){
    int i,j,limit_ord,limit_abs;
    bool possible = false;

    i=t.position[ORD]-1;
    j=t.position[ABS]-1;

    limit_ord=i+3;
    limit_abs=j+3;

    while( i < limit_ord && possible == false ){
        if(i >= 0 && i < PLATEAU_HAUTEUR){

            j = t.position[ABS] - 1;

            while(j < limit_abs && possible == false){

                if(j >= 0 && j < PLATEAU_LARGEUR && get_pion(je->p,i,j) == VIDE){
                    possible = true;
                }

                if(possible == false){
                    j++;
                }
            }
        }
        if(possible == false)
            i++;
    }
    return(possible);
}

bool chevres_immobiles(jeu_s j){
    bool immo = true;
    int i=0;

    while(immo == true && i<NB_MAX_CHEVRE){
        if(test_deplacement_possible(j, j->g->c[i]))
            immo = false;
       i++;
    }

    return(immo);
}
