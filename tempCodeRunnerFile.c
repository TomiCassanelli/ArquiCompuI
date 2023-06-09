int delayc(int a) {
  // initscr();
  // noecho();
  // cbreak();
  int c;
  // keypad(stdscr, TRUE);
  // nodelay(stdscr, TRUE);
  c = getch(); /*c = getchar();*/

  // nocbreak();
  if (c == /*KEY_UP*/ 27) {
    a = tomadelay(1);
  }
  if (c == /*KEY_DOWN*/ 26) {
    a = tomadelay(0);
  }
  if (c == 102) {  // finaliza con f, cbreak no me deja con intro
    // echo();
    // endwin();
    salir = 0;
    menu();
  }
  // for (int j = 0; j < a; j++) {
  //   unsigned int i = 0x4fffff;  // raspberry 0x3fffff
  //   while (i) i--;
  // }
  // echo();
  // endwin();
  return a;
}