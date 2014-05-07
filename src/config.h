#ifndef CONFIG_G
#define CONFIG_G

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

//Taille max du nom d'un joueur
#define TAILLE_NOM 20
//Nombre max de tigre
#define NB_MAX_TIGRE 4
//Nombre max de chèvre
#define NB_MAX_CHEVRE 20
//Indice de l'ordonnée dans le tableau des coordonnées
#define ORD 0
//Indice de l'abscisse dans le tableau des coordonnées
#define ABS 1
//Valeur de la source quand le coup_s correspond à un ajout
#define AJOUT -1
//Phase de la partie
#define PHASE_PLACEMENT 0
#define PHASE_DEPLACEMENT 1
#define PHASE_FIN 2
//Hauteur du plateau
#define PLATEAU_HAUTEUR 5
//Largeur du plateau
#define PLATEAU_LARGEUR 5
//Type des cases et role des joueurs
#define CHEVRE 0
#define TIGRE 1
#define VIDE -1


#endif
