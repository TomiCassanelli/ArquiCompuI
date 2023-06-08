// prj.s
// 22 de Mayo de 2019
// Arqui I UCC
.text

.extern outputLED
.extern delayass
.global init_carrera



init_carrera:
    PUSH {R4-R6, LR}
    MOV R4, #0
    MOV R5, #20
repite:
     LDR R6, = array
     LDRB R6, [R6,R4]
     ADD R4, R4, #1
     MOV R0, R6
     BL outputLED
     MOV R0, R5
     BL delayass
     MOV R5, R0
     CMP R5, #0
     BEQ salida
     BNE repite
salida:
     POP {R4-R6, PC}
.data
array:
      .byte 0x80
      .byte 0x80
      .byte 0x40
      .byte 0x40
      .byte 0x20
      .byte 0x20
      .byte 0x10
      .byte 0x10
      .byte 0x88
      .byte 0x48
      .byte 0x24
      .byte 0x14
      .byte 0x0A
      .byte 0x06
      .byte 0x03
      .byte 0x01
.end


/*
gcc main.c -lncurses -o main
gcc -g carrera2.s -o prueba1

-g
-o es para generar con el nombre prueba1


debugger: ddd nombre.s, pongo breakpoints en main y done

*/

