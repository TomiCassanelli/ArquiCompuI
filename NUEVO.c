#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>

#include "EasyPIO.h"

// ncursed
// EasyPIO.h maneja todo lo interno a la raspberry

const char password[] = "12345";
const char led[] = {14, 15, 18, 23, 24, 25, 8, 7};  // Puertos de los LEDS
int DELAY = 500;
int salir;

void mostrar(unsigned char b);
void menu();
void autoFantastico();
void choque();
void tenis();

// ---------------------------------------------------------------
//                 PATRONES PARA LAS SECUENCIAS
// ---------------------------------------------------------------
unsigned char patronElChoque[] = {
    0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81,
};

unsigned char patronAutoFantastico[] = {
    0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01,
};

unsigned char patronTenis[] = {
    0x81, 0xC1, 0xA1, 0x91, 0x89, 0x85, 0x83,
    0x83, 0x85, 0x89, 0x91, 0xA1, 0xC1,
};

// ---------------------------------------------------------------
//                     FUNCIONES DE DELAY
// ---------------------------------------------------------------

// int tomadelay(int n) {
//   if (DELAY < 44) {
//     if (n == 0) {
//       DELAY = DELAY + 4;
//       return DELAY;
//     }
//   }
//   if (DELAY > 4)
//     if (n == 1) {
//       DELAY = DELAY - 4;
//       return DELAY;
//     }
//   return DELAY;
// }

// int delayc(int a) {
//   initscr();
//   noecho();
//   cbreak();
//   int c;
//   keypad(stdscr, TRUE);
//   nodelay(stdscr, TRUE);
//   c = getch();
//   nocbreak();
//   if (c == KEY_UP) {
//     a = tomadelay(1);
//   }
//   if (c == KEY_DOWN) {
//     a = tomadelay(0);
//   }
//   if (c == 102) {  // finaliza con f, cbreak no me deja con intro
//     echo();
//     endwin();
//     ejec = 0;
//     menu();
//   }
//   for (int j = 0; j < a; j++) {
//     unsigned int i = 0x4fffff;  // raspberry 0x3fffff
//     while (i) i--;
//   }
//   echo();
//   endwin();
//   return a;
// }

int delayc(void) {
  // timeout(0);
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  int c = getch();

  if (c != ERR) {
    if (c == KEY_UP) {
      DELAY -= 50;
      if (DELAY < 50) {
        DELAY = 50;
        return 0;
      }
    } else if (c == KEY_DOWN) {
      DELAY += 50;
      if (DELAY > 2000) {
        DELAY = 2000;
        return 0;
      }
    }
    return 1;
  } else {
    salir = 0;
    return 0;
  }
}

// ---------------------------------------------------------------
//                FUNCION PARA MOSTRAR LED O CARACTER
// ---------------------------------------------------------------
void mostrar(unsigned char dato) {
  initscr();

  for (int i = 7; i >= 0; --i) {
    char charConsola;
    int onOffLed;

    if (dato & (1 << i)) {
      charConsola = '*';
      onOffLed = 0;

    } else {
      charConsola = '_';
      onOffLed = 1;
    }
    printw("%c", charConsola);           // representa en la consola
    /*digitalWrite(led[i], onOffLed);*/  // representa en el led
  }
  printw("\r");
  fflush(stdout);
  endwin();
}

// void mostrar(unsigned char b) {
//   initscr();
//   for (int i = 8; i > 0; i--) {
//     if ((b & 1) == 1) {
//       printw("*");
//     } else
//       printw("_");
//     b = b >> 1;
//   }
//   printw("\r");
//   fflush(stdout);
//   endwin();
// }

// void mostrarLED(unsigned char b) {
//   for (int i = 7; i >= 0; --i) {
//     char tmp = (b & (1 << i)) ? '*' : '_';
//     int onOffLed = (b & (1 << i)) ? 1 : 0;
//     digitalWrite(led[i], onOffLed);
//   }
// }

// ---------------------------------------------------------------
//               SECUENCIA PARA EL AUTO FANTASTICO
// ---------------------------------------------------------------
void autoFantastico() {
  for (int i = 0; i < 8; i++) {
    mostrar(patronAutoFantastico[i]);
    DELAY = delayc();
  }
  for (int i = 7; i != 0; i--) {
    mostrar(patronAutoFantastico[i]);
    DELAY = delayc();
  }
}

// ---------------------------------------------------------------
//                    SECUENCIA PARA EL CHOQUE
// ---------------------------------------------------------------
void choque() {
  for (int i = 0; i < 8; i++) {
    mostrar(patronElChoque[i]);
    DELAY = delayc();
  }
}

// ---------------------------------------------------------------
//                     SECUENCIA PROPIA TENIS
// ---------------------------------------------------------------
void tenis() {
  for (int i = 0; i < 13; i++) {
    mostrar(patronTenis[i]);
    DELAY = delayc();
  }
}

// ---------------------------------------------------------------
//                             MENU
// ---------------------------------------------------------------
void menu() {
  printf("\n");
  printf("    MENU DE OPCIONES\n");
  printf("***************************\n");
  printf("*   [1]- Auto Fantastico  *\n");
  printf("*   [2]- El Choque        *\n");
  printf("*   [3]- OPCION 3         *\n");
  printf("*   [4]- OPCION 4         *\n");
  printf("*   [5]- OPCION 5         *\n");
  printf("*   [0]- OPCION 0         *\n");
  printf("***************************\n");
  printf("\n");

  salir = 1;
  char caracter;

  /*scanf("%d", &opcion);*/

  char n = getchar();
  initscr();
  clear();
  do {
    switch (n) {
      case '0':
        exit(-1);
      case '1':
        printw("Auto fantastico");
        printw("\nPresione f para salir\n");
        do {
          autoFantastico();
        } while (salir);
      case '2':
        clear();
        printw("El choque");
        printw("\nPresione f para salir\n");
        do {
          choque();
        } while (salir);

      default:
        break;
    }
  } while (TRUE);
}

// ---------------------------------------------------------------
//                       FUNCION PRINCIPAL
// ---------------------------------------------------------------
int main() {
  // pioInit();
  /*for (int i = 0; i < 8; i++) {
  pinMode(led[i], OUTPUT);
  }*/

  int salir = 1;

  menu();

  return 0;
}
