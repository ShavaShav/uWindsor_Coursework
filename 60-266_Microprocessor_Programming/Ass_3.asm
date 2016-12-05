TITLE Assignment 3     (Ass_3.asm)

; Assignment 3 - 266 - Calculates GCD, Factorial, and Primes < 1000
; Author: Zach Shaver
; Last update: 29/11/2016

; Include Irvine32 library routines
INCLUDE Irvine32.inc

.data
	num1 DWORD ?
	num2 DWORD ?
	GCD_PROMPT BYTE "Please enter two positive integers: ", 0
	GCD_FIN BYTE "Greatest Common Denominator is ",0
	FACT_PROMPT BYTE "Please enter a positive integer, less than 13: ", 0
	FACT_FIN BYTE "Factorial is ",0
	PRIMES_ST BYTE "The first 1000 prime numbers are:",0dh,0ah,0
	GCD_MASM PROTO, varX:DWORD, varY:DWORD
.code
main PROC
	; PROMPTING FOR GCD INPUT
	MOV EDX, OFFSET GCD_PROMPT
	CALL WriteString
	CALL ReadInt
	MOV num1, EAX	; store X
	CALL ReadInt
	MOV num2, EAX	; store Y

	; A) CALLING ITERATIVE GCD FUNCTION
	;INVOKE GCD_MASM, num1, num2	; ALT METHOD
	MOV EDX, OFFSET GCD_FIN
	CALL WriteString		; display output string
	PUSH num2				; pushing arguments in reverse order
	PUSH num1
	CALL GCD_ITV			; call function
	CALL WriteDec			; display result		
	CALL Crlf

	; B) CALLING RECURSIVE GCD FUNCTION
	MOV EDX, OFFSET GCD_FIN
	CALL WriteString		; display output string
	CALL GCD_REC			; call function (reusing stack args)
	CALL WriteDec			; display result
	CALL Crlf

	ADD ESP, 8			; caller cleans stack

	; PROMPTING FOR FACTORIAL INPUT
	MOV EDX, OFFSET FACT_PROMPT
	CALL WriteString
	CALL ReadInt
	MOV num1, EAX	; store N	

	; C) CALLING ITERATIVE FACTORIAL FUNCTION
	MOV EDX, OFFSET FACT_FIN
	CALL WriteString		; display output string
	PUSH num1				; push number onto stack
	CALL FACTORIAL			; call function
	CALL WriteDec			; display result		
	CALL Crlf

	; D) CALLING PRIMES FUNCTION
	MOV EDX, OFFSET PRIMES_ST
	CALL WriteString		; display output string
	CALL PrimesUpTo1000
	CALL Crlf

	exit
main ENDP

GCD_ITV PROC USES EBX EDX
; Receives: X and Y (DWORDs) passed as stack arguments
; Returns: Greatest common denominator to EAX
; Cleans it's own stack of input parameters
	PUSH EBP			; Push base pointer to stack
	MOV EBP, ESP		; Set base pointer to its place in stack

	; Can make use of registers instead of local variables
	MOV EAX, [EBP+16]	; EAX = X
	MOV EBX, [EBP+20]	; EBX = Y
	WHILELOOP:
		ROL EAX, 16	; Shifting to move high 16 bits to EDX
		MOVZX EDX, AX	; in preparation for 32 bit DIV operation
		ROL EAX, 16	; Shift back to original
		AND EAX, 00FFh	; Clear top half
		DIV EBX		; AX = Quotient, DX = Remainder
		MOV EAX, EBX	; X = Y
		MOVZX EBX, DX	; Y = Remainder
		CMP EBX, 0	; Y > 0?
		JA WHILELOOP

	MOV ESP, EBP		; Free local space
	POP EBP			; ESP + 4

	RET
GCD_ITV ENDP

GCD_REC PROC USES EBX EDX
; Receives: X and Y (DWORDs) passed as stack arguments
; Returns: Greatest common denominator to EAX
; Uses recursion as loop will remain invariant
; Cleans it's own stack of input parameters
	PUSH EBP
	MOV EBP, ESP

	MOV EAX, [EBP+16]	; EAX = X
	MOV EBX, [EBP+20]	; EBX = Y
	CMP EBX, 0
	JE RETURN
	ROL EAX, 16	; Shifting to move high 16 bits to EDX
	MOVZX EDX, AX	; in preparation for 32 bit DIV operation
	ROL EAX, 16	; Shift back to original
	AND EAX, 00FFh	; Clear top half
	DIV EBX		; AX = Quotient, DX = Remainder
	MOV EAX, EBX	; X = Y
	MOVZX EBX, DX	; Y = Remainder
	PUSH EBX		; push X % Y onto stack
	PUSH EAX		; push Y onto stack
	CALL GCD_REC
	RETURN:

		MOV ESP, EBP	; free local variable (ESP reset to EBP)
		POP EBP
		RET
GCD_REC ENDP

FACTORIAL PROC USES ECX
; Receives: N (DWORD) passed as a stack argument
; Return: Factorial of N to EAX (assumed to not overflow)
; Cleans it's own stack
	PUSH EBP
	MOV EBP, ESP
	MOV EAX, 1
	MOV ECX, 12[EBP]	; set loop counter to N
	CALCFACT:
		MUL ECX		; EAX = EAX * N
		LOOP CALCFACT	; N = N -1
	MOV ESP, EBP	; free local space
	POP EBP
	RET 4	; clean stack
FACTORIAL ENDP

PrimesUpTo1000 PROC USES EAX EBX ECX EDX ESI
; Receives and returns nothing. Displays all prime numbers
; less than or equal to 1000 using Sieve of Eratosthenes algo
; Tried to make use of bitmasks and register shifts for education purposes
	ENTER 250, 0	; Do base pointer placement and ESP - 250 for local array
	MOV ECX, 63	; Will be using 1000 bits as boolean array or 250 Bytes/63 DWORDS
	LEA ESI, [EBP]	; Load address of base pointer to segment index pointer
	CLEAR:	
		SUB ESI, 4					; Next DWORD in stack
		MOV DWORD PTR [ESI], 0FFFFFFFFh	; set all bits to true
		LOOP CLEAR

	LEA ESI, [EBP-4]	; ESI = First DWORD of flags
	MOV EBX, 0FFFFFFFCh	; set first two bits to false (0 and 1 aren't prime)
	AND EBX, [ESI]		
	MOV [ESI], EBX		; overwrite array variable

	MOV EBX, 00000001h ; for checking if flag true
	ROL EBX, 2		; True Bitmask set to start at bit 2
	MOV ECX, 2		; N = 2

	WHILELOOP: ; for N = 2, 3, 4 ... not exceeding sqrt of 1000
		MOV EAX, EBX	; EAX = Bitmask for checking truth
		AND EAX, [ESI]
		JZ SKIPINNER	; Flag is fakse, skip inner loop
		; inner loop initiliazations
		MOV EAX, ECX
		MUL ECX		; EAX = N squared
		PUSH ESI	; store location of first 32 flags
		PUSH EBX	; push truth bitmask to stack
	INNER:
		PUSH ECX	; store old N
		CMP EAX, 1000	; current number > 1000?
		JAE ENDINNER
		LEA ESI, [EBP-4]	; beginning of flag array
		MOV EBX, 0FFFFFFFEh ; for setting flag to false
		PUSH EAX	; store EAX
		MOV DL, 32
		DIV DL	; AL = quotient, AH = remainder
		MOV CL, AH
		ROL EBX, CL	; use modulus to shift select bit in DWORD bitmask
		MOV DL, SIZEOF DWORD
		MUL DL		; find number of DWORDS to move in array
		MOVZX ECX, AL
		SUB ESI, ECX	; move position in array to DWORD containing flag 
		AND EBX, [ESI]	; toggle selected flag to false
		MOV [ESI], EBX ; overwrite old DWORD flags
		;MOV EAX, [ESI]	;Uncomment to see sieve action
		;CALL WriteBin
		;CALL Crlf
		POP EAX	; restore EAX
		POP ECX	; restore N
		ADD EAX, ECX	; EAX = current number + N
		JMP INNER
	ENDINNER:
		POP ECX	; restore N
		POP EBX	; restore truth bitmask
		POP ESI	; restore location of first 32 flags
	SKIPINNER:
		ROL EAX, 1	; rotate flag setters left by 1;
		ROL EBX, 1
		INC ECX		; increment N		
		CMP ECX, 32	; square root of 1000
		JLE WHILELOOP

	; Display primes
	MOV ECX, 0
	LEA ESI, [EBP]
	DISPLAY:
		SUB ESI, 4
		MOV EBX, 0
		MOV EDX, 00000001h ; for checking if flag true 
		FOREACHFLAG:
			MOV EAX, [ESI]	; store current round of 32 flags
			AND EAX, EDX	; EAX should be 0-filled if flag is set
			JZ FALSEFLAG
			MOV EAX, ECX	; Move number to EAX
			CALL WriteDec	; Write to screen
			MOV AL, 09h	; Move TAB ASCII to AL
			CALL WriteChar ; Write to screen
			FALSEFLAG:
			ROL EDX, 1	; rotate select bit
			INC ECX		; increment current number
			CMP ECX, 1000
			JE EXITL
			INC EBX		; increment counter until 32nd bit hit
			CMP EBX, 32
			JL FOREACHFLAG
		JMP DISPLAY
	EXITL:
	LEAVE
	RET
PrimesUpTo1000 ENDP


; Unused in assignment, but works fine
GCD_MASM PROC USES EBX EDX, varX:DWORD, varY:DWORD
; Receives: X and Y (DWORDs) passed as INVOKE parameters
; Returns: Greatest common denominator to EAX
; Uses MASM's INVOKE DIRECTIVE -> EBP pushed to stack and set to ESP and sets variables 
; to numbers put on stack by INVOKE. Will reset EBP but need to clean stack manually.
	MOV EAX, varX
	MOV EBX, varY
	WHILELOOP:
		ROL EAX, 16	; Shifting to move high 16 bits to EDX
		MOVZX EDX, AX	; in preparation for 32 bit DIV operation
		ROL EAX, 16	; Shift back to original
		AND EAX, 00FFh	; Clear top half
		DIV EBX		; AX = Quotient, DX = Remainder
		MOV EAX, EBX	; X = Y
		MOVZX EBX, DX	; Y = Remainder
		CMP EBX, 0	; Y > 0?
		JA WHILELOOP
	RET 8			; Clean stack of 2 DWORDS -> ESP + 8
GCD_MASM ENDP

END main