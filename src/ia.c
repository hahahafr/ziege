#include "ia.h"

coup_s choix_placement_chevre(jeu_s je){
    int i,j,ord,abs, score = 0,score_iter=0;
    coup_s c,r;

    i = 0;
    j = 0;

    c = (coup_s)malloc(sizeof(t_coup_s));
    r = (coup_s)malloc(sizeof(t_coup_s));

    r->type = c->type = CHEVRE;

    c->source[ORD] = r->source[ORD] = -1;
    c->source[ABS] = r->source[ABS] = -1;

    while( i < PLATEAU_HAUTEUR && score < 2 ){
        j=0;
        while(j < PLATEAU_LARGEUR && score < 2){
            c->destination[ORD] = i;
            c->destination[ABS] = j;

            if( est_vide_destination(je,c)){
                score_iter = test_position_chevre(je,c);

                if(score_iter > score ){
                    score = score_iter;
                    r->destination[ORD] = i;
                    r->destination[ABS] = j;
                }
            }

            j++;
        }

        i++;
    }

    if( score == 0 ){
        free(r);
        return(c);
    }
    free(c);
    return(r);

}

coup_s choix_deplacement_chevre(jeu_s j){
    coup_s r;
    coup_s c;

    int score=1, score_iter=2, i=0;

    int op_ord;
    int op_abs;

    r = (coup_s)malloc(sizeof(t_coup_s));
    c = (coup_s)malloc(sizeof(t_coup_s));

    while( i < NB_MAX_CHEVRE && score != 0 ){
        /*on doit chercher qu'elle chevre va se faire bouffer si on ne fait rien*/

        if( j->g->c[i].position[ORD] != -1 ){
            c->destination[ORD] = j->g->c[i].position[ORD];
            c->destination[ABS] = j->g->c[i].position[ABS];

            c->source[ORD] = -1;
            c->source[ABS] = -1;

            score_iter = test_position_chevre(j,c);

            if(score_iter == 0){

                c->source[ORD] = j->g->c[i].position[ORD];
                c->source[ABS] = j->g->c[i].position[ABS];

                if(score_iter < chevre_deplacement(j,c) ){
                    /*si un deplacement peut la sauver*/
                    r->source[ORD] = c->source[ORD];
                    r->source[ABS] = c->source[ABS];

                    r->destination[ORD] = c->destination[ORD];
                    r->destination[ABS] = c->destination[ABS];

                    score = score_iter;
                }
            }

            if( score_iter != 0 && score_iter >= score ){
                c->source[ORD] = j->g->c[i].position[ORD];
                c->source[ABS] = j->g->c[i].position[ABS];
                /*chercher le meilleur deplacement*/

                if( chevre_deplacement(j,c) >= score_iter ){
//                    printf("%d %d\n",c->destination[ORD],c->destination[ABS]);
                    r->source[ORD] = c->source[ORD];
                    r->source[ABS] = c->source[ABS];

                    r->destination[ORD] = c->destination[ORD];
                    r->destination[ABS] = c->destination[ABS];

                    score = score_iter;
                }

            }
        }else{
            //pas de chevre
        }
        i++;
    }

    return(r);
}

int chevre_deplacement(jeu_s j,coup_s c){
    int score = 0;
    int score_iter = 0;

    int ord = c->source[ORD] - 1;
    int abs = c->source[ABS] - 1;

    int op_ord;
    int op_abs;

    int limit_ord = c->source[ORD]+2;
    int limit_abs = c->source[ABS]+1;

    coup_s r;

    r = (coup_s)malloc(sizeof(t_coup_s));

    while( ord < limit_ord && score != 2 ){
        abs = c->source[ABS] - 1;

        do{
            op_ord = c->source[ORD] + (c->source[ORD] - ord);
            op_abs = c->source[ABS] + (c->source[ABS] - abs);

            //SI les coordonne existent
            if( !hors_limite(ord,abs) || !hors_limite(op_ord,op_abs) ){
                //POS
                if( !hors_limite(ord,abs) && get_pion(j->p,ord,abs) == VIDE ){
                    c->destination[ORD] =  ord;
                    c->destination[ABS] =  abs;

                    score_iter = test_position_chevre(j,c);

                    if(score_iter >= score){
                        score = score_iter;
                        r->destination[ORD] = ord;
                        r->destination[ABS] = abs;
                    }
                }
                //OPPOSE POS
                if( !hors_limite(op_ord,op_abs) && get_pion(j->p,op_ord,op_abs) == VIDE ){
                    c->destination[ORD] =  op_ord;
                    c->destination[ABS] =  op_abs;

                    score_iter = test_position_chevre(j,c);

                    if(score_iter >= score){
                        score = score_iter;
                        r->destination[ORD] = op_ord;
                        r->destination[ABS] = op_abs;
                    }
                }
            }
            abs++;
        }while(abs < limit_abs && score != 2 && ord < c->destination[ORD]);

        ord++;
    }

    c->destination[ORD] =  r->destination[ORD];
    c->destination[ABS] =  r->destination[ABS];

    free(r);

    return(score);

}

int test_position_chevre(jeu_s je,coup_s c){
    int score = 2;
    int score_iter = 1;

    int ord = c->destination[ORD] - 1;
    int abs = c->destination[ABS] - 1;

    int op_ord;
    int op_abs;

    int limit_ord = c->destination[ORD]+2;
    int limit_abs = c->destination[ABS]+1;

    while( ord < limit_ord && score != 0 ){
        abs = c->destination[ABS] - 1;
        do{
            op_ord = c->destination[ORD] + (c->destination[ORD] - ord);
            op_abs = c->destination[ABS] + (c->destination[ABS] - abs);



            //SI les coordonne existent
            if( !hors_limite(ord,abs) || !hors_limite(op_ord,op_abs)){
                //POS
                if( !hors_limite(ord,abs) && ( c->source[ORD] != ord || c->source[ABS] != abs ) ){
//                    printf("pion %d %d : %d\n",ord,abs, get_pion(je->p,ord,abs));
                    if( get_pion(je->p,ord,abs) == CHEVRE ){
                        score_iter = 2;
                    }

                    if( get_pion(je->p,ord,abs) == VIDE ){
                        score_iter = 1;
                    }

                    if( get_pion(je->p,ord,abs) == TIGRE ){
                        score_iter = 0;
                    }
                }

                if( c->source[ORD] != ord && c->source[ABS] != abs ){
                    score_iter = 1;
                }

                //OPPOSE POS
                if( !hors_limite(op_ord,op_abs) && ( c->source[ORD] != op_ord || c->source[ABS] != op_abs ) ){


                    if( get_pion(je->p,op_ord,op_abs) == CHEVRE ){
                        score_iter = 2;
                    }

                    if( get_pion(je->p,op_ord,op_abs) == TIGRE && score_iter != 1 ){
                        score_iter = 2;
                    }
//                    printf("pion %d %d : %d\n",op_ord,op_abs, get_pion(je->p,op_ord,op_abs));
                    if( get_pion(je->p,op_ord,op_abs) == TIGRE && score_iter == 1 ){
                        score_iter = 0;
                    }

                }

                score = score_iter;
            }

            abs++;
        }while(abs < limit_abs && score != 0 && ord < c->destination[ORD]);

        ord++;
    }

    return(score);
}

coup_s choix_deplacement_tigre(jeu_s je){
    int i,j,ord,abs, score = 0,score_iter=0;
    coup_s c,r;

    i = 0;

    c = (coup_s)malloc(sizeof(t_coup_s));
    r = (coup_s)malloc(sizeof(t_coup_s));

    c->source[ORD] = r->source[ORD] = je->g->t[i].position[ORD];
    c->source[ABS] = r->source[ABS] = je->g->t[i].position[ABS];

    c->type = r->type = TIGRE;

    r->destination[ORD] = -1;
    r->destination[ABS] = -1;

    r->type = c->type = TIGRE;

    while( i < NB_MAX_TIGRE && score < 2 ){
        c->source[ORD]= je->g->t[i].position[ORD];
        c->source[ABS] = je->g->t[i].position[ABS];

//        printf("\ntigre en : %d %d\n",c->source[ORD],c->source[ABS]);

        score_iter = test_position_tigre(je,c);

        if(score_iter >= score){
            score = score_iter;
            r->source[ORD] = c->source[ORD];
            r->source[ABS] = c->source[ABS];

            r->destination[ORD] = c->destination[ORD];
            r->destination[ABS] = c->destination[ABS];

        }
        i++;
    }

//    printf("Deplacement tigre : %d %d -> %d %d\n",r->source[ORD],r->source[ABS],r->destination[ORD],r->destination[ABS]);
    free(c);
    return(r);
}

int test_position_tigre(jeu_s j,coup_s c){
    int score = 0,score_iter=0;

    int ord = c->source[ORD] - 1;
    int abs = c->source[ABS] - 1;

    //Coordonnée pour voir ce qu'il y a derriere une chevre
    int der_ord;
    int der_abs;

    int op_ord;
    int op_abs;

    int limit_ord = c->source[ORD]+2;
    int limit_abs = c->source[ABS]+1;

    while( ord < limit_ord && score != 1 ){
        abs = c->source[ABS] - 1;

        do{
            op_ord = c->source[ORD] + (c->source[ORD] - ord);
            op_abs = c->source[ABS] + (c->source[ABS] - abs);

            //SI les coordonne existent
            if( !hors_limite(ord,abs) || !hors_limite(op_ord,op_abs) ){
                if( !hors_limite(ord,abs) ){

                    der_ord = ord + (ord - c->source[ORD]);
                    der_abs = abs + (abs - c->source[ABS]);

                    if( get_pion(j->p,ord,abs) == VIDE ){
                        c->destination[ORD] = ord;
                        c->destination[ABS] = abs;
                    }

                    if( get_pion(j->p,ord,abs) == CHEVRE && !hors_limite(der_ord,der_abs) && get_pion(j->p,der_ord,der_abs) == VIDE ){
                        //je mange
                        c->destination[ORD] = der_ord;
                        c->destination[ABS] = der_abs;
                        score_iter = 1;

                    }
                }

                //OPPOSE POS
                if( !hors_limite(op_ord,op_abs) ){
                    der_ord = op_ord + (op_ord - c->source[ORD]);
                    der_abs = op_abs + (op_abs - c->source[ABS]);

                    if( get_pion(j->p,op_ord,op_abs) == VIDE ){
                        c->destination[ORD] = op_ord;
                        c->destination[ABS] = op_abs;
                    }

                    if( get_pion(j->p,op_ord,op_abs) == CHEVRE && !hors_limite(der_ord,der_abs) && get_pion(j->p,der_ord,der_abs) == VIDE ){
                        // ou j'ai de la chance moi
                        score_iter = 1;
                        c->destination[ORD] = der_ord;
                        c->destination[ABS] = der_abs;
                    }
                }

                score = score_iter;
            }

            abs++;
        }while(abs < limit_abs && score != 1 && ord < c->source[ORD]);

        ord++;
    }

    return(score);
}


