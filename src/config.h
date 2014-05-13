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
#define NB_MAX_TIGRE 1
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

//static const char * const error[] = {
//    "Coup hors limite !\n",
//    "Erreur, deplacement d'une case vide!\n",
//    "Case prise!\n",
//    "Deplacement des pions d'un adversaire, incorrect!(tricheur)\n",
//    "On ne peut pas placer plus de tigre!\n",
//    "Deplacement incorrect!\n",
//    "Deplacement de tigre incorrect!\n",
//    "Deplacement des chevres impossible tant qu'elles ne sont pas toute posées!\n",
//    "Toute les chevres sont posées!\n",
//    "Deplacement de chevre incorect!\n"
//};

//static const char * error = "Erreur!\n";

#define FOREACH_FRUIT(FRUIT) \
        FRUIT(apple)   \
        FRUIT(orange)  \
        FRUIT(grape)   \
        FRUIT(banana)  \

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

//enum FRUIT_ENUM {
//    FOREACH_FRUIT(GENERATE_ENUM)
//};

static const char *error[] = {
    "Coup hors limite !\n",
    "Erreur, deplacement d'une case vide!\n",
    "Case prise!\n",
    "Deplacement des pions d'un adversaire, incorrect!(tricheur)\n",
    "On ne peut pas placer plus de tigre!\n",
    "Deplacement incorrect!\n",
    "Deplacement de tigre incorrect!\n",
    "Deplacement des chevres impossible tant qu'elles ne sont pas toute posées!\n",
    "Toute les chevres sont posées!\n",
    "Deplacement de chevre incorect!\n"
};

#endif
