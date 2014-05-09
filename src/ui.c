#include "ui.h"

int
init_affichage(jeux_s jeu)
{
    int screeny, screenx;
    int ch;
    
    initscr();
    cbreak();
    noecho();
    
    getmaxyx(stdscr, screeny, screenx);
    
    WINDOW *etat = newwin(20, screeny/2, 0, screenx-20);
    WINDOW *cimetiere = newwin(20, screeny/2, screenx/2, screenx-20);
    WINDOW *plateau = newwin(49, 29, (screeny-49)/2, ((screenx-29)/2));
    
    refresh();
    
    wgetch();
    endwin();
    
    return 0;
}

int
maj_affichage(jeux_s jeu)
{
    return 0;
}
