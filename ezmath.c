#include <stdlib.h>
#include <ncurses.h>

void clearlinetoline(int ln1, int ln2) {
  for (int i = ln1; i <= ln2; i++) {
    move(i, 0); clrtoeol();
  }
}

int main() {
  float options[] = {0, 0};
  int highlight = 0, ch;

  initscr();
  noecho();
  cbreak();
  curs_set(0);
  keypad(stdscr, TRUE);

  while (1) {
    for (int i = 0; i < 2; i++) {
      if (i == highlight) attron(A_REVERSE);
      mvprintw(i, 0, "%.2f", options[i]);
      attroff(A_REVERSE);
    }

    clearlinetoline(3, 6);
    mvprintw(3, 0, "SUM(+): %.3f", options[0]+options[1]);
    mvprintw(4, 0, "DIF(-): %.3f", options[0]-options[1]);
    mvprintw(5, 0, "PRO(x): %.3f", options[0]*options[1]);
    mvprintw(6, 0, "QUO(/): %.3f", options[0]/options[1]);

    refresh();

    ch = getch();

    switch (ch) {
      case KEY_UP:
        highlight = (highlight + 1) % 2;
        break;
      case KEY_DOWN:
        highlight = (highlight + 1) % 2;
        break;
      case '\n':
        echo();
        curs_set(1);
        char input[10];
        move(highlight, 0);
        clrtoeol();
        getnstr(input, 10); 
        options[highlight] = atof(input); 
        noecho();
        curs_set(0);
        break;
      case 'q':
        goto exit;
    }
  }
exit:
  endwin();
  return 0;
}
