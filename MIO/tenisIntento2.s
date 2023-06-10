.text

.global secuenciaTenisDos

.extern mostrar
.extern retardo



secuenciaTenisDos:
      PUSH {R4-R6, LR}
    MOV R4, #0
    MOV R5, #12 ; Tamaño del patrón de tenis (12 elementos)
repite:
    LDR R6, =patronTenis
    LDRB R6, [R6,R4]
    ADD R4, R4, #1
    MOV R0, R6
    BL mostrar ; Llamada a la función mostrar
    MOV R0, DELAY
    BL retardo ; Llamada a la función retardo y guarda el resultado en R0
    MOV DELAY, R0 ; Actualiza el valor de DELAY con el resultado del retardo
    CMP DELAY, #0
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

