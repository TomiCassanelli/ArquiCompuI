#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "EasyPIO.h"

// ncursed
// EasyPIO.h maneja todo lo interno a la raspberry

const char led[] = {14, 15, 18, 23, 24, 25, 8, 7};  // Puertos de los LEDS
const char password[] = "12345";  // Contraseña preestablecida
int DELAY = 50;
const int DELAYSUPERIOR = 100;
const int DELAYINFERIOR = 0;
const int CAMBIODELAY = 5;

void mostrar(unsigned char b);
void menu();
void autoFantastico(int* delay);
void choque(int* delay);
void carrera(int* delay);
void pingPong(int* delay);
void repiqueteo(int* delay);

// extern void secuenciaPingPong(void);
// extern void secuenciaPingPong(int* delay);
// extern void secuenciaRepiqueteo(int* delay);

// ---------------------------------------------------------------
//                 PATRONES PARA LAS SECUENCIAS
// ---------------------------------------------------------------
// En estos patrones se representan los numeros binarios en hexadecimales
// generando asi una secuencia

unsigned char patronAutoFantastico[] = {
    0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01,
};
// 10000000
// 01000000
// 00100000
// 00010000
// 00001000
// 00000100
// 00000010
// 00000001

unsigned char patronElChoque[] = {
    0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81,
};
// 10000001
// 01000010
// 00100100
// 00011000
// 00011000
// 00100100
// 01000010
// 10000001

unsigned char patronCarrera[] = {
    0x80, 0x80, 0x40, 0x40, 0x20, 0x20, 0x10, 0x10,
    0x88, 0x48, 0x24, 0x14, 0x0A, 0x06, 0x03, 0x01,
};

unsigned char patronPingPong[] = {0xC1, 0xA1, 0x91, 0x89, 0x85, 0x83,
                               0x83, 0x85, 0x89, 0x91, 0xA1, 0xC1};
// 11000001
// 10100001
// 10010001
// 10001001
// 10000101
// 10000011
// 10000101
// 10001001
// 10010001
// 10100001
// 11000001

unsigned char patronRepiqueteo[] = {
    0x80, 0x40, 0x80, 0x40, 0x20, 0x40, 0x80, 0x40, 0x20, 0x10, 0x20, 0x40,
    0x80, 0x40, 0x20, 0x10, 0x08, 0x10, 0x20, 0x40, 0x80, 0x40, 0x20, 0x10,
    0x08, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04,
    0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04,
    0x02, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80,
};
// 10000000
// 01000000
// 10000000
// 01000000
// 00100000
// 01000000
// 10000000
// 01000000
// 00100000
// 00010000
// 00100000
// 01000000
// 10000000
// 01000000
// 00100000
// 00010000
// 00001000

// ---------------------------------------------------------------
//                     FUNCIONES CONTRASENA
// ---------------------------------------------------------------
// En este caso implementamos una contraseña ya establecida constante, y se
// utiliza la funcion noecho para no mostrar los numeros que se muestran,
// entonces con solo indicar con getch que se uso esa tecla inserta el *

int passwordFn() {
  noecho();
  int error = 0;
  char tecla;
  char passIngresada[5];

  do {
    printw("Ingrese su contraseña de 5 dígitos:\n");

    for (int i = 0; i < 5; i++) {
      tecla = getch();
      passIngresada[i] = tecla;
      printw("*");
    }

    if (strcmp(password, passIngresada) != 0) {
      error++;
      printw("\nContraseña incorrecta. Intentos restantes: %d\n", 3 - error);
    }
  } while (error < 3 && strcmp(password, passIngresada) != 0);

  echo();

  return strcmp(password, passIngresada);
}

// ---------------------------------------------------------------
//                     FUNCIONES DE DELAY
// ---------------------------------------------------------------

int ajustarDelay(int n, int cambiaDelay) {
  if (cambiaDelay < DELAYSUPERIOR && n == 0) {
    cambiaDelay += CAMBIODELAY;
    if (cambiaDelay > DELAYSUPERIOR) {
      cambiaDelay = DELAYSUPERIOR;  // Ajustar al límite superior
    }
    return cambiaDelay;
  }

  if (cambiaDelay > DELAYINFERIOR && n == 1) {
    cambiaDelay -= CAMBIODELAY;
    if (cambiaDelay < DELAYINFERIOR) {
      cambiaDelay = DELAYINFERIOR;  // Ajustar al límite inferior
    }
    return cambiaDelay;
  }

  return cambiaDelay;
}

int controles(int numDelay) {
  int salir = 1;
  noecho();
  cbreak();

  int tecla;
  keypad(stdscr, TRUE);

  timeout(15);

  tecla = getch();

  nocbreak();

  switch (tecla) {
    case KEY_UP: // ↑ key
      numDelay = ajustarDelay(1, numDelay);
      break;

    case KEY_DOWN: // ↓ key
      numDelay = ajustarDelay(0, numDelay);
      break;

    case 27:  // ESC key
      echo();
      salir = 0;
      menu();
      break;
  }

  // pausa la ejecución por 15 milisegundos, controla la velocidad de respuesta
  for (int i = 0; i < numDelay; i++) {
    napms(10);
  }

  echo();

  return numDelay;
}

// ---------------------------------------------------------------
//                FUNCION PARA MOSTRAR LED O CARACTER
// ---------------------------------------------------------------
void mostrar(unsigned char bit) {
  for (int i = 7; i >= 0; --i) {
    char charConsole;

    if (bit & (1 << i)) {
      charConsole = '*';
    } else {
      charConsole = '_';
    }

    printw("%c", charConsole);                 // representa en la consola
    digitalWrite(led[i], charConsole == '*');  // representa en los leds
  }
  printw("\r");
}

// ---------------------------------------------------------------
//               SECUENCIA PARA EL AUTO FANTASTICO
// ---------------------------------------------------------------
void autoFantastico(int* delay) {
  for (int i = 0; i < 8; i++) {
    mostrar(patronAutoFantastico[i]);
    *delay = controles(*delay);
  }
  for (int i = 7; i != 0; i--) {
    mostrar(patronAutoFantastico[i]);
    *delay = controles(*delay);
  }
}

// ---------------------------------------------------------------
//                    SECUENCIA PARA EL CHOQUE
// ---------------------------------------------------------------
void choque(int* delay) {
  for (int i = 0; i < 8; i++) {
    mostrar(patronElChoque[i]);
    *delay = controles(*delay);
  }
}

// ---------------------------------------------------------------
//                   SECUENCIA PARA LA CARRERA
// ---------------------------------------------------------------
void carrera(int* delay) {
  for (int i = 0; i < 16; i++) {
    mostrar(patronCarrera[i]);
    *delay = controles(*delay);
  }
}

// ---------------------------------------------------------------
//                       SECUENCIA TENIS
// ---------------------------------------------------------------
void pingPong(int* delay) {
  for (int i = 0; i < 12; i++) {
    mostrar(patronPingPong[i]);
    *delay = controles(*delay);
  }
}

// ---------------------------------------------------------------
//                     SECUENCIA REPIQUETEO
// ---------------------------------------------------------------
void repiqueteo(int* delay) {
  for (int i = 0; i < 57; i++) {
    mostrar(patronRepiqueteo[i]);
    *delay = controles(*delay);
  }
}

// ---------------------------------------------------------------
//                             MENU
// ---------------------------------------------------------------
void menu() {
  int delay = DELAY;
  int salir = 1;
  noecho();

  char option;
  refresh();
  clear();

  do {
    printw("\n");
    printw("      MENU DE OPCIONES\n");
    printw("***************************\n");
    printw("*   [1]- Auto Fantastico  *\n");
    printw("*   [2]- El Choque        *\n");
    printw("*   [3]- Carrera          *\n");
    printw("*   [4]- Ping Pong        *\n");
    printw("*   [5]- Repiqueteo       *\n");
    printw("*   [0]- Salir            *\n");
    printw("***************************\n");
    printw(" ESC <- Finaliza Secuencia\n");
    printw("\n");
    printw("\n");
    printw("\n");
    option = getch();

    switch (option) {
      case '0':
        exit(-1);
      case '1':
        printw("***************************\n");
        printw("*     AUTO FANTASTICO     *\n");
        printw("***************************\n");
        do {
          autoFantastico(&delay);
        } while (salir);
        break;
      case '2':
        printw("***************************\n");
        printw("*          CHOQUE         *\n");
        printw("***************************\n");
        do {
          choque(&delay);
        } while (salir);
        break;
      case '3':
        printw("***************************\n");
        printw("*         CARRERA         *\n");
        printw("***************************\n");
        do {
          carrera(&delay);
        } while (salir);
        break;
      case '4':
        printw("***************************\n");
        printw("*        PING PONG        *\n");
        printw("***************************\n");
        do {
          pingPong(&delay);
        } while (salir);

        break;
      case '5':
        printw("***************************\n");
        printw("*        REPIQUETEO       *\n");
        printw("***************************\n");
        do {
          repiqueteo(&delay);
        } while (salir);

        break;
      case '6':
        printw("***************************\n");
        printw("*   PING PONG ASSEMBLER   *\n");
        printw("***************************\n");
        // do {
        // secuenciaPingPong(&delay);
        // } while (salir);

        break;
      case '7':
        printw("***************************\n");
        printw("*   REPIQUETEO ASSEMBLER  *\n");
        printw("***************************\n");
        // do {
        // secuenciaRepiqueteo(&delay);
        // } while (salir);

      default:
        break;
    }
    clear();
  } while (TRUE);
}

// ---------------------------------------------------------------
//                       FUNCION PRINCIPAL
// ---------------------------------------------------------------
int main() {
  pioInit();  // inicia EasyPIO
  initscr();  // Inicia ncurses
  clear();
  for (int i = 0; i < 8; i++) {
    pinMode(led[i], OUTPUT);
  }

  int salir = 1;
  int login = passwordFn();

  if (login == 0) {
    printw("\nContraseña correcta. Acceso concedido.\n");
    clear();  // Actualizar la pantalla
    menu();
  } else {
    printw("\nDemasiados intentos fallidos. Acceso denegado.\n");
  }

  endwin();

  return 0;
}
