#include <conio.h>
#include <stdio.h>
#include <windows.h>

#include <iostream>

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
      cout << "*";
    } else {
      cout << "_";
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
          printf("\b \b");
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

void auto_fantastico(unsigned long int velocidad = 1000000) {
  unsigned int dato;
  while (1) {
    dato = 0x80;
    cout << "Presione ESC para regresar al menu principal" << endl;
    cout << "Pulse la flecha para arriba para incrementar la velocidad, o "
            "para abajo para disminuirla"
         << endl;
    cout << "Demora: " << velocidad << endl;
    for (int t = 0; t < 8; t++) {
      // cout << "Presione ESC para regresar al menu principal" << endl;
      // cout << "Pulse la flecha para arriba para incrementar la velocidad, o "
      //         "para abajo para disminuirla"
      //      << endl;
      // cout << "Demora: " << velocidad << endl;
      mostrar(dato);
      retardo(velocidad);
      // system("cls");
      dato = dato >> 1;
      printf("\n");
      if (GetAsyncKeyState(VK_ESCAPE) & 0x0001) {
        return;
      }
    }
    dato = 0x01;
    for (int i = 0; i < 6; i++) {
      // cout << "Presione ESC para regresar al menu principal" << endl;
      // cout << "Pulse la flecha para arriba para incrementar la velocidad, o "
      //         "para abajo para disminuirla"
      //      << endl;
      // cout << "Demora: " << velocidad << endl;
      dato = dato << 1;
      mostrar(dato);
      retardo(velocidad);
      // system("cls");

      if (GetAsyncKeyState(VK_ESCAPE) & 0x0001) {
        return;
      }
    }
  }
}

int main() {
  int opcion = 0;
  unsigned long int velocidadAux = 145000000;
  unsigned long int velocidad = velocidadAux;

  ingresarContrasena();

  do {
    menu();
    cin >> opcion;
    switch (opcion) {
      case 1:
        system("cls");
        auto_fantastico(velocidad);
        opcion = 0;
        velocidad = velocidadAux;
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