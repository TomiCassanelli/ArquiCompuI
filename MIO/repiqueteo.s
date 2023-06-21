.global secuenciaRepiqueteo

.extern mostrar
.extern controles

secuenciaRepiqueteo:
    STMFD SP!, {R4, R5, R6, LR}
    MOV R4, #0
    MOV R5, #57

loop:
    LDR R6, =patronRepiqueteo
    ADD R6, R6, R4  @ Realizar la suma entre R6 y R4 para obtener la dirección correcta
    LDRB R6, [R6]
    MOV R0, R6
    BL mostrar
    BL controles
    SUB R5, R5, #1  @ Restar 1 a R5 en cada iteración
    CMP R5, #0     @ Verificar si R5 ha llegado a 0
    BEQ exit
    ADD R4, R4, #1  @ Incrementar R4 para el próximo byte
    B loop

exit:
    MOV R4, #0       @ Reiniciar R4 a 0 y R5 a 0 para comenzar desde el primer byte de la secuencia
    MOV R5, #57
    B loop           @ Saltar al inicio del bucle

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


