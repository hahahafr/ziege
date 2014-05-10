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

    int screeny, screenx;
    int plateau_orig_y, plateau_orig_x;
    int ch;

    initscr();
    noecho();
    cbreak();

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
      screenx-TAILLE_ETAT_L);

    WINDOW *cimetiere = newwin(
      screeny/2,
      TAILLE_CIM_L,
      screeny/2,
      screenx-TAILLE_CIM_L);
    
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
    return 0;
}

int coord_jeu_vers_aff(aff_s aff, int inx, int iny, int *outy, int *outx)
{
    return 0;
}

int maj_affichage(jeu_s jeu, aff_s aff)   
{
    // itérerer sur la struscture jeu et se servir de coordjeu vers coordaffichage
    return 0;
}

int saisir_coups(aff_s aff)
{
    int c;
    MEVENT event;
    mousemask(ALL_MOUSE_EVENTS, NULL);

    do
    {
        keypad(stdscr, TRUE);
        c = getch();
        if (c == KEY_MOUSE)
            if(getmouse(&event) == OK)
                if(event.bstate & BUTTON1_CLICKED)
                {
                    mvwprintw(stdscr, 1, 2,
                      "x: %3d, y: %3d, plateau_orig_x: %d, plateau_orig_y: %d",
                      event.x,
                      event.y,
                      aff->plateau_orig_x,
                      aff->plateau_orig_y);
                    refresh();
                }
    } while (c != 'a');

    return 0;
}
