#ifndef JEU_H
#define JEU_H

#include "config.h"
#include "struct_jeu.h"

void init_jeu(jeu_s * j);
void init_player(jeu_s j);

int jouer(jeu_s j);

/*
test si tout les chèvre on été mangé ou que tout les tigres soient bloqués
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
    fontion appelant le module dde logique pour vérifier la validité d'un coup jouer
    retourne :
        - true, dans le cas ou le coup est valide
        - false, dans ce cas resaisi du coup
*/
bool traitement_action(jeu_s j, coup_s c);

/*
Mis à jour du plateau en conséquence du coup joué
*/
int maj_plateau(jeu_s j, coup_s c);


#endif
