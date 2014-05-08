#ifndef JEU_H
#define JEU_H

#include "config.h"
#include "struct_jeu.h"
#include "sauvegarde.h"

void init_jeu(jeu_s * j);
void init_player(jeu_s j);

int jouer(jeu_s j);

/*
test si tout les ch�vre on �t� mang� ou que tout les tigres soient bloqu�s
    retourne ;
        - true, si la fin de la partie est atteinte
        - false sinon
*/
bool is_end(jeu_s j);

/*
    retourne ;
        - l'adresse d'un coup jouer par  l'un des joueurs
*/
coup_s saisi_action(jeu_s j);

/*
    fontion appelant le module dde logique pour v�rifier la validit� d'un coup jouer
    retourne :
        - true, dans le cas ou le coup est valide
        - false, dans ce cas resaisi du coup
*/
bool traitement_action(jeu_s j, coup_s c);

/*
Mis � jour du plateau en cons�quence du coup jou�
*/
int maj_plateau(jeu_s j, coup_s c);

/*test des d�placement des tigres*/
void deplacement_tigre(jeu_s * j);

/*Mise a jour des score*/
void maj_score(jeu_s j);


#endif
