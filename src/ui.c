#include "ui.h"

void
init_affichage(jeu_s jeu, aff_s *aff)
{
    initscr();
    start_color();

    init_pair(20+CHEVRE, COLOR_WHITE, COLOR_GREEN);
    init_pair(20+TIGRE, COLOR_WHITE, COLOR_RED);
    init_pair(23, COLOR_WHITE, COLOR_YELLOW);

    noecho();
    cbreak();
    curs_set(0);

    int screeny, screenx;
    int plateau_orig_y, plateau_orig_x;

    getmaxyx(stdscr, screeny, screenx);

    plateau_orig_y = (screeny-TAILLE_PLATEAU_H)/2;
    plateau_orig_x = (screenx-TAILLE_PLATEAU_L-TAILLE_ETAT_L)/2;

    WINDOW *plateau = newwin(
      TAILLE_PLATEAU_H,
      TAILLE_PLATEAU_L,
      plateau_orig_y,
      plateau_orig_x);

    WINDOW *etat = newwin(
      screeny/2,
      TAILLE_ETAT_L,
      0,
      screenx-TAILLE_ETAT_L+2);

    WINDOW *cimetiere = newwin(
      screeny/2,
      TAILLE_CIM_L,
      screeny/2,
      screenx-TAILLE_CIM_L+2);

    WINDOW *message = newwin(
      3,
      screenx-TAILLE_ETAT_L-2,
      1,
      2);

    wattron(message, A_BOLD | COLOR_PAIR(23));
    
    wborder(etat, ACS_VLINE, ' ', ' ', ACS_HLINE, ACS_VLINE, ' ', ACS_LTEE, ACS_HLINE); 
    wborder(cimetiere, ACS_VLINE, ' ', ' ', ' ', ACS_VLINE, ' ', ACS_VLINE, ' ');
    box(plateau, ACS_VLINE, ACS_HLINE);
    
    refresh();
    wrefresh(etat);
    wrefresh(cimetiere);
    wrefresh(plateau);

    (* aff) = (aff_s)malloc(sizeof(t_affichage_s));

    (* aff)->plateau_orig_y=plateau_orig_y;
    (* aff)->plateau_orig_x=plateau_orig_x;
    (* aff)->etat=etat;
    (* aff)->plateau=plateau;
    (* aff)->cimetiere=cimetiere;
    (* aff)->message=message;


    tracer_plateau((* aff));

    mvwprintw(cimetiere, 0, 2, "Appuyer sur 's' pour sauvegarder");
    wrefresh(etat);
    wrefresh(cimetiere);
    wrefresh(plateau);


    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            // i = y
            // j = x
            (* aff)->tabindcoord[i][j]=malloc(2*sizeof(int));
            (* aff)->tabindcoord[i][j][ORD]=2+plateau_orig_y+(6*i);
            (* aff)->tabindcoord[i][j][ABS]=4+plateau_orig_x+(10*j);
        }
    }
}
/*
void ui_redraw(jeu_s jeu, aff_s aff)
{
    int plateau_orig_y = (screeny-TAILLE_PLATEAU_H)/2;
    int plateau_orig_x = (screenx-TAILLE_PLATEAU_L-TAILLE_ETAT_L)/2;

    wrefresh(aff->etat);
    wrefresh(aff->cimetiere);
    wrefresh(aff->plateau);

    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            // i = y
            // j = x
            aff->tabindcoord[i][j]=malloc(2*sizeof(int));
            aff->tabindcoord[i][j][ORD]=2+plateau_orig_y+(6*i);
            aff->tabindcoord[i][j][ABS]=4+plateau_orig_x+(10*j);
        }
    }
    }
}
*/

void tracer_plateau(aff_s aff)
{
    for (int y = 0; y < TAILLE_PLATEAU_H-2; y++)
    {
        for (int x = 0; x < TAILLE_PLATEAU_L-4; x++)
        {
            mvwaddch(aff->plateau, y+1, x+2, return_ch_plateau(y, x));
        }
    }
}

int
coord_aff_vers_jeu(aff_s aff, int iny, int inx, int *outx, int *outy)
{
    int i, j;
    i = j = 0;

    int trouve = 0;

    while (i < PLATEAU_LARGEUR && !trouve)
    {
        j = 0;

        while (j < PLATEAU_HAUTEUR && !trouve)
        {
            if ((aff->tabindcoord[i][j][ORD] <= iny+1 && aff->tabindcoord[i][j][ORD] >= iny-1)
              && (aff->tabindcoord[i][j][ABS] <= inx+2 && aff->tabindcoord[i][j][ABS] >= inx-2))
                trouve = 1;
            else
                j++;
        }

        if (!trouve)
            i++;
    }

    if (!trouve)
        return 1;

    *outx = j;
    *outy = i;

    return 0;
}

void
coord_jeu_vers_aff(aff_s aff, int inx, int iny, int *outy, int *outx)
{
    *outy = (aff->tabindcoord[iny][inx][ORD])-(aff->plateau_orig_y);
    *outx = (aff->tabindcoord[iny][inx][ABS])-(aff->plateau_orig_x);
}

void
maj_affichage(jeu_s jeu, aff_s aff)
{

    int x, y;
    
    int winmaxx, winmaxy;
    getmaxyx(aff->etat, winmaxy, winmaxx);
    
    mvwprintw(aff->etat, winmaxy - 2, 2, "Score TIGRE:");
    wattron(aff->etat, A_BOLD);
    wprintw(aff->etat, " %d", jeu->participant[TIGRE].score);
    wattroff(aff->etat, A_BOLD);
    wclrtoeol(aff->etat);

    mvwprintw(aff->etat, winmaxy - 3, 2, "Score CHEVRE:");
    wattron(aff->etat, A_BOLD);
    wprintw(aff->etat, " %d", jeu->participant[CHEVRE].score);
    wattroff(aff->etat, A_BOLD);
    wclrtoeol(aff->etat);
    
    if (get_phase(jeu) == PHASE_PLACEMENT)
    {
        mvwprintw(aff->etat, winmaxy - 4, 2, "PHASE: ");
        wattron(aff->etat, A_BOLD);
        wprintw(aff->etat, "PLACEMENT", get_phase(jeu));
        wattroff(aff->etat, A_BOLD);
        wclrtoeol(aff->etat);
    }
    if (get_phase(jeu) == PHASE_DEPLACEMENT)
    {
        mvwprintw(aff->etat, winmaxy - 4, 2, "PHASE: ");
        wattron(aff->etat, A_BOLD);
        wprintw(aff->etat, "DEPLACEMENT", get_phase(jeu));
        wattroff(aff->etat, A_BOLD);
        wclrtoeol(aff->etat);
    }

    if (get_joueur(jeu) == CHEVRE)
    {
        mvwprintw(aff->etat, winmaxy - 5, 2, "JOUEUR: ");
        wattron(aff->etat, A_BOLD | COLOR_PAIR(20));
        wprintw(aff->etat, "CHEVRE", get_joueur(jeu));
        wattroff(aff->etat, A_BOLD | COLOR_PAIR(20));
        wclrtoeol(aff->etat);
    }
    if (get_joueur(jeu) == TIGRE)
    {
        mvwprintw(aff->etat, winmaxy - 5, 2, "JOUEUR: ");
        wattron(aff->etat, A_BOLD | COLOR_PAIR(21));
        wprintw(aff->etat, "TIGRE", get_joueur(jeu));
        wattroff(aff->etat, A_BOLD | COLOR_PAIR(21));
        wclrtoeol(aff->etat);
    }

    mvwprintw(aff->etat, winmaxy - 6, 2, "CHEVRES VIVANTES:");
    wattron(aff->etat, A_BOLD);
    wprintw(aff->etat, " %d", jeu->g->nb_chevre);
    wattroff(aff->etat, A_BOLD);
    wclrtoeol(aff->etat);

    mvwprintw(aff->etat, winmaxy - 7, 2, "CHEVRES A PLACER:");
    wattron(aff->etat, A_BOLD);
    wprintw(aff->etat, " %d", NB_MAX_CHEVRE-jeu->participant[TIGRE].score-jeu->g->nb_chevre);
    wattroff(aff->etat, A_BOLD);
    wclrtoeol(aff->etat);


    // i = ORD = x
    // j = ABS = y
    for (int i = 0; i < PLATEAU_LARGEUR; i++)
    {
        for (int j = 0; j < PLATEAU_HAUTEUR; j++)
        {
            if (get_pion(jeu->p,j,i) == CHEVRE)
            {
                coord_jeu_vers_aff(aff, i, j, &y, &x);
                retracer_case(aff, y, x, CHEVRE);
                wrefresh(aff->plateau);
            }
            else if (get_pion(jeu->p,j,i) == TIGRE)
            {
                coord_jeu_vers_aff(aff, i, j, &y, &x);
                retracer_case(aff, y, x, TIGRE);
                wrefresh(aff->plateau);
            }
            else
            {
                coord_jeu_vers_aff(aff, i, j, &y, &x);
                retracer_case(aff, y, x, VIDE);
                wrefresh(aff->plateau);
            }
        }
    }
}

void retracer_case(aff_s aff, int y, int x, int p)
{
    if (p == CHEVRE)
    {
        for (int l = 0; l < 3; l++)
            for (int c = 0; c < 5; c++)
                mvwaddch(aff->plateau, y-1+l, x-2+c, return_ch_plateau(l, c) | A_BOLD | COLOR_PAIR(20));
        mvwaddch(aff->plateau, y, x, CHEVRE_CH | A_BOLD | COLOR_PAIR(20));
    }
    else if (p == TIGRE)
    {
        for (int l = 0; l < 3; l++)
            for (int c = 0; c < 5; c++)
                mvwaddch(aff->plateau, y-1+l, x-2+c, return_ch_plateau(l, c) | A_BOLD | COLOR_PAIR(21));
        mvwaddch(aff->plateau, y, x, TIGRE_CH | A_BOLD | COLOR_PAIR(21));
    }
    else
    {
        for (int l = 0; l < 3; l++)
            for (int c = 0; c < 5; c++)
                mvwaddch(aff->plateau, y-1+l, x-2+c, return_ch_plateau(l, c) | A_NORMAL);
        mvwaddch(aff->plateau, y, x, VIDE_CH | A_NORMAL);
    }
}

int return_ch_plateau(int y, int x)
{
    if (x%10 == 0 && y%6 == 0)
        return ACS_ULCORNER;
    
    if ((x%10 >= 1 && x%10 <= 3) && (y%6 == 0 || y%6 == 2)
      || ((x%10 >= 5 && x%10 <= 9) && (y%6 == 1)))
        return ACS_HLINE;

    if (x%10 == 4 && y%6 == 0)
        return ACS_URCORNER;

    if ((x%10 == 0 || x%10 == 4) && (y%6 == 1)
      || (x%10 == 2 && y%6 >= 3 && y%6 <= 5))
        return ACS_VLINE;

    if (x%10 == 4 && y%6 == 2)
        return ACS_LRCORNER;

    if (x%10 == 0 && y%6 == 2)
        return ACS_LLCORNER;

    if ((x%20 == 5 && y%12 == 3)
      || (x%20 == 7 && y%12 == 4)
      || (x%20 == 9 && y%12 == 5)
      || (x%20 == 15 && y%12 == 9)
      || (x%20 == 17 && y%12 == 10)
      || (x%20 == 19 && y%12 == 11))
        return '\\';

    if ((x%20 == 15 && y%12 == 5)
      || (x%20 == 17 && y%12 == 4)
      || (x%20 == 19 && y%12 == 3)
      || (x%20 == 5 && y%12 == 11)
      || (x%20 == 7 && y%12 == 10)
      || (x%20 == 9 && y%12 == 9))
        return '/';

    return ' ';
}


void jouer_ui(jeu_s jeu, aff_s aff)
{
    coup_s c;
    int erreur=0;
    int x, y;

    while(!is_end(jeu))
    {
        maj_affichage(jeu, aff);
        if (jeu->participant[jeu->g->joueur].is_ai)
            c = choix_coup_ai(jeu);
        else
            c = saisir_coups(jeu, aff);
        erreur = jouer(jeu, c);

    if(!erreur == 0)
    {
        //afficher_message(aff, "ERRUURE");
    }
    else
    {
        wmove(aff->message, 0, 0);
        wclrtoeol(aff->message);
        wrefresh(aff->message);
    }

    }
    
        clear();
        getmaxyx(stdscr, y, x);
        attron(A_BOLD | A_REVERSE); 
        keypad(stdscr, FALSE);
        if (jeu->participant[TIGRE].score == 7)
            mvprintw((y/2), (x/2)-23, "Les tigres ont gagnés !");
        else
            mvprintw((y/2), (x/2)-24, "Les chèvres ont gagnés !");
    

    getch();
}

void afficher_message(aff_s aff, char *mess)
{
    for (int i = 0; i < strlen(mess)+4; i++)
        mvwaddch(aff->message, 0, i, ' ');
    
    mvwprintw(aff->message, 1, 0, '  ');
    wprintw(aff->message, mess);
    wprintw(aff->message, '  ');
    wclrtoeol(aff->message);

    for (int i = 0; i < strlen(mess)+4; i++)
        mvwaddch(aff->message, 2, i, ' ');

    wrefresh(aff->message);
}

void
init_player_ui(jeu_s jeu, aff_s aff)
{
    char nomj1[TAILLE_NOM];
    char nomj2[TAILLE_NOM];
    char rolej1;
    char ai;
    int roleint;

    curs_set(1);
    echo();

    do {
    wattron(aff->etat, A_BOLD | A_REVERSE);
    mvwprintw(aff->etat, 1, 2, "Entrez le rôle du joueur 1");
    mvwprintw(aff->etat, 2, 2, "0 pour chèvre, 1 pour tigre :");
    wattroff(aff->etat, A_BOLD | A_REVERSE);
    wattron(aff->etat, A_BOLD);
    mvwscanw(aff->etat, 3, 2, "%c", &rolej1);
    wrefresh(aff->etat);
    wattroff(aff->etat, A_BOLD);

    wmove(aff->etat, 1, 2);
    wclrtoeol(aff->etat);
    wmove(aff->etat, 2, 2);
    wclrtoeol(aff->etat);
    wmove(aff->etat, 3, 2);
    wclrtoeol(aff->etat);
    wrefresh(aff->etat);
    } while ((rolej1 != '0') && (rolej1) != '1');

    if (rolej1 == '0')
        roleint = 0;
    else
        roleint = 1;


    do {
    wattron(aff->etat, A_BOLD | A_REVERSE);
    mvwprintw(aff->etat, 1, 2, "Jouer contre l'AI ?");
    mvwprintw(aff->etat, 2, 2, "0 pour NON, 1 pour OUI:");
    wattroff(aff->etat, A_BOLD | A_REVERSE);
    wattron(aff->etat, A_BOLD);
    mvwscanw(aff->etat, 3, 2, "%c", &ai);
    wrefresh(aff->etat);
    wattroff(aff->etat, A_BOLD);

    wmove(aff->etat, 1, 2);
    wclrtoeol(aff->etat);
    wmove(aff->etat, 2, 2);
    wclrtoeol(aff->etat);
    wmove(aff->etat, 3, 2);
    wclrtoeol(aff->etat);
    wrefresh(aff->etat);
    } while ((ai != '0') && (ai) != '1');

    if (ai == '0')
        init_player(jeu, roleint);
    else
        init_player_ai(jeu, roleint, !roleint);

    curs_set(0);
    noecho();
}

coup_s
saisir_coups(jeu_s jeu, aff_s aff)
{
    int c;
    MEVENT event;
    mousemask(ALL_MOUSE_EVENTS, NULL);



    int clics_sont_valides = 0;
    int err;

    coup_s coup = malloc(sizeof(t_coup_s));

    int second_click = 0;


    if (get_phase(jeu) == PHASE_PLACEMENT && get_joueur(jeu) == CHEVRE)
    {
        coup->source[ABS]=-1;
        coup->source[ORD]=-1;
        second_click = 1;
        wattron(aff->etat, A_REVERSE | A_BOLD);
        mvwprintw(aff->etat, 1, 2, "Positionnez une chèvre");
        wattroff(aff->etat, A_REVERSE | A_BOLD);
        wrefresh(aff->etat);
    }
    if (get_phase(jeu) == PHASE_DEPLACEMENT && get_joueur(jeu) == CHEVRE)
    {
        wattron(aff->etat, A_REVERSE | A_BOLD);
        mvwprintw(aff->etat, 1, 2, "Déplacez une chèvre");
        wattroff(aff->etat, A_REVERSE | A_BOLD);
        wrefresh(aff->etat);
    }
    if (get_joueur(jeu) == TIGRE)
    {
        wattron(aff->etat, A_REVERSE | A_BOLD);
        mvwprintw(aff->etat, 1, 2, "Déplacez un tigre");
        wattroff(aff->etat, A_REVERSE | A_BOLD);
        wrefresh(aff->etat);
    }

    do
    {
        keypad(stdscr, TRUE);
        c = getch();
        if (c == KEY_MOUSE)
            if(getmouse(&event) == OK)
                if(event.bstate & BUTTON1_CLICKED)
                {
                    wmove(aff->etat, 1, 2);
                    wclrtoeol(aff->etat);
                    wmove(aff->etat, 2, 2);
                    wclrtoeol(aff->etat);
                    wmove(aff->etat, 3, 2);
                    wclrtoeol(aff->etat);
                    if (second_click)
                    {

                        wattron(aff->etat, A_BOLD);
                        mvwprintw(aff->etat, 3, 2, "FAIRE SELECTION");
                        wattroff(aff->etat, A_BOLD);
                        wrefresh(aff->etat);

                        err = coord_aff_vers_jeu(aff, event.y, event.x, &(coup->destination[ABS]),
                         &(coup->destination[ORD]));
                        if (!err)
                        {
                            clics_sont_valides = 1;

                            wmove(aff->etat, 2, 2);
                            wclrtoeol(aff->etat);
                            mvwprintw(aff->etat, 2, 2, "DX: ");
                            wattroff(aff->etat, A_BOLD);
                            wattron(aff->etat, A_BOLD);
                            wprintw(aff->etat, "%d ", coup->destination[ABS]);
                            wattroff(aff->etat, A_BOLD);
                            wprintw(aff->etat, "DY: ");
                            wattron(aff->etat, A_BOLD);
                            wprintw(aff->etat, "%d", coup->destination[ORD]);
                            wattroff(aff->etat, A_BOLD);
                            wrefresh(aff->etat);
                        }
                        else
                        {
                            wattron(aff->etat, A_REVERSE | A_BOLD);
                            mvwprintw(aff->etat, 2, 2, "Clic invalide, cliquez sur un pion!");
                            wattroff(aff->etat, A_REVERSE | A_BOLD);
                            wrefresh(aff->etat);
                        }
                    }
                    else
                    {

                        wattron(aff->etat, A_BOLD);
                        mvwprintw(aff->etat, 3, 2, "CHOIX DE LA DESTINATION");
                        wattroff(aff->etat, A_BOLD);
                        wrefresh(aff->etat);

                        err = coord_aff_vers_jeu(aff, event.y, event.x, &(coup->source[ABS]),
                         &(coup->source[ORD]));
                        if (!err)
                        {
                            second_click = 1;
                            wmove(aff->etat, 1, 2);
                            wclrtoeol(aff->etat);
                            wmove(aff->etat, 2, 2);
                            wclrtoeol(aff->etat);
                            mvwprintw(aff->etat, 1, 2, "SX: ");
                            wattroff(aff->etat, A_BOLD);
                            wattron(aff->etat, A_BOLD);
                            wprintw(aff->etat, "%d ", coup->source[ABS]);
                            wattroff(aff->etat, A_BOLD);
                            wprintw(aff->etat, "SY: ");
                            wattron(aff->etat, A_BOLD);
                            wprintw(aff->etat, "%d", coup->source[ORD]);
                            wattroff(aff->etat, A_BOLD);
                            wrefresh(aff->etat);
                        }
                        else
                        {
                            wmove(aff->etat, 1, 2);
                            wclrtoeol(aff->etat);
                            wmove(aff->etat, 2, 2);
                            wclrtoeol(aff->etat);
                            wattron(aff->etat, A_REVERSE | A_BOLD);
                            mvwprintw(aff->etat, 1, 2, "Clic invalide, cliquez sur un pion!");
                            wattroff(aff->etat, A_REVERSE | A_BOLD);
                            wrefresh(aff->etat);
                        }
                    }
                }
    if (c == 's')
    {
        sauvegarder(jeu);
        mvwprintw(aff->cimetiere, 2, 2, "PARTIE SAUVEGARDER DANS save.txt");
        wrefresh(aff->cimetiere);
    }
    } while (!clics_sont_valides);

    coup->type=get_joueur(jeu);

    return coup;
}
