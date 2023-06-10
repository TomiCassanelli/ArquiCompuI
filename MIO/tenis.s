.text

.global secuenciaTenis

.extern mostrar
.extern retardo



secuenciaTenis:
    PUSH {R4-R6, LR}
    MOV R4, #0
    MOV R5, #12
repite:
    LDRB R6, =array
    LDRB R6, [R6,R4]
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
.data array:
      .byte 0xC1, 0xA1, 0x91, 0x89, 0x85, 0x83, 0x83, 0x85, 0x89, 0x91, 0xA1, 0xC1
.end


/*
gcc main.c -lncurses -o main
gcc -g carrera2.s -o prueba1

-g
-o es para generar con el nombre prueba1


debugger: ddd nombre.s, pongo breakpoints en main y done

*/

