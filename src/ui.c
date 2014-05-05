#include "ui.h"

int
init_affichage(jeux_s jeu)
{
    initscr();
    printw("Hi you.");
    refresh();
    getch();
    endwin();

    return 0;
}

int maj_affichage(jeux_s jeu)
{
    return 0;
}