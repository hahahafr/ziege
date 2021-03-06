#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H

#include "struct_jeu.h"

void init_sauvegarde(sauvegarde * s);

void ajout_historique(jeu_s j,sauvegarde s);

jeu_s revenir_arriere(jeu_s j,sauvegarde s);

int sauvegarde_fichier(jeu_s j,sauvegarde s);

/*
    Retourne :
        - 0, si tout est ok
        - -1, si il y a une erreur au niveau du fichier de sauvegarde
*/
int chargement_fichier(jeu_s j, sauvegarde s);

#endif
