#ifndef PARTIE_H
#define PARTIE_H

#include "config.h"
#include "struct_jeu.h"

//initialise la partie
void init_partie(jeu_s j);

//initialise le tableau de tigre mais aussi leur position de début sur le plateau
void init_tigres(jeu_s j);

void tour_suivant(partie g);

#endif

