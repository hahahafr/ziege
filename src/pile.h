#ifndef def_pile_fonction
#define def_pile_fonction

#include "config.h"

typedef struct jeu_s * Element;

typedef struct Cell {
	Element elem;
	struct Cell * suivant;
}T_Cell;

typedef struct Cell * Pile;

void INIT_PILE(Pile * p);
bool PILE_VIDE(Pile p);
void AFFICHER(Pile p);
void EMPILER(Pile * p, Element elem);
Element DEPILER(Pile * p);
Element SOMMET(Pile * p);

#endif
