#include <Windows.h>
#include <stdlib.h>

#include <iostream>
#include <vector>

#include "conio.h"
#include "string.h"

using namespace std;

void delay(unsigned long int);  // da tiempo entre las luces
void mostrar(unsigned char);
int fvelocidad(unsigned long int);  // aumenta o disminuye velocidad

void auto_fantastico(unsigned long int);
void carrera(unsigned long int);
void choque(unsigned long int);
void bateriaDescargandose(unsigned long int);
void chocaLos5(unsigned long int);

int main() {
  char contrasenia[] = {'a', 'b', 'c', '1', '0'};
  char contra[20];
  string pw;
  int v = 0;
  int contador = 0, intentos = 3;

  while (intentos != 0) {
    cout << "Ingrese su contraseña: ";
    for (int i = 0; i < 5; i++) {
      v = getch();
      pw.push_back(v);
      cout << "*";
    }

    if (pw != "abc10") {
      contador++;
      intentos--;
      system("cls");
      for (int i = 0; i < 5; i++) {
        pw.pop_back();
      }
      cout << "Contrasenia incorrecta, le quedan " << intentos << " intentos"
           << endl;
    } else {
      intentos = 0;
    }
  }

  if (contador < 3) {
    // if(pw == "abc10"){
    system("cls");
    cout << "Bienvenido al sistema" << endl;
  } else {
    cout << "\nPassword no valida" << endl;
  }

  int opcion = 0;
  unsigned long int velocidadAux = 145000000;
  unsigned long int velocidad = velocidadAux;

  do {
    if (contador < 3) {
      cout << "\n(1) Autos fantastico" << endl;
      cout << "(2) La carrera" << endl;
      cout << "(3) El choque" << endl;
      cout << "(4) Bateria descargandose" << endl;
      cout << "(5) Choca los 5" << endl;
      cout << "(6) Salir" << endl;

      cout << "\nIngrese la opcion que desee visualizar: ";
      cin >> opcion;
      while (opcion < 1 || opcion > 6) {
        cout << "Valor erroneo, ingrese nuevamente: ";
        cin >> opcion;
      }

      switch (opcion) {
        case 1:
          system("cls");
          auto_fantastico(velocidad);
          opcion = 0;
          velocidad = velocidadAux;
          break;
        case 2:
          system("cls");
          carrera(velocidad);
          opcion = 0;
          velocidad = velocidadAux;
          break;
        case 3:
          system("cls");
          choque(velocidad);
          opcion = 0;
          velocidad = velocidadAux;
          break;
        case 4:
          system("cls");
          bateriaDescargandose(velocidad);
          opcion = 0;
          velocidad = velocidadAux;
          break;
        case 5:
          system("cls");
          chocaLos5(velocidad);
          opcion = 0;
          velocidad = velocidadAux;
          break;
        case 6:
          system("cls");
          cout << "Sistema apagado";
          break;
        default:
          system("cls");
          cout << "No existe secuencia para ese numero" << endl;
          opcion = 0;
      }
    }
  } while (opcion != 6);
}

void delay(unsigned long int a) {
  while (a) a--;
}

void mostrar(unsigned char dato) {
  for (unsigned char mascara = 128; mascara > 0; mascara >>= 1) {
    if (dato & mascara) {
      cout << "*";
    } else {
      cout << "_";
    }
  }
}

int fvelocidad(unsigned long int velocidad) {
  if ((velocidad - 4800000) > 9600000) {
    if (GetAsyncKeyState(VK_UP) & 0x0001) {
      velocidad -= 4800000;
    }
  }
  if (GetAsyncKeyState(VK_DOWN) & 0x0001) {
    velocidad += 4800000;
  }
  return velocidad;
}

void auto_fantastico(unsigned long int velocidad) {
  unsigned int dato;
  while (1) {
    dato = 0x80;
    for (int t = 0; t < 8; t++) {
      cout << "Presione ESC para regresar al menu principal" << endl;
      cout << "Pulse la flecha para arriba para incrementar la velocidad, o "
              "para abajo para disminuirla"
           << endl;
      cout << "Demora: " << velocidad << endl;
      mostrar(dato);
      delay(velocidad);
      system("cls");
      dato = dato >> 1;
      velocidad = fvelocidad(velocidad);
      if (GetAsyncKeyState(VK_ESCAPE) & 0x0001) {
        return;
      }
    }
    dato = 0x01;
    for (int i = 0; i < 6; i++) {
      cout << "Presione ESC para regresar al menu principal" << endl;
      cout << "Pulse la flecha para arriba para incrementar la velocidad, o "
              "para abajo para disminuirla"
           << endl;
      cout << "Demora: " << velocidad << endl;
      dato = dato << 1;
      mostrar(dato);
      delay(velocidad);
      system("cls");
      velocidad = fvelocidad(velocidad);
      if (GetAsyncKeyState(VK_ESCAPE) & 0x0001) {
        return;
      }
    }
  }
}

void carrera(unsigned long int velocidad) {
  uint8_t tabla[] = {0x80, 0x80, 0x40, 0x40, 0x20, 0x20, 0x10, 0x10,
                     0x88, 0x48, 0x24, 0x14, 0xA,  0x6,  0x3,  0x1};

  while (1) {
    for (int i = 0; i < 16; ++i) {
      cout << "Presione ESC para regresar al menu principal" << endl;
      cout << "Pulse la flecha para arriba para incrementar la velocidad, o "
              "para abajo para disminuirla"
           << endl;
      cout << "Demora: " << velocidad << endl;
      mostrar(tabla[i]);
      delay(velocidad);
      system("cls");
      velocidad = fvelocidad(velocidad);
      if (GetAsyncKeyState(VK_ESCAPE) & 0x0001) {
        return;
      }
    }
  }
}

void choque(unsigned long int velocidad) {
  uint8_t tabla[] = {0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42};

  while (1) {
    for (int i = 0; i < 7; ++i) {
      cout << "Presione ESC para volver al menu principal" << endl;
      cout << "Pulse la flecha para arriba para incrementar la velocidad, o "
              "para abajo para disminuirla"
           << endl;
      cout << "Demora: " << velocidad << endl;
      mostrar(tabla[i]);
      delay(velocidad);
      system("cls");

      velocidad = fvelocidad(velocidad);
      if (GetAsyncKeyState(VK_ESCAPE) & 0x0001) {
        return;
      }
    }
  }
}

void bateriaDescargandose(unsigned long int velocidad) {
  unsigned int dato = 0xFF;
  while (1) {
    for (int i = 0; i < 9; ++i) {
      cout << "Presione ESC para regresar al menu principal" << endl;
      cout << "Demora: " << velocidad << endl;
      mostrar(dato);
      dato <<= 1;
      delay(velocidad);
      system("cls");

      velocidad = fvelocidad(velocidad);
      if (GetAsyncKeyState(VK_ESCAPE) & 0x0001) {
        return;
      }
    }
    dato = 0xFF;
  }
}

void chocaLos5(unsigned long int velocidad) {
  unsigned char tabla[] = {0x0, 0x81, 0xC3, 0xE7, 0xFF, 0xE7, 0xC3, 0x81};
  while (1) {
    for (int i = 0; i < 8; i++) {
      cout << "Presione ESC para regresar al menu principal" << endl;
      cout << "Pulse la flecha para arriba para incrementar la velocidad, o "
              "para abajo para disminuirla"
           << endl;
      cout << "Demora: " << velocidad << endl;
      mostrar(tabla[i]);
      delay(velocidad);
      system("cls");

      velocidad = fvelocidad(velocidad);
      if (GetAsyncKeyState(VK_ESCAPE) & 0x0001) {
        return;
      }
    }
  }
}