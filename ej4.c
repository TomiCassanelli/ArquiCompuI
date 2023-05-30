#include <stdio.h>
#include <windows.h>

void disp_binary(int);
void delay(int);

void delay(int time) {
  Sleep(time);  // Utiliza la función Sleep de windows.h para pausar el programa
}

// void disp_binary(int i) {
//   int t;
//   for (t = 128; t > 0; t = t / 2)
//     if (i & t)
//       printf("*");
//     else
//       printf("_");
//   printf("\n");
// }

void disp_binary(int i) {
  unsigned char valor[7]={0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42};
  for (i = 0; i < 6; i++)
   disp_binary(valor[i]);
}

int main(void) {
  unsigned char output;
  char t;
  int on_time;

  HANDLE hOut =
      GetStdHandle(STD_OUTPUT_HANDLE);  // Obtener el handle de la consola

  printf("secuencia en accion... Oprima una tecla para finalizar\n");

  do {
    output = 0x80;
    for (t = 0; t < 8; t++) {
      on_time = 1000;  // Valor de tiempo arbitrario para ejemplificar
      disp_binary(output);
      delay(on_time);
      output = output >> 1;
    }
    output = 0x01;
    for (t = 0; t < 6; t++) {
      output = output << 1;
      on_time = 1000;  // Valor de tiempo arbitrario para ejemplificar
      disp_binary(output);
      delay(on_time);
    }
  } while (!_kbhit());  // Utiliza _kbhit() en lugar de kbhit()

  output = 0x00;

  disp_binary(output);
  printf("chau... !\n");

  return 0;
}
