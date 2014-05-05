#include <stdio.h>
#include <ncurses.h>

#include "main.h"
#include "ui.h"

int main(int argc, char **argv)
{   

    jeux_s jeu;

    init_affichage(jeu);
    maj_affichage(jeu);

    return 0;
}
