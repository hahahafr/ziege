#ifndef CONFIG_G
#define CONFIG_G

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

//Taille d'un tableau de coordonnée
#define TAILLE_POS 2
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

/*destination 1 -> abs , destination 0 ->ord*/
typedef struct et_coup_s {
    int destination[2];
    int source[2];
    int type;
}t_coup_s;

typedef t_coup_s * coup_s;

//enum FRUIT_ENUM {
//    FOREACH_FRUIT(GENERATE_ENUM)
//};

static const char *error[] = {
    "Coup hors limite !",
    "Erreur, deplacement d'une case vide!",
    "Case prise!",
    "Deplacement des pions d'un adversaire, incorrect!(tricheur)",
    "On ne peut pas placer plus de tigre!",
    "Deplacement incorrect!",
    "Deplacement de tigre incorrect!",
    "Deplacement des chevres impossible tant qu'elles ne sont pas toute posées!",
    "Toute les chevres sont posées!",
    "Deplacement de chevre incorect!"
};

#endif
