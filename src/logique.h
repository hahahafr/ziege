#ifndef LOGIQUE_H
#define LOGIQUE_H

#include "struct_jeu.h"

/*Test si un coup est possible en tenant compte du plateau*/
bool plateau_coup(jeu_s j, coup_s c);

/*Determine si un coup est possible mais ne tiens pas en compte de ce qu'il y à l'interieur du plateau*/
bool validite_coup(jeu_s j, coup_s c);

/*test si le coup utilise les diagonale et si elle sont disponnible à partir de la postion source*/
bool test_diagonale(coup_s c);

/*test si le coup n'est hors du plateau*/
bool test_limite(coup_s c);

/*test si ça correspond à un deplacement basique correct*/
bool test_deplacement(coup_s c);

/*test si ça correspon à un deplacement de tigre qui mange un chèvre*/
bool test_deplacement_tigre(jeu_s j,coup_s c);

/*Retourne vrai ou faux selon si la case de destination est vide on non*/
bool est_vide_destination(jeu_s j, coup_s c);

/*Retourne vrai ou faux selon si la case de source est vide on non*/
bool est_vide_source(jeu_s j, coup_s c);

/*
Test du deplacement immobile
    retournee :
        - true si le coup ne fait rien
        - false sinon
*/
bool test_immobile(coup_s c);

/*test si tout les tigres ont été emprisonné de manière itérative sur tout les tigres, et pour
chacun d'eux si des deplacement sont disponnible
    retourne :
        - true , si tout les tigres son coincés
        - false , sinon
*/
bool tigre_immobile(jeu_s j);

/*test si toutes les chèvres sont emprisonnées*/
bool chevres_immobiles(jeu_s j);

/*test si un tigre est bloqué par rapport à son environnement
    retourne:
        - true , si un deplacement est possible
        - false , sinon
*/
bool test_deplacement_possible(jeu_s j, t_pion t);

#endif

