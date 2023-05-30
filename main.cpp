#include <conio.h>
#include <stdio.h>
#include <windows.h>

#include <iostream>

using namespace std;

// Declaración de la función en ensamblador
// extern "C" void procesarOpcion(int);

const char contrasenaPreestablecida[] = "12345";

void menu();
void menu() {
  cout << endl;
  cout << "   MENU DE OPCIONES" << endl;
  cout << "***********************" << endl;
  cout << "*   [1]- OPCION 1     *" << endl;
  cout << "*   [2]- OPCION 2     *" << endl;
  cout << "*   [3]- OPCION 3     *" << endl;
  cout << "*   [4]- OPCION 4     *" << endl;
  cout << "*   [5]- OPCION 5     *" << endl;
  cout << "*   [0]- OPCION 0     *" << endl;
  cout << "***********************" << endl;
  cout << endl;
}

// void displayLights(int lights) {
//   for (int i = 0; i < 8; i++) {
//     if ((lights >> i) & 1)
//       std::cout << "*";
//     else
//       std::cout << "_";
//   }
//   std::cout << std::endl;
// }

void ingresarContrasena() {
  char contrasenaIngresada[6];
  int intentos = 3;

  while (intentos > 0) {
    cout << "Ingrese la contrasena de 5 digitos: ";
    cin >> contrasenaIngresada;

    // for (int i = 0; i < 5; ++i) {
    //   contrasenaIngresada[i] = getch();
    //   cout << "*";
    // }
    // contrasenaIngresada[5] = '\0';

    cout << endl;

    if (strlen(contrasenaIngresada) != 5) {
      cout << "La contrasena debe tener exactamente 5 digitos." << endl;
    }

    if (strcmp(contrasenaIngresada, contrasenaPreestablecida) == 0) {
      return;
    }

    cout << "Contrasena incorrecta. Intentos restantes: " << intentos-- << endl;
  }
  cout << "Has excedido el numero maximo de intentos. Abortando." << endl;
  exit(0);  // Se detiene el programa
}

int main() {
  int opcion = 0;

  ingresarContrasena();

  do {
    menu();
    cin >> opcion;
    switch (opcion) {
      case 1:
        //         const int DELAY_MS = 200;

        // int lights = 1;
        // int direction = 1;

        // while (true) {
        //   displayLights(lights);

        //   if (lights == 128)
        //     direction = -1;
        //   else if (lights == 1)
        //     direction = 1;

        //   lights <<= direction;
        //    std::this_thread::sleep_for(std::chrono::milliseconds(DELAY_MS));
        //   system("cls"); // Para limpiar la pantalla en Windows,
        //   utiliza "clear"
        //         }
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