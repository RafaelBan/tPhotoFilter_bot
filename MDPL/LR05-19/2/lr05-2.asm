SSEG	SEGMENT	PARA	STACK
		DB	100	DUP	(0)
SSEG	ENDS

DSEG	SEGMENT
	MATRIX	DB	"01234"
		DB	"56789"
		DB	"98765"
		DB	"43210"
		DB	"01234"
DSEG	ENDS

CSEG	SEGMENT
	ASSUME CS:CSEG, DS:DSEG, SS:SSEG

MAIN:
		MOV	AX,DSEG
		MOV	DS,AX

		MOV	SI,5
		MOV	DI,5
		CALL	MATRIX_PRINT

		MOV	BX,OFFSET MATRIX
		MOV	DX,5
		MOV	CX,DX
		DEC	CX
		LOOP1:
			MOV	SI,1
			MOV	DI,DX

			LOOP2:
				MOV	AL,[BX+SI]
				XCHG	AL,[BX+DI]

				MOV	[BX+SI],AL

				INC	SI
				ADD	DI,DX

				CMP	SI,CX
				JNG	LOOP2

			ADD	BX,DX
			INC	BX

			DEC	CX
			JNZ	LOOP1
		
		MOV	SI,5
		MOV	DI,5
		CALL	MATRIX_PRINT

		MOV	AX,4C00H
		INT	21H

MATRIX_PRINT	PROC	NEAR
		MOV	CX,DI
		MOV	BX,0
		MOV	AH,02H

		PRINT_ROW:
			MOV	DL,MATRIX[BX]
			INT	21H
			MOV	DL,' '
			INT	21H

			DEC	DI
			JNZ	SKIP_CRLF

			MOV	DL,13
			INT	21H
			MOV	DL,10
			INT	21H

			MOV	DI,CX		
			DEC	SI
			JZ	PRINT_END

			SKIP_CRLF:
			INC	BX
			JMP	PRINT_ROW

		PRINT_END: 	
			int	21h
		RET
MATRIX_PRINT	ENDP

CSEG	ENDS

END	MAIN
