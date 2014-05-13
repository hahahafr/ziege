#ifndef LOGIQUE_H
#define LOGIQUE_H

#include "struct_jeu.h"

/*Test si un coup est possible en tenant compte du plateau*/
bool plateau_coup(jeu_s j, coup_s c);

/*Determine si un coup est possible mais ne tiens pas en compte de ce qu'il y � l'interieur du plateau*/
int validite_coup(jeu_s j, coup_s c);

/*test si le coup utilise les diagonale et si elle sont disponnible � partir de la postion source*/
bool test_diagonale(coup_s c);

/*test si le coup n'est hors du plateau*/
bool test_limite(coup_s c);

/*test si des indice sont hors limite ou non du plateau*/
bool hors_limite(int ord,int abs);

/*test si �a correspond � un deplacement basique correct*/
bool test_deplacement(coup_s c);

/*test si �a correspon � un deplacement de tigre qui mange un ch�vre*/
bool test_deplacement_tigre(jeu_s j,coup_s c);

/*Retourne vrai ou faux selon si la case de destination est vide on non*/
bool est_vide_destination(jeu_s j, coup_s c);

/*Retourne vrai ou faux selon si la case de source est vide on non*/
bool est_vide_source(jeu_s j, coup_s c);

bool test_eat_chevre(jeu_s j, coup_s c);

/*
Test du deplacement immobile
    retournee :
        - true si le coup ne fait rien
        - false sinon
*/
bool test_immobile(coup_s c);

/*test si tout les tigres ont �t� emprisonn� de mani�re it�rative sur tout les tigres, et pour
chacun d'eux si des deplacement sont disponnible
    retourne :
        - true , si tout les tigres son coinc�s
        - false , sinon
*/
bool tigre_immobile(coup_s c);

/*test si toutes les ch�vres sont emprisonn�es*/
bool chevres_immobiles(jeu_s j);

/*test si un tigre est bloqu� par rapport � son environnement
    retourne:
        - true , si un deplacement est possible
        - false , sinon
*/
bool test_deplacement_possible(jeu_s j, t_pion t);

#endif

