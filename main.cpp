#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// #include <iostream>
#include <ncurses.h>

#include "EasyPIO.h"

// ncursed

// EasyPIO.h maneja todo lo interno a la raspberry

using namespace std;

// Declaración de la función en ensamblador
// extern "C" void procesarOpcion(int);

const char contrasenaPreestablecida[] = "12345";

void retardo(unsigned long int);
void retardo(unsigned long int a) {
  while (a) a--;
}

void mostrar(unsigned char);
void mostrar(unsigned char dato) {
  for (unsigned char mascara = 128; mascara > 0; mascara >>= 1) {
    if (dato & mascara) {
      printf("*");
    } else {
      printf("_");
    }
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
      cout << "ESC = Frena Ejecucion" << endl;
      cout << "UP = Aumenta Velocidad" << endl;
      cout << "DOWN = Baja Velocidad" << endl;
      // cout << "Demora: " << velocidad << endl;
      mostrar(dato);
      retardo(velocidad);
      system("cls");
      dato = dato >> 1;
      printf("\n");
      if (GetAsyncKeyState(VK_ESCAPE) & 0x0001) {
        return;
      }
    }
    dato = 0x01;
    for (i = 0; i < 6; i++) {
      cout << "ESC = Frena Ejecucion" << endl;
      cout << "UP = Aumenta Velocidad" << endl;
      cout << "DOWN = Baja Velocidad" << endl;
      // cout << "Demora: " << velocidad << endl;
      dato = dato << 1;
      mostrar(dato);
      retardo(velocidad);
      system("cls");
      printf("\n");

      if (GetAsyncKeyState(VK_ESCAPE) & 0x0001) {
        return;
      }
    }
  }
}

int main() {
  int opcion = 0;
  unsigned long int velocidad = 145000000;

  ingresarContrasena();

  do {
    menu();
    cin >> opcion;
    switch (opcion) {
      case 1:
        system("cls");
        autoFantastico(velocidad);
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

  return 0;
  system("Pause");
}