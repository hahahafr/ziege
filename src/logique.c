#include "logique.h"

bool validite_coup(jeu_s j,coup_s c){

    if(j->g->joueur != c->type){
        printf("Vous avez essaye de deplace un pion de l equipe adverse!\n");
        return(false);
    }

    if( !test_limite(c) ){
        printf("Coup hors limite !\n");
        return(false);
    }

    if( c->source[ORD] == VIDE && c->type == TIGRE ){
        printf("On ne peut pas placer plus de tigre!\n");
        return(false);
    }

    if( !est_vide(j->p,c) ){
        printf("Case déjà utilisee!\n");
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
            printf("Deplacement des chevres impossible tant qu'elles ne sont pas toute posées!\n");
            return(false);
        }

        return(true);
    }

    /*Phase de deplacement*/
    if( c->type == CHEVRE && c->source[ORD] == VIDE ){
        printf("Toute les chevres sont posées!\n");
        return(false);
    }

    if( c->type == CHEVRE && !test_deplacement(c) ){
        printf("Deplacement de chevre incorect!\n");
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

    if( (tmp->destination[ABS] - tmp->destination[ORD] ) != 0){
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
        return( c->destination[ABS] == 1 );
    }

    return(false);
}

bool test_immobile(coup_s c){
    return( c->destination[ORD] == c->source[ORD] && c->destination[ABS] == c->source[ABS] );
}

bool test_limite(coup_s c){
    if( c->destination[ORD] < 0 && c->destination[ORD] > PLATEAU_HAUTEUR ){
        return(false);
    }

    if( c->destination[ABS] < 0 && c->destination[ABS] > PLATEAU_LARGEUR ){
        return(false);
    }

    return(true);
}

bool test_deplacement(coup_s c){
/*test si ça correspond à un deplacement basique correct*/
    if( fabs(c->source[ORD] - c->destination[ORD]) > 1 && fabs(c->source[ABS] - c->destination[ABS]) > 1 ){
        return(false);
    }

    if( !test_diagonale(c) ){
        return(false);
    }

    return(true);
}

bool test_deplacement_tigre(jeu_s j, coup_s c){
/*test si ça correspon à un deplacement de tigre qui mange un chèvre
  ce deplacement est valide que si il y a une chèvre à manger
*/
    if( fabs(c->source[ORD] - c->destination[ORD]) > 2 && fabs(c->source[ABS] - c->destination[ABS]) > 2 ){
        return(false);
    }

    if(!test_diagonale(c) ){
        return(false);
    }

    if( !test_eat_chevre(j,c) ){
        printf("Il n'y a pas de chevre a manger, deplacement incorrect !\n");
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

    return(true);
}

bool est_vide(plateau p, coup_s c){
    return(p->grille[c->destination[ORD]][c->destination[ABS]].pion == -1);
}

int get_pion(plateau p, int ord, int abs){
    return(p->grille[ord][abs].pion);
}

bool tigre_immobile(jeu_s j){
    bool immo = true;
    int i=0;

    while(immo == true && i<NB_MAX_TIGRE){
        if(deplacement_possible(j->p, j->g->t[i]))
            immo = false;

       i++;
    }



    return(immo);
}

bool deplacement_possible(plateau p, t_tigre t){
    int i,j;
    bool possible = false;

    i = t.position[ORD] - 2;
    j = t.position[ABS] - 2;

    while( i < i + 4 && possible == false ){
        while(j < j +4 && possible == false ){
            if(p->grille[i][j].pion == VIDE){
                possible = true;
            }else{
                j++;
            }
        }

        if(possible = false)
            i++;
    }

    return(possible);
}
