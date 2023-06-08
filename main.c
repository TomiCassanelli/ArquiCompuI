#include <conio.h>
// #include <ncurses.h>
#include <dos.h>
#include <stdio.h>

#include "EasyPIO.h"
#define port_out 0x208
#define port_in 0x209
//
void disp_binary(int);
void delay(int);
//
void main(void) {
  unsigned char output;
  char t;
  int on_time; /* set holding time */
  printf("secuencia en acción ... Oprima una tecla para finalizar\n");
  do {
    output = 0x80;
    for (t = 0; t < 8; t++) {
      on_time = inportb(port_in);  /* Read from DIP switches */
      outportb(port_out, ~output); /* Turn LEDs on */
      disp_binary(output);
      delay(on_time);       /* Wait a while */
      output = output >> 1; /* Shift bits to lower positions */
    }
    output = 0x01;
    for (t = 0; t < 6; t++) {
      output = output << 1;
      on_time = inportb(port_in);
      outportb(port_out, ~output);
      disp_binary(output);
      delay(on_time);
    }
  } while (!kbhit()); /* Repeat loop until the keyboard is hit */
  output = 0x00;
  outportb(port_out, ~output);
  disp_binary(output);
  printf("chau... !\n");
}
void delay(int time) {
  int i;
  unsigned int j;
  for (i = time; i > 0; --i) /* repeat specified number of times */
    for (j = 0; j < 65535; ++j)
      ;
}
void disp_binary(int i) {
  int t;
  for (t = 128; t > 0; t = t / 2)
    if (i & t)
      printf("1 ");
    else
      printf("0 ");
  printf("\n");
}