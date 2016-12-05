TITLE  Fibonacci   (Ass_1-b.asm)

; Computes and displays the fibonacci sequence up to a given upper limit
; Author: Zach Shaver
; Last update: 26/10/2016

; Include Irvine32 library routines
INCLUDE Irvine32.inc

.data
	prompt BYTE "How many fibonacci numbers would you like? ", 0
	fib BYTE "Fibonacci sequence with N = 10 is: ", 0
	space BYTE " "
.code
main PROC
	MOV EDX, OFFSET prompt
	CALL WriteString	; Console: "How many.."
	CALL ReadInt		; EAX = n
	CALL Crlf

	MOV ECX, EAX		; Set loop counter to n
	
	MOV EAX, lightBlue
	CALL SetTextColor
	MOV EDX, OFFSET fib
	CALL WriteString	; Console : "Fibonacci sequence.."

	; Fibonacci sequence will be written to console as it is computed
	MOV DL, space	; Store space ASCII in DL for writing
	MOV EAX, 0	; EAX will be fibonacci number	(init 0)
	MOV EBX, 1	; EBX will be previous fibonacci number (init 1)	
CALC:
	CALL WriteDec		; Write fibonacci number
	XCHG AL, DL		; DL = lower byte of Fib, AL = Space ASCII
	CALL WriteChar		; Write space
	XCHG DL, AL		; DL = Space, EAX = fib
	ADD	EBX,		EAX	; Next (EBX) = Prev (EBX) + Current (EAX) Fib
	XCHG EAX,		EBX	; EAX = Next , EBX = Current
	LOOP CALC			; exits loop after n iterations

	MOV EAX, lightGray
	CALL SetTextColor
	CALL Crlf
	CALL Crlf
	;call WaitMsg				; commented out for as debugger already calls it

	exit
main ENDP
END main