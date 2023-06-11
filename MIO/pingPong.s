.global secuenciaTenis

.extern mostrar
.extern controles

secuenciaTenis
    STMFD SP!,{R4, R5, R6, LR}
    MOV R4, #0
    MOV R5, #12

loop
    LDR R6, =patronTenis
    LDRB R6, [R6, R4]
    MOV R0, R6
    BL mostrar
    MOV R0, R5
    BL controles
    MOV R5, R0
    CMP R5, #0
    BEQ exit
    BNE loop

exit
   LDMFD SP!,{R4, R5, R6, PC}

.data patronTenis
    .byte 0xC1
    .byte 0xA1
    .byte 0x91
    .byte 0x89
    .byte 0x85
    .byte 0x83
    .byte 0x83
    .byte 0x85
    .byte 0x89
    .byte 0x91
    .byte 0xA1
    .byte 0xC1
    
/*
gcc main.c -o main -lncurses 
gcc -g tenis.s -o prueba

gcc main.o prueba.o -lncurses -o programa

-g
-o es para generar con el nombre prueba1


debugger: ddd nombre.s, pongo breakpoints en main y done

*/

