#include <ui.h>

void test_tracage_plateau ()
{
    for(int y = 0; y < 27; y++)
        for(int x = 0; x < 45; x++)
            mvaddch(y, x, return_ch_plateau(y, x));
}

/*int main()
{
    initscr();
    test_tracage_plateau();
    getch();
    endwin();
    return 0;
}*/