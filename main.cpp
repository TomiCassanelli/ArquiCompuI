// #include <stdio.h>
// #include <Windows.h>
// #include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

// #include "EasyPIO.h"
#include "conio.h"

// ncursed
// EasyPIO.h maneja todo lo interno a la raspberry

using namespace std;

const char contrasenaPreestablecida[] = "12345";
const char led[] = {7, 8, 25, 24, 23, 18, 15, 14};

void delay(unsigned long int);
void delay(unsigned long int a) {
  while (a) a--;
}

void mostrar(unsigned char);
void mostrar(unsigned char dato) {
  for (unsigned char tamano = 128; tamano > 0; tamano >>= 1) {
    if (dato & tamano) {
      printf("*");
    } else {
      printf("_");
    }
  }
}

void mostrarLED(unsigned char);
void mostrarLED(unsigned char b) {
  for (int i = 7; i >= 0; --i) {
    char tmp = (b & (1 << i)) ? '*' : '_';
    int status = (b & (1 << i)) ? 0 : 1;
    // digitalWrite(led[i], status);
  }
}

void menu();
void menu() {
  printf("\n");
  printf("   MENU DE OPCIONES\n");
  printf("***********************\n");
  printf("*   [1]- OPCION 1     *\n");
  printf("*   [2]- OPCION 2     *\n");
  printf("*   [3]- OPCION 3     *\n");
  printf("*   [4]- OPCION 4     *\n");
  printf("*   [5]- OPCION 5     *\n");
  printf("*   [0]- OPCION 0     *\n");
  printf("***********************\n");
  printf("\n");
}

void ingresarContrasena() {
  char contrasenaPreestablecida[] = "12345";
  char contrasenaIngresada[6];
  int intentos = 3;

  while (intentos > 0) {
    printf("Ingrese la contrasena de 5 digitos: ");

    char caracter;
    int posicion = 0;

    while ((caracter = getch()) != '\r') {
      if (caracter != '\b') {
        contrasenaIngresada[posicion++] = caracter;
        printf("*");
      } else {
        if (posicion > 0) {
          printf("\b \b");  // permite el borrado
          posicion--;
        }
      }
    }
    contrasenaIngresada[posicion] = '\0';
    printf("\n");

    if (strlen(contrasenaIngresada) != 5) {
      printf("La contrasena debe tener exactamente 5 digitos.\n");
    }

    if (strcmp(contrasenaIngresada, contrasenaPreestablecida) == 0) {
      return;
    }
    printf("Contrasena incorrecta. Intentos restantes: %d\n", --intentos);
  }
  printf("Has excedido el numero maximo de intentos. Adios!.\n");
  exit(0);
}

void autoFantastico(unsigned long int velocidad = 10000000) {
  unsigned int dato, t, i;
  cout << endl;
  while (1) {
    dato = 0x80;
    for (t = 0; t < 8; t++) {
      mostrar(dato);
      mostrarLED(dato);
      delay(velocidad);
      system("cls");
      dato = dato >> 1;
      printf("\n");
      if (GetAsyncKeyState(VK_ESCAPE) & 0x0001) {
        return;
      }
    }
    dato = 0x01;
    for (i = 0; i < 6; i++) {
      mostrar(dato);
      mostrarLED(dato);
      delay(velocidad);
      system("cls");
      dato = dato << 1;
      printf("\n");
      if (GetAsyncKeyState(VK_ESCAPE) & 0x0001) {
        return;
      }
    }
  }
}

int main() {
  // initscr();  // inicia la biblioteca ncurses
  // echo();     // habilita la eco automatica de caracteres ingresados
  // noecho();   // la deshabilita, la uso para cuando comience alguna rutina
  // uso printw en vez de printf
  int opcion = 0, exit = 1;
  // pioInit();
  unsigned long int velocidad = 145000000;

  // ingresarContrasena();

  do {
    menu();
    cin >> opcion;
    switch (opcion) {
      case 1:
        system("cls");
        do {
          autoFantastico(velocidad);
        } while (exit);

        opcion = 0;
        break;
      case 2:
        /* code */
        break;
      case 3:
        /* code */
        break;
      case 4:
        /* code */
        break;

      default:
        break;
    }
  } while (opcion != 0);

  // endwin();  // Finalizar y cerrar la ventana ncurses
  return 0;

  system("Pause");
}