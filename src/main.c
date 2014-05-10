#include <stdio.h>

#include "main.h"
#include "ui.h"

int main(int argc, char **argv)
{   

    jeu_s jeu;
    aff_s aff;

    init_affichage(jeu, &aff);
    maj_affichage(jeu, aff);
    saisir_coups(aff);
    endwin();

    return 0;
}
