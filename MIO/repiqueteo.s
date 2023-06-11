.global secuenciaRepiqueteo

.extern mostrar
.extern controles


secuenciaRepiqueteo:
    PUSH {R4-R6, LR}
    MOV R4, #0
    MOV R5, #57

loop:
    LDRB R6, =patronRepiqueteo
    LDRB R6, [R6,R4]
    MOV R0, R6
    BL mostrar
    MOV R0, R5
    BL controles
    MOV R5, R0
    CMP R5, #0
    BEQ exit
    BNE loop

exit:
    POP {R4-R6, PC}

.data 
patronRepiqueteo:
    .byte 0x80
    .byte 0x40
    .byte 0x80
    .byte 0x40
    .byte 0x20
    .byte 0x40
    .byte 0x80
    .byte 0x40
    .byte 0x20
    .byte 0x10
    .byte 0x20
    .byte 0x40
    .byte 0x80
    .byte 0x40
    .byte 0x20
    .byte 0x10
    .byte 0x08
    .byte 0x10
    .byte 0x20
    .byte 0x40
    .byte 0x80
    .byte 0x40
    .byte 0x20
    .byte 0x10
    .byte 0x08
    .byte 0x04
    .byte 0x08
    .byte 0x10
    .byte 0x20
    .byte 0x40
    .byte 0x80
    .byte 0x40
    .byte 0x20
    .byte 0x10
    .byte 0x08
    .byte 0x04
    .byte 0x02
    .byte 0x04
    .byte 0x08
    .byte 0x10
    .byte 0x20
    .byte 0x40
    .byte 0x80
    .byte 0x40
    .byte 0x20
    .byte 0x10
    .byte 0x08
    .byte 0x04
    .byte 0x02
    .byte 0x01
    .byte 0x02
    .byte 0x04
    .byte 0x08
    .byte 0x10
    .byte 0x20
    .byte 0x40
    .byte 0x80
.end

/*
gcc main.c -lncurses -o main
gcc -g carrera2.s -o prueba1

-g
-o es para generar con el nombre prueba1


debugger: ddd nombre.s, pongo breakpoints en main y done

*/

