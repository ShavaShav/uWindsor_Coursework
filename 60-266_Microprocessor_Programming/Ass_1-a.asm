TITLE CharacterCount     (ass_1-a.asm)

; Assignment 1 - Programming Exercise 1 -  provides various character counts
; Completed for 60-266 at the University of Windsor
; Author: Zach Shaver
; Last update: 24/10/2016

; Include Irvine32 library routines
INCLUDE Irvine32.inc

LINE_MAX = 240	; 240 characters for max line (arbitrary)

.data
	prompt	 BYTE	"Write a sentence ending with a period:", 0Dh, 0Ah, 0Dh, 0Ah, 0
	line		 BYTE	LINE_MAX+1 DUP(0)	; +1 for null-termination
	totalCount DWORD	0				; the tallys for type of each character
	lowerCount DWORD	0				; in "line". Standard Int32
	decCount	 DWORD	0
	blankCount DWORD	0
	estring1	 BYTE	"The file contains ", 0
	estring2	 BYTE	" characters: out of which,", 0DH, 0Ah, 0
	estring3	 BYTE	" are lowercase characters; ", 0
	estring4	 BYTE	" are decimal numbers; and, ", 0
	estring5	 BYTE	" are blank characters.", 0DH, 0Ah, 0
.code
main PROC
	MOV edx, OFFSET prompt
	CALL WriteString
	mov eax, lightBlue
	CALL SetTextColor
STRD:
	MOV edx, OFFSET line	; point edx to address of line
	MOV ecx, LINE_MAX		; give ecx the maximum length of the line
	CALL ReadString		; line now has null-terminated string, eax = length

	ADD totalCount, eax		; add length to total count
	mov esi, 0			; offset pointer = 0
	CHRD: cmp eax, esi		; compare length to current offset (check if end of string)
		JZ NEXT			; exit if so
		mov dl, [line+esi]	; move character at esi offset in line to dl
	; Switch statement based on type of character
	; Lowercase
		CMP dl, 61h		; first condition: lower limit of lowercase ASCII
		JB CDC			; not lowercase, so go to next case
		CMP dl, 7Ah		; second condition: upper limit of lowercase ASCII	
		JA CDC			; not lowercase, so go to next case
		INC lowerCount		; else, increment counter and break out of switch statement
		JMP ENDC
	; Decimal
	CDC: CMP dl, 30h		; first condition: lower limit of decimal ASCII
		JB CBL			; not decimal, so go to next case
		CMP dl, 39h		; second condition: upper limit of decimal ASCII	
		JA CBL			; not decimal, so go to next case
		INC decCount		; else, increment counter and break out of switch statement
		JMP ENDC
	; Blank
	CBL: CMP dl, 20h		; you know the routine..
		JNE CPR
		INC blankCount
		JMP ENDC
	; Period
	CPR:
		cmp dl, 2Eh		; ZR = 1 if a period
		JZ DONE			; jumps to output message
	ENDC:	
		inc esi			; increment pointer by a byte (next character)
		JMP CHRD			; continue the "while loop"
	
	NEXT:
	JMP STRD

DONE:
	
	; Display results
	CALL Crlf
	mov eax, lightRed
	CALL SetTextColor
	mov edx, OFFSET estring1
	CALL WriteString
	mov eax, totalCount		
	CALL WriteDec
	mov edx, OFFSET estring2
	CALL WriteString
	mov eax, lowerCount		
	CALL WriteDec
	mov edx, OFFSET estring3
	CALL WriteString
	mov eax, decCount		
	CALL WriteDec
	mov edx, OFFSET estring4
	CALL WriteString
	mov eax, blankCount		
	CALL WriteDec
	mov edx, OFFSET estring5
	CALL WriteString
	CALL Crlf
	
	mov eax, lightGray
	CALL SetTextColor
	;call WaitMsg				; commented out for as debugger already calls it
	exit
main ENDP
END main