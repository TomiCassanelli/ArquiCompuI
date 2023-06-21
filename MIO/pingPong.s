.global secuenciaPingPong

.extern mostrar
.extern controles

secuenciaPingPong:
    STMFD SP!, {R4, R5, R6, LR}
    MOV R4, #0
    MOV R5, #12

loop:
    LDR R6, =patronPingPong @ Le carga a R6 el arreglo patron
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
    MOV R5, #12
    B loop           @ Saltar al inicio del bucle

patronPingPong:
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