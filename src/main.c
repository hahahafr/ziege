#include <stdio.h>

#include "main.h"
#include "ui.h"

int main(int argc, char **argv)
{   

    jeu_s jeu;
    aff_s aff;

    init_jeu(&jeu);
    init_affichage(jeu, &aff);
    init_player_ui(jeu, aff);

    jouer_ui(jeu, aff);
    
    endwin();

    return 0;
}
