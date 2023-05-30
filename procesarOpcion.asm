global procesarOpcion
section .text

procesarOpcion
			mov		R0, R1   ; El parametro de entrada (opcion) se pasa en el registro R0
			cmp		R0, #1
			beq		Opcion1
			cmp		R0, #2
			beq		Opcion2
			cmp		R0, #3
			beq		Opcion3
			cmp		R0, #0
			
Opcion1
			;		C�digo de la opci�n 1
			;		...
			
			
Opcion2
			;		C�digo de la opci�n 2
			;		...
			
			
Opcion3
			;		C�digo de la opci�n 3
			;		...
