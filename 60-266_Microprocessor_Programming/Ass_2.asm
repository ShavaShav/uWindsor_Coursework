TITLE  Assignment 2    (Ass_2.asm)

; Completed for 60-266 - Displays numbers up to 2^16 in hexadecimal
; Author: Zach Shaver
; Last update: 05/11/2016

; Include Irvine32 library routines
INCLUDE Irvine32.inc

; Enter constants and EQU directives up here

.data
	prompt	BYTE		"Enter a number between 0 and 65535: ",0
	badnum	BYTE		"Invalid number.",0

.code
main PROC
	mov edx, OFFSET prompt
	mov ecx, LENGTHOF prompt
	call WriteString
	call ReadInt		; get number from user
	call Crlf
	; switch case statement to determine size of number for proper proc
	cmp eax, 0FFFFh	; upper limit = FFFFh
	ja INVALID
	cmp ax, 0FFh		; upper limit of byte
	ja HWORD			; above will be valid word
	cmp ax, 0Fh		; upper limit of hex digit
	ja HBYTE			; above will be valid byte
	cmp ax, 0h		; lower limit = 0h
	jb INVALID		
HDIGIT:				; else must be hex digit
	mov bx, ax
	call DisplayHexDigit
	jmp FINISH
HBYTE:
	mov bx, ax
	call DisplayHexByte
	jmp FINISH
HWORD:
	mov bx, ax
	call DisplayHexWord
	jmp FINISH
INVALID:
	mov edx, OFFSET badnum
	call WriteString
FINISH:
	call Crlf
	call Crlf
	;call WaitMsg		; debugger already displays wait msg
	exit
main ENDP

DisplayHexDigit PROC
; Receives bx containing between 0-16 (zero padded 12 bytes)
; Displays hex digit on screen
; output: 
	push bx		; store bx
	push eax		; store eax	
	add bl, '0'	; Will bring numbers to proper ASCII for Hex
	cmp bl, ':'	; check if over numeric ascii (e.g A-F)
	jb OUTPUT		; if not, then good so can print
	add bl, 7		; else increment 7 to proper ASCII for hex
OUTPUT:
	movzx EAX, BL
	call WriteChar
	pop eax		; restore eax
	pop bx		; restore bx
	ret
DisplayHexDigit ENDP

DisplayHexByte PROC
; Receives bx containing number between 0-255 (zero padded 8 bytes)
; Displays hex byte on screen (2 digits)
; output: void
	push bx		; store bx
	push ax		; store ax
	mov AX, BX	; set up for division by 16
	mov bl, 10h	;
	div bl		; AH & AL now contain each digit
	movzx bx, al;	; AL = most significant hex digit
	call DisplayHexDigit
	movzx bx, ah;	; AH = least significant hex digit
	call DisplayHexDigit
	pop ax		; restore ax
	pop bx		; restore bx
	ret
DisplayHexByte ENDP

DisplayHexWord PROC
; Receives bx containing number between 0-65,536
; Displays hex word on screen (4 digits)
; output: void
	push bx		; store bx
	push ax		; store ax
	push dx		; store dx
	mov ax, bx	; set up for division by 16^2
	mov dx, 0		; clear most significant bits of dividend
	mov bx, 100h	
	div bx		; AX and DX now contain each group of hex bytes
	mov bx, ax	; AX = most significant hex byte (2 hex digits)
	call DisplayHexByte
	mov bx, dx	; DX = least significant hex byte (2 hex digits)
	call DisplayHexByte
	pop dx		; restore dx
	pop ax		; restore ax
	pop bx		; restore bx
	ret
DisplayHexWord ENDP

END main