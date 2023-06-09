// #include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <sys/ioctl.h>
// #include <termios.h>
// #include "EasyPIO.h"

// ncursed
// EasyPIO.h maneja todo lo interno a la raspberry

const char password[] = "12345";
const char led[] = {14, 15, 18, 23, 24, 25, 8, 7};  // Puertos de los LEDS
int DELAY = 100;
int salir;

void mostrar(unsigned char);
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

// int tomadelay(int n) {
//   if (n == 0) {
//     DELAY += 4;
//     if (DELAY > 44) {
//       DELAY = 44;  // Límite superior de DELAY
//     }
//   } else if (n == 1) {
//     DELAY -= 4;
//     if (DELAY < 4) {
//       DELAY = 4;  // Límite inferior de DELAY
//     }
//   }
//   return DELAY;
// }

// int delayc(int a) {
//   // initscr();
//   // noecho();
//   // cbreak();
//   int c;
//   // keypad(stdscr, TRUE);
//   // nodelay(stdscr, TRUE);
//   /*c = getch();*/ c = getchar();

//   // nocbreak();
//   if (c == /*KEY_UP*/ 27) {
//     a = tomadelay(1);
//   }
//   if (c == /*KEY_DOWN*/ 26) {
//     a = tomadelay(0);
//   }
//   if (c == 102) {  // finaliza con f, cbreak no me deja con intro
//     // echo();
//     // endwin();
//     salir = 0;
//     menu();
//   }
//   // for (int j = 0; j < a; j++) {
//   //   unsigned int i = 0x4fffff;  // raspberry 0x3fffff
//   //   while (i) i--;
//   // }
//   // echo();
//   // endwin();
//   return a;
// }

// void delay(unsigned long int a) {
//   while (a) a--;
// }

// ---------------------------------------------------------------
//                FUNCION PARA MOSTRAR LED O CARACTER
// ---------------------------------------------------------------
void mostrar(unsigned char dato) {
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
    printf("%c", charConsola);  // representa en la consola
    // digitalWrite(led[i], onOffLed);  // representa en el led
  }
  printf("\r");
}

// ---------------------------------------------------------------
//               SECUENCIA PARA EL AUTO FANTASTICO
// ---------------------------------------------------------------
void autoFantastico() {
  unsigned long int velocidad = 0;  // Inicializar velocidad
  for (int i = 0; i < 8; i++) {
    mostrar(patronAutoFantastico[i]);
    // DELAY = delayc(DELAY);
  }
  for (int i = 7; i != 0; i--) {
    mostrar(patronAutoFantastico[i]);
    // DELAY = delayc(DELAY);
  }
}

// ---------------------------------------------------------------
//                    SECUENCIA PARA EL CHOQUE
// ---------------------------------------------------------------
void choque() {
  for (int i = 0; i < 8; i++) {
    mostrar(patronElChoque[i]);
    // DELAY = delayc(DELAY);
  }
}

// ---------------------------------------------------------------
//                     SECUENCIA PROPIA TENIS
// ---------------------------------------------------------------
void tenis() {
  for (int i = 0; i < 13; i++) {
    mostrar(patronTenis[i]);
    // DELAY = delayc(DELAY);
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
}

// ---------------------------------------------------------------
//                       FUNCION PRINCIPAL
// ---------------------------------------------------------------
int main() {
  // pioInit();
  // for (int i = 0; i < 8; i++) {
  // pinMode(led[i], OUTPUT);
  // }

  int opcion = 0, salir = 1;

  do {
    menu();
    scanf("%d", &opcion);

    // initscr();
    // clear();
    switch (opcion) {
      case 1:
        // clear();
        printf("Auto fantastico\n");
        printf("Si apretas ESC, salis\n");
        do {
          autoFantastico();
        } while (salir);
        break;
      case 2:
        // clear();
        printf("El choque\n");
        printf("Si apretas ESC, salis\n");
        do {
          choque();
        } while (salir);
        break;
      case 3:
        // clear();
        printf("Tenis\n");
        printf("Si apretas ESC, salis\n");
        do {
          choque();
        } while (salir);
        break;

      case 4:
        /* code */
        break;

      default:
        break;
    }
  } while (opcion != 0);

  return 0;
  system("Pause");
}