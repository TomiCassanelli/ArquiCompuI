// #include <sys/ioctl.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>

#include "EasyPIO.h"

// ncursed
// EasyPIO.h maneja todo lo interno a la raspberry

const char led[] = {14, 15, 18, 23, 24, 25, 8, 7};  // Puertos de los LEDS
int DELAY = 10;
int salir;

void mostrar(unsigned char b);
void menu();
void autoFantastico();
void choque();
void tenis();
void repiqueteo();

extern void secuenciaTenisDos(void);
extern void secuenciaTenis(void);
extern void secuenciaRepiqueteo(void);

// ---------------------------------------------------------------
//                 PATRONES PARA LAS SECUENCIAS
// ---------------------------------------------------------------
unsigned char patronElChoque[] = {
    0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81,
};

unsigned char patronAutoFantastico[] = {
    0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01,
};

unsigned char patronTenis[] = {0xC1, 0xA1, 0x91, 0x89, 0x85, 0x83, 0x83,
                               0x85, 0x89, 0x91, 0xA1, 0xC1

};

unsigned char patronRepiqueteo[] = {
    0x80, 0x40, 0x80, 0x40, 0x20, 0x40, 0x80, 0x40, 0x20, 0x10, 0x20, 0x40,
    0x80, 0x40, 0x20, 0x10, 0x08, 0x10, 0x20, 0x40, 0x80, 0x40, 0x20, 0x10,
    0x08, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04,
    0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04,
    0x02, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80,
};

// ---------------------------------------------------------------
//                     FUNCIONES CONTRASENA
// ---------------------------------------------------------------
int passwordFn() {
  initscr();
  noecho();
  int error = 0;
  char c;
  char password[] = "12345";  // Contraseña preestablecida
  char ingreso[6];  // Aumentamos el tamaño para incluir el carácter nulo

  do {
    printw("Ingrese su contraseña de 5 dígitos:\n");

    for (int i = 0; i < 5; i++) {
      c = getch();
      ingreso[i] = c;
      printw("*");
    }
    ingreso[5] = '\0';  // Agregamos el carácter nulo al final de la cadena

    if (strcmp(password, ingreso) != 0) {
      error++;
      printw("\nContraseña incorrecta. Intentos restantes: %d\n", 3 - error);
    }
  } while (error < 3 && strcmp(password, ingreso) != 0);

  echo();
  endwin();

  return strcmp(password, ingreso);
}

// ---------------------------------------------------------------
//                     FUNCIONES DE DELAY
// ---------------------------------------------------------------
int corazonDelay(int n) {
  if (DELAY < 44) {
    if (n == 0) {
      DELAY = DELAY + 4;
      return DELAY;
    }
  }
  if (DELAY > 4)
    if (n == 1) {
      DELAY = DELAY - 4;
      return DELAY;
    }
  return DELAY;
}

int retardo(int a) {
  initscr();
  noecho();
  cbreak();
  int c;
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  c = getch();
  nocbreak();
  if (c == KEY_UP) {
    a = corazonDelay(1);
  }
  if (c == KEY_DOWN) {
    a = corazonDelay(0);
  }
  if (c == 102) {  // finaliza con f, cbreak no me deja con intro
    echo();
    endwin();
    salir = 0;
    clear();
    menu();
  }
  for (int j = 0; j < a; j++) {
    unsigned int i = 0x4fffff;  // raspberry 0x3fffff
    while (i) i--;
  }
  echo();
  endwin();
  return a;
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
      onOffLed = 1;

    } else {
      charConsola = '_';
      onOffLed = 0;
    }
    printw("%c", charConsola);       // representa en la consola
    digitalWrite(led[i], onOffLed);  // representa en el led
  }
  printw("\r");
  fflush(stdout);
  endwin();
}

// ---------------------------------------------------------------
//               SECUENCIA PARA EL AUTO FANTASTICO
// ---------------------------------------------------------------
void autoFantastico() {
  for (int i = 0; i < 8; i++) {
    mostrar(patronAutoFantastico[i]);
    DELAY = retardo(DELAY);
  }
  for (int i = 7; i != 0; i--) {
    mostrar(patronAutoFantastico[i]);
    DELAY = retardo(DELAY);
  }
}

// ---------------------------------------------------------------
//                    SECUENCIA PARA EL CHOQUE
// ---------------------------------------------------------------
void choque() {
  for (int i = 0; i < 8; i++) {
    mostrar(patronElChoque[i]);
    DELAY = retardo(DELAY);
  }
}

// ---------------------------------------------------------------
//                       SECUENCIA TENIS
// ---------------------------------------------------------------
void tenis() {
  for (int i = 0; i < 12; i++) {
    mostrar(patronTenis[i]);
    DELAY = retardo(DELAY);
  }
}

// ---------------------------------------------------------------
//                     SECUENCIA REPIQUETEO
// ---------------------------------------------------------------
void repiqueteo() {
  for (int i = 0; i < 57; i++) {
    mostrar(patronRepiqueteo[i]);
    DELAY = retardo(DELAY);
  }
}

// ---------------------------------------------------------------
//                             MENU
// ---------------------------------------------------------------
void menu() {
  clear();
  salir = 1;

  char n;
  printf("\n");
  printf("    MENU DE OPCIONES\n");
  printf("***************************\n");
  printf("*   [1]- Auto Fantastico  *\n");
  printf("*   [2]- El Choque        *\n");
  printf("*   [3]- Tenis            *\n");
  printf("*   [4]- Repiqueteo       *\n");
  printf("*   [0]- Salir            *\n");
  printf("***************************\n");
  printf("\n");
  do {
    n = getchar();
    initscr();
    clear();

    switch (n) {
      case '0':
        exit(-1);
      case '1':
        clear();
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
      case '3':
        clear();
        printw("Tenis");
        printw("\nPresione f para salir\n");
        do {
          tenis();
        } while (salir);
      case '4':
        clear();
        printw("Repiqueteo");
        printw("\nPresione f para salir\n");
        do {
          repiqueteo();
        } while (salir);
      case '5':
        clear();
        printw("Tenis ASSEMBLER");
        printw("\nPresione f para salir\n");
        do {
          secuenciaTenis();
        } while (salir);
      case '6':
        clear();
        printw("Repiqueteo ASSEMBLER");
        printw("\nPresione f para salir\n");
        do {
          secuenciaRepiqueteo();
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
  pioInit();  // inicia EasyPIO
  initscr();  // Inicia ncurses
  for (int i = 0; i < 8; i++) {
    pinMode(led[i], OUTPUT);
  }

  int salir = 1;

  int resultado = passwordFn();
  if (resultado == 0) {
    printw("\nContraseña correcta. Acceso concedido.\n");
    clear();  // Actualizar la pantalla
    menu();
  } else {
    printw("\nDemasiados intentos fallidos. Acceso denegado.\n");
  }

  return 0;
}
