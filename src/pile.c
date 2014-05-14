#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pile.h"

void INIT_PILE(Pile * p){
	*p=NULL;
}

bool PILE_VIDE(Pile p){
	if(p == NULL){
		return(true);
	}else{
		return(false);
	}
}

bool PILE_PLEINE(Pile p){
	Pile tmp = (Pile) malloc(sizeof(Pile));
	if(tmp == NULL){
		return(true);
	}else{
		free(tmp);
		return(false);
	}
}

void AFFICHER(Pile p){
	printf("Affichage de la pile :\n");
	while(p != NULL){
		printf("Element = %d \n",(int)p->elem);
		p = p->suivant;
	}
}

void EMPILER(Pile * p, Element elem){
	Pile tmp;
	if(PILE_PLEINE((*p))){
		printf("La pile est pleine\n");
	}else{
		if( PILE_VIDE((*p))){
			(*p) = (Pile) malloc(sizeof(Pile));
			(*p)->elem = elem;
			(*p)->suivant = NULL;
		}else{
			tmp = malloc(sizeof(Pile));

			tmp->suivant = *p;
			tmp->elem = elem;

			*p = tmp;
		}
	}
}

Element DEPILER(Pile * p){
	Pile tmp;
	Element elem = 0;

	if( PILE_VIDE((*p))){
		return(-1);
	}else{
		tmp = *p;

		elem = tmp->elem;

		*p = (*p)->suivant;
		free(tmp);


	}
	return(elem);
}


