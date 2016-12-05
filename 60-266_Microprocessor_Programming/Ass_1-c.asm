TITLE StringReversal    (Ass_1-c.asm)

; Takes a string and displays it in lowercase and reverse order
; Author: Zach Shaver
; Last update: 27/10/2016

; Include Irvine32 library routines
INCLUDE Irvine32.inc

.data
	IN_MAX = 128
	prompt	BYTE	"Enter a string of at most 128 characters: ",0dh,0ah,0dh,0ah,0	
	input	BYTE	IN_MAX+1 DUP(0)	; at most 128 chars + 1 for null
	outString	BYTE	"Here it is in LOWERCASE and in reverse order:",0dh,0ah,0dh,0ah,0
.code
main PROC
; Prompt User for input and store in reserved memory
	mov edx, OFFSET prompt		; move address of prompt to edx
	call WriteString			; write prompt to console
	mov eax, lightBlue			; user input will be colored blue
	call SetTextColor
	mov edx, OFFSET input		; move address of reserved input memory into edx
	mov ecx, IN_MAX			; set ecx so as to read up to 128 characters
	call ReadString			; read input from console, EAX = string length
	call Crlf
	mov ecx, eax				; Store string length in loop counter to be used in reversal
; Display Output
	mov eax, lightRed			; output will be colored red
	call SetTextColor
	mov edx, OFFSET outString	; move address of output string to edx
	call WriteString			; write output header to console
; String will be made lowercase and displayed in reverse on the fly to save memory
	mov eax, 0				; zero-fill eax since it will be used in writing chars
L1:
	mov dl, input[ecx-1]		; store character, starting from last
	cmp dl, 41h
	jl GOOD					; if lower than lower limit of uppcase, then "good"
	cmp dl, 5Ah				; check next AND condition
	ja GOOD					; if higher than upper limit, then good
	add dl, 20h				; else character is uppercase so make lowercase
GOOD:						; character is good, so now we can write the character to console
	mov al, dl				; move character to proper register for writing char
	call WriteChar				; write to console and continue loop to previous character
	loop L1

	call Crlf
	call Crlf
	mov eax, lightGray			; reset color for wait msg..
	call SetTextColor
	;call WaitMsg				; commented out for as debugger already calls it
	exit
main ENDP
END main