#include "ui.h"

int
init_affichage(jeu_s jeu, aff_s * aff)
{

    // y correspond à la ligne sur laquelle sera le pion (y-1 est l'origine)
    // type 0 = 0, 2, 4, 6, 8; 1 = 1, 5; 2 = 3, 7
    void tracer_ligne(int type, WINDOW *plateau, int y)
    {
        void tracer_ligne_boite()
        {
            void tracer_trait_h(int n)
            {
                for (int i = 0; i < n; i++)
                {
                    waddch(plateau, ACS_HLINE);
                }
            }
            void tracer_boite()
            {
                wmove(plateau, getcury(plateau)-1, getcurx(plateau));
                waddch(plateau, ACS_ULCORNER);
                tracer_trait_h(3);
                waddch(plateau, ACS_URCORNER);

                wmove(plateau, getcury(plateau)+1, getcurx(plateau)-5);
                waddch(plateau, ACS_VLINE);
                wmove(plateau, getcury(plateau), getcurx(plateau)+3);
                waddch(plateau, ACS_VLINE);

                wmove(plateau, getcury(plateau)+1, getcurx(plateau)-5);
                waddch(plateau, ACS_LLCORNER);
                tracer_trait_h(3);
                waddch(plateau, ACS_LRCORNER);

                wmove(plateau, getcury(plateau)-1, getcurx(plateau));
            }
            wmove(plateau, y, 2);
            tracer_boite();
            for (int i = 0; i < 4; i++)
            {
                tracer_trait_h(5);
                tracer_boite();
            }
        }

        void tracer_ligne_diag(int type)
        {
            void tracer_l_v(int n)
            {
                for (int i = 0; i < n; i++)
                {
                    waddch(plateau, ACS_VLINE);
                    wmove(plateau, getcury(plateau)+1, getcurx(plateau)-1);
                }
            }
            void tracer_l_dd(int n)
            {
                for (int i = 0; i < n; i++)
                {
                    waddch(plateau, '\\');
                    wmove(plateau, getcury(plateau)+1, getcurx(plateau)+1);
                }
            }
            void tracer_l_dg(int n)
            {
                for (int i = 0; i < n; i++)
                {
                    waddch(plateau, '/');
                    wmove(plateau, getcury(plateau)+1, getcurx(plateau)-3);
                }
            }
            void tracer_tte_l_v()
            {
                wmove(plateau, y-1, getcurx(plateau)+2);
                tracer_l_v(3);
                for (int i = 0; i < 4; i++)
                {
                    wmove(plateau, y-1, getcurx(plateau)+10);
                    tracer_l_v(3);
                }
                wmove(plateau, y-1, 2);
            }
            void tracer_tte_l_dd_1()
            {
                wmove(plateau, y-1, getcurx(plateau)+5);
                tracer_l_dd(3);
                wmove(plateau, y-1, getcurx(plateau)+14);
                tracer_l_dd(3);
            }
            void tracer_tte_l_dd_2()
            {
                wmove(plateau, y-1, getcurx(plateau)+15);
                tracer_l_dd(3);
                wmove(plateau, y-1, getcurx(plateau)+14);
                tracer_l_dd(3);
            }
            void tracer_tte_l_dg_1()
            {
                wmove(plateau, y-1, 21);
                tracer_l_dg(3);
                wmove(plateau, y-1, 41);
                tracer_l_dg(3);
            }
            void tracer_tte_l_dg_2()
            {
                wmove(plateau, y-1, 11);
                tracer_l_dg(3);
                wmove(plateau, y-1, 31);
                tracer_l_dg(3);
            }
            if (type == 1)
            {
                tracer_tte_l_v();
                tracer_tte_l_dd_1();
                tracer_tte_l_dg_1();
            }
            else if (type == 2)
            {
                tracer_tte_l_v();
                tracer_tte_l_dd_2();
                tracer_tte_l_dg_2();
            }
        }

        if (type == 0)
        {
            tracer_ligne_boite();
        }
        else if (type == 1 || type == 2)
        {
            tracer_ligne_diag(type);
        }

    }
    initscr();
    start_color();

    init_pair(CHEVRE+1, COLOR_WHITE, COLOR_GREEN);
    init_pair(TIGRE+1, COLOR_BLACK, COLOR_RED);

    int screeny, screenx;
    int plateau_orig_y, plateau_orig_x;

    
    noecho();
    cbreak();
    curs_set(0);

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
    
    wborder(etat, ACS_VLINE, ' ', ' ', ACS_HLINE, ACS_VLINE, ' ', ACS_LTEE, ACS_HLINE); 
    wborder(cimetiere, ACS_VLINE, ' ', ' ', ' ', ACS_VLINE, ' ', ACS_VLINE, ' ');
    box(plateau, ACS_VLINE, ACS_HLINE);
    
    refresh();
    wrefresh(etat);
    wrefresh(cimetiere);
    wrefresh(plateau);

    wmove(plateau, 2, 2);
    tracer_ligne(0, plateau, getcury(plateau));
    wmove(plateau, 5, 2);
    tracer_ligne(1, plateau, getcury(plateau));
    wmove(plateau, 8, 2);
    tracer_ligne(0, plateau, getcury(plateau));
    wmove(plateau, 11, 2);
    tracer_ligne(2, plateau, getcury(plateau));
    wmove(plateau, 14, 2);
    tracer_ligne(0, plateau, getcury(plateau));
    wmove(plateau, 17, 2);
    tracer_ligne(1, plateau, getcury(plateau));
    wmove(plateau, 20, 2);
    tracer_ligne(0, plateau, getcury(plateau));
    wmove(plateau, 23, 2);
    tracer_ligne(2, plateau, getcury(plateau));
    wmove(plateau, 26, 2);
    tracer_ligne(0, plateau, getcury(plateau));

    (* aff) = (aff_s)malloc(sizeof(t_affichage_s));

    (* aff)->plateau_orig_y=plateau_orig_y;
    (* aff)->plateau_orig_x=plateau_orig_x;
    (* aff)->etat=etat;
    (* aff)->plateau=plateau;
    (* aff)->cimetiere=cimetiere;

    wrefresh(etat);
    wrefresh(cimetiere);
    wrefresh(plateau);
/*    int cpt = 0;*/
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            // i = y
            // j = x
            (* aff)->tabindcoord[i][j]=malloc(2*sizeof(int));
            (* aff)->tabindcoord[i][j][ORD]=2+plateau_orig_y+(6*i);
            (* aff)->tabindcoord[i][j][ABS]=4+plateau_orig_x+(10*j);

/*            mvprintw(cpt,0,"(* aff)->tabindcoord: %d, (* aff)->tabindcoord[%d][%d]: %d, "
              "(* aff)->tabindcoord[%d][%d][0]: %d, (* aff)->tabindcoord[%d][%d][1]: %d",
              (* aff)->tabindcoord, i, j, (* aff)->tabindcoord[i][j], i, j, (* aff)->tabindcoord[i][j][0],
              i, j, (* aff)->tabindcoord[i][j][1]);
            cpt++;*/
        }
    }

    return 0;
}

int coord_aff_vers_jeu(aff_s aff, int iny, int inx, int *outx, int *outy)
{
    int i, j;
    i = j = 0;

    int cpt = 0;
    int trouve = 0;

    while (i < PLATEAU_LARGEUR && !trouve)
    {

        j = 0;

/*                mvprintw(cpt,0, "i:%3d, j:%3d, inx:%3d, iny:%3d, aff->tabindcoord[%d][%d][ORD]:%3d"
                  " aff->tabindcoord[%d][%d][ABS]:%3d", i, j, inx, iny, i, j, aff->tabindcoord[i][j][ORD],
                  i, j, aff->tabindcoord[i][j][ABS]);
                refresh();
                cpt++;*/

        while (j < PLATEAU_HAUTEUR && !trouve)
        {
/*                mvprintw(cpt,0, "i:%3d, j:%3d, inx:%3d, iny:%3d, aff->tabindcoord[%d][%d][ORD]:%3d"
                  " aff->tabindcoord[%d][%d][ABS]:%3d", i, j, inx, iny, i, j, aff->tabindcoord[i][j][ORD],
                  i, j, aff->tabindcoord[i][j][ABS]);
                refresh();
                cpt++;*/

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

void coord_jeu_vers_aff(aff_s aff, int inx, int iny, int *outy, int *outx)
{
    *outy = (aff->tabindcoord[iny][inx][ORD])-(aff->plateau_orig_y);
    *outx = (aff->tabindcoord[iny][inx][ABS])-(aff->plateau_orig_x);
}

int maj_affichage(jeu_s jeu, aff_s aff)   
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
        wattron(aff->etat, A_REVERSE | A_BOLD);
        wprintw(aff->etat, "CHEVRES", get_joueur(jeu));
        wattroff(aff->etat, A_REVERSE | A_BOLD);
        wclrtoeol(aff->etat);
    }
    if (get_joueur(jeu) == TIGRE)
    {
        mvwprintw(aff->etat, winmaxy - 5, 2, "JOUEUR: ");
        wattron(aff->etat, A_REVERSE | A_BOLD);
        wprintw(aff->etat, "TIGRE", get_joueur(jeu));
        wattroff(aff->etat, A_REVERSE | A_BOLD);
        wclrtoeol(aff->etat);
    }

    mvwprintw(aff->etat, winmaxy - 6, 2, "CHEVRES RESTANTES:");
    wattron(aff->etat, A_BOLD);
    wprintw(aff->etat, " %d", 25-jeu->participant[TIGRE].score);
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
                mvwaddch(aff->plateau, y, x, CHEVRE_CH | COLOR_PAIR(CHEVRE+1));
                wrefresh(aff->plateau);
            }
            else if (get_pion(jeu->p,j,i) == TIGRE)
            {
                coord_jeu_vers_aff(aff, i, j, &y, &x);
                mvwaddch(aff->plateau, y, x, TIGRE_CH | COLOR_PAIR(TIGRE+1));
                wrefresh(aff->plateau);
            }
            else
            {
                coord_jeu_vers_aff(aff, i, j, &y, &x);
                mvwaddch(aff->plateau, y, x, ' ');
                wrefresh(aff->plateau);
            }
        }
    }
    return 0;
}

void jouer_ui(jeu_s jeu, aff_s aff)
{
    coup_s c;

    int x, y;

    while(!is_end(jeu))
    {
        maj_affichage(jeu, aff);
        c = saisir_coups(jeu, aff);
        jouer(jeu, c);
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

void init_player_ui(jeu_s jeu, aff_s aff)
{
    char nomj1[TAILLE_NOM];
    char nomj2[TAILLE_NOM];
    char rolej1;
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

    init_player(jeu, roleint);

    curs_set(0);
    noecho();
}

coup_s saisir_coups(jeu_s jeu, aff_s aff)
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
        wmove(aff->etat, 1, 2);
        wclrtoeol(aff->etat);
        wmove(aff->etat, 2, 2);
        wclrtoeol(aff->etat);
        wmove(aff->etat, 3, 2);
        wclrtoeol(aff->etat);
        keypad(stdscr, TRUE);
        c = getch();
        if (c == KEY_MOUSE)
            if(getmouse(&event) == OK)
                if(event.bstate & BUTTON1_CLICKED)
                {
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
    } while (!clics_sont_valides);

    coup->type=get_joueur(jeu);

    return coup;
}
