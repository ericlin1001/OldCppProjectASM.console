; Listing generated by Microsoft (R) Optimizing Compiler Version 16.00.30319.01 

	TITLE	E:\C ++\C++Projects\console\likeEatSnack\snackAsm.cpp
	.686P
	.XMM
	include listing.inc
	.model	flat

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	?an@@3EA					; an
PUBLIC	?outputData@@3PAEA				; outputData
PUBLIC	?pivot@@3PAUNode@@A				; pivot
PUBLIC	?graph@@3PAY07EA				; graph
PUBLIC	?len@@3EA					; len
PUBLIC	?head@@3PAUNode@@A				; head
PUBLIC	?food@@3PAUNode@@A				; food
PUBLIC	?dirs@@3PAUDir@@A				; dirs
PUBLIC	?idir@@3EA					; idir
PUBLIC	?winLen@@3EA					; winLen
PUBLIC	?seed@@3EA					; seed
_BSS	SEGMENT
?an@@3EA DB	01H DUP (?)				; an
	ALIGN	4

?outputData@@3PAEA DB 08H DUP (?)			; outputData
?pivot@@3PAUNode@@A DD 01H DUP (?)			; pivot
?graph@@3PAY07EA DB 040H DUP (?)			; graph
?len@@3EA DB	01H DUP (?)				; len
	ALIGN	4

?head@@3PAUNode@@A DD 01H DUP (?)			; head
?food@@3PAUNode@@A DD 01H DUP (?)			; food
_BSS	ENDS
_DATA	SEGMENT
?dirs@@3PAUDir@@A DB 00H				; dirs
	DB	00H
	DB	0ffH
	DB	00H
	DB	00H
	DB	01H
	DB	01H
	DB	00H
	DB	00H
	DB	0ffH
?idir@@3EA DB	03H					; idir
?winLen@@3EA DB	05H					; winLen
?seed@@3EA DB	02H					; seed
_DATA	ENDS
PUBLIC	??0Node@@QAE@EEPAU0@@Z				; Node::Node
PUBLIC	?init@@YAXXZ					; init
EXTRN	??2@YAPAXI@Z:PROC				; operator new
; Function compile flags: /Odtp
_TEXT	SEGMENT
tv146 = -40						; size = 4
tv136 = -36						; size = 4
tv95 = -32						; size = 4
tv84 = -28						; size = 4
tv72 = -24						; size = 4
$T2673 = -20						; size = 4
$T2670 = -16						; size = 4
$T2667 = -12						; size = 4
$T2664 = -8						; size = 4
$T2661 = -4						; size = 4
?init@@YAXXZ PROC					; init
; File e:\c ++\c++projects\console\likeeatsnack\snackasm.cpp
; Line 27
	push	ebp
	mov	ebp, esp
	sub	esp, 40					; 00000028H
; Line 28
	push	8
	call	??2@YAPAXI@Z				; operator new
	add	esp, 4
	mov	DWORD PTR $T2661[ebp], eax
	cmp	DWORD PTR $T2661[ebp], 0
	je	SHORT $LN3@init
	push	0
	push	4
	push	2
	mov	ecx, DWORD PTR $T2661[ebp]
	call	??0Node@@QAE@EEPAU0@@Z			; Node::Node
	mov	DWORD PTR tv72[ebp], eax
	jmp	SHORT $LN4@init
$LN3@init:
	mov	DWORD PTR tv72[ebp], 0
$LN4@init:
	mov	eax, DWORD PTR tv72[ebp]
	mov	DWORD PTR ?head@@3PAUNode@@A, eax	; head
; Line 29
	mov	ecx, DWORD PTR ?head@@3PAUNode@@A	; head
	mov	edx, DWORD PTR ?head@@3PAUNode@@A	; head
	mov	DWORD PTR [ecx+4], edx
; Line 30
	push	8
	call	??2@YAPAXI@Z				; operator new
	add	esp, 4
	mov	DWORD PTR $T2664[ebp], eax
	cmp	DWORD PTR $T2664[ebp], 0
	je	SHORT $LN5@init
	mov	eax, DWORD PTR ?head@@3PAUNode@@A	; head
	mov	ecx, DWORD PTR [eax+4]
	push	ecx
	push	4
	push	1
	mov	ecx, DWORD PTR $T2664[ebp]
	call	??0Node@@QAE@EEPAU0@@Z			; Node::Node
	mov	DWORD PTR tv84[ebp], eax
	jmp	SHORT $LN6@init
$LN5@init:
	mov	DWORD PTR tv84[ebp], 0
$LN6@init:
	mov	edx, DWORD PTR ?head@@3PAUNode@@A	; head
	mov	eax, DWORD PTR tv84[ebp]
	mov	DWORD PTR [edx+4], eax
; Line 31
	push	8
	call	??2@YAPAXI@Z				; operator new
	add	esp, 4
	mov	DWORD PTR $T2667[ebp], eax
	cmp	DWORD PTR $T2667[ebp], 0
	je	SHORT $LN7@init
	mov	ecx, DWORD PTR ?head@@3PAUNode@@A	; head
	mov	edx, DWORD PTR [ecx+4]
	push	edx
	push	4
	push	0
	mov	ecx, DWORD PTR $T2667[ebp]
	call	??0Node@@QAE@EEPAU0@@Z			; Node::Node
	mov	DWORD PTR tv95[ebp], eax
	jmp	SHORT $LN8@init
$LN7@init:
	mov	DWORD PTR tv95[ebp], 0
$LN8@init:
	mov	eax, DWORD PTR ?head@@3PAUNode@@A	; head
	mov	ecx, DWORD PTR tv95[ebp]
	mov	DWORD PTR [eax+4], ecx
; Line 32
	mov	BYTE PTR ?len@@3EA, 3			; len
; Line 33
	push	8
	call	??2@YAPAXI@Z				; operator new
	add	esp, 4
	mov	DWORD PTR $T2670[ebp], eax
	cmp	DWORD PTR $T2670[ebp], 0
	je	SHORT $LN9@init
	push	0
	push	0
	push	0
	mov	ecx, DWORD PTR $T2670[ebp]
	call	??0Node@@QAE@EEPAU0@@Z			; Node::Node
	mov	DWORD PTR tv136[ebp], eax
	jmp	SHORT $LN10@init
$LN9@init:
	mov	DWORD PTR tv136[ebp], 0
$LN10@init:
	mov	edx, DWORD PTR tv136[ebp]
	mov	DWORD PTR ?food@@3PAUNode@@A, edx	; food
; Line 35
	push	8
	call	??2@YAPAXI@Z				; operator new
	add	esp, 4
	mov	DWORD PTR $T2673[ebp], eax
	cmp	DWORD PTR $T2673[ebp], 0
	je	SHORT $LN11@init
	mov	eax, DWORD PTR ?head@@3PAUNode@@A	; head
	mov	ecx, DWORD PTR [eax+4]
	push	ecx
	push	0
	push	0
	mov	ecx, DWORD PTR $T2673[ebp]
	call	??0Node@@QAE@EEPAU0@@Z			; Node::Node
	mov	DWORD PTR tv146[ebp], eax
	jmp	SHORT $LN12@init
$LN11@init:
	mov	DWORD PTR tv146[ebp], 0
$LN12@init:
	mov	edx, DWORD PTR tv146[ebp]
	mov	DWORD PTR ?pivot@@3PAUNode@@A, edx	; pivot
; Line 36
	mov	esp, ebp
	pop	ebp
	ret	0
?init@@YAXXZ ENDP					; init
; Function compile flags: /Odtp
_TEXT	ENDS
;	COMDAT ??0Node@@QAE@EEPAU0@@Z
_TEXT	SEGMENT
_this$ = -4						; size = 4
_tx$ = 8						; size = 1
_ty$ = 12						; size = 1
_p$ = 16						; size = 4
??0Node@@QAE@EEPAU0@@Z PROC				; Node::Node, COMDAT
; _this$ = ecx
; Line 5
	push	ebp
	mov	ebp, esp
	push	ecx
	mov	DWORD PTR _this$[ebp], ecx
; Line 6
	mov	eax, DWORD PTR _this$[ebp]
	mov	cl, BYTE PTR _tx$[ebp]
	mov	BYTE PTR [eax], cl
	mov	edx, DWORD PTR _this$[ebp]
	mov	al, BYTE PTR _ty$[ebp]
	mov	BYTE PTR [edx+1], al
; Line 7
	mov	ecx, DWORD PTR _this$[ebp]
	mov	edx, DWORD PTR _p$[ebp]
	mov	DWORD PTR [ecx+4], edx
; Line 8
	mov	eax, DWORD PTR _this$[ebp]
	mov	esp, ebp
	pop	ebp
	ret	12					; 0000000cH
??0Node@@QAE@EEPAU0@@Z ENDP				; Node::Node
_TEXT	ENDS
PUBLIC	?lose@@YAXXZ					; lose
; Function compile flags: /Odtp
_TEXT	SEGMENT
?lose@@YAXXZ PROC					; lose
; Line 37
	push	ebp
	mov	ebp, esp
; Line 39
	pop	ebp
	ret	0
?lose@@YAXXZ ENDP					; lose
_TEXT	ENDS
PUBLIC	?win@@YAXXZ					; win
; Function compile flags: /Odtp
_TEXT	SEGMENT
?win@@YAXXZ PROC					; win
; Line 40
	push	ebp
	mov	ebp, esp
; Line 41
	pop	ebp
	ret	0
?win@@YAXXZ ENDP					; win
_TEXT	ENDS
PUBLIC	?createGraph@@YAXXZ				; createGraph
; Function compile flags: /Odtp
_TEXT	SEGMENT
_pg$ = -12						; size = 4
_i$ = -5						; size = 1
_p$ = -4						; size = 4
?createGraph@@YAXXZ PROC				; createGraph
; Line 44
	push	ebp
	mov	ebp, esp
	sub	esp, 12					; 0000000cH
; Line 46
	mov	DWORD PTR _pg$[ebp], OFFSET ?graph@@3PAY07EA ; graph
; Line 47
	mov	BYTE PTR _i$[ebp], 0
	jmp	SHORT $LN6@createGrap
$LN5@createGrap:
	mov	al, BYTE PTR _i$[ebp]
	add	al, 1
	mov	BYTE PTR _i$[ebp], al
$LN6@createGrap:
	movzx	ecx, BYTE PTR _i$[ebp]
	cmp	ecx, 64					; 00000040H
	jge	SHORT $LN4@createGrap
	mov	edx, DWORD PTR _pg$[ebp]
	mov	BYTE PTR [edx], 0
	mov	eax, DWORD PTR _pg$[ebp]
	add	eax, 1
	mov	DWORD PTR _pg$[ebp], eax
	jmp	SHORT $LN5@createGrap
$LN4@createGrap:
; Line 49
	mov	ecx, DWORD PTR ?head@@3PAUNode@@A	; head
	mov	DWORD PTR _p$[ebp], ecx
$LN3@createGrap:
; Line 51
	mov	edx, DWORD PTR _p$[ebp]
	movzx	eax, BYTE PTR [edx]
	mov	ecx, DWORD PTR _p$[ebp]
	movzx	edx, BYTE PTR [ecx+1]
	mov	BYTE PTR ?graph@@3PAY07EA[edx+eax*8], 1
; Line 52
	mov	eax, DWORD PTR _p$[ebp]
	mov	ecx, DWORD PTR [eax+4]
	mov	DWORD PTR _p$[ebp], ecx
; Line 53
	mov	edx, DWORD PTR _p$[ebp]
	cmp	edx, DWORD PTR ?head@@3PAUNode@@A	; head
	jne	SHORT $LN3@createGrap
; Line 54
	mov	eax, DWORD PTR ?food@@3PAUNode@@A	; food
	movzx	ecx, BYTE PTR [eax]
	mov	edx, DWORD PTR ?food@@3PAUNode@@A	; food
	movzx	eax, BYTE PTR [edx+1]
	mov	BYTE PTR ?graph@@3PAY07EA[eax+ecx*8], 2
; Line 55
	mov	esp, ebp
	pop	ebp
	ret	0
?createGraph@@YAXXZ ENDP				; createGraph
_TEXT	ENDS
PUBLIC	?rand@@YAEXZ					; rand
; Function compile flags: /Odtp
_TEXT	SEGMENT
?rand@@YAEXZ PROC					; rand
; Line 58
	push	ebp
	mov	ebp, esp
; Line 59
	xor	al, al
; Line 60
	pop	ebp
	ret	0
?rand@@YAEXZ ENDP					; rand
_TEXT	ENDS
PUBLIC	?move@@YAXE@Z					; move
; Function compile flags: /Odtp
_TEXT	SEGMENT
tv138 = -28						; size = 4
$T2682 = -24						; size = 4
_ipg$2611 = -17						; size = 1
_pg$2610 = -16						; size = 4
_index$2609 = -9					; size = 1
_dir$ = -8						; size = 2
_p$ = -4						; size = 4
_tdir$ = 8						; size = 1
?move@@YAXE@Z PROC					; move
; Line 61
	push	ebp
	mov	ebp, esp
	sub	esp, 28					; 0000001cH
; Line 62
	movzx	eax, BYTE PTR _tdir$[ebp]
	test	eax, eax
	jne	SHORT $LN13@move
; Line 63
	mov	cl, BYTE PTR ?idir@@3EA			; idir
	mov	BYTE PTR _tdir$[ebp], cl
$LN13@move:
; Line 65
	movzx	edx, BYTE PTR _tdir$[ebp]
	mov	ax, WORD PTR ?dirs@@3PAUDir@@A[edx*2]
	mov	WORD PTR _dir$[ebp], ax
; Line 66
	mov	ecx, DWORD PTR ?head@@3PAUNode@@A	; head
	mov	DWORD PTR _p$[ebp], ecx
; Line 67
	mov	edx, DWORD PTR ?head@@3PAUNode@@A	; head
	movzx	eax, BYTE PTR [edx]
	movzx	ecx, BYTE PTR _dir$[ebp]
	lea	edx, DWORD PTR [eax+ecx+8]
	and	edx, -2147483641			; 80000007H
	jns	SHORT $LN18@move
	dec	edx
	or	edx, -8					; fffffff8H
	inc	edx
$LN18@move:
	mov	eax, DWORD PTR ?pivot@@3PAUNode@@A	; pivot
	mov	BYTE PTR [eax], dl
; Line 68
	mov	ecx, DWORD PTR ?head@@3PAUNode@@A	; head
	movzx	edx, BYTE PTR [ecx+1]
	movzx	eax, BYTE PTR _dir$[ebp+1]
	lea	ecx, DWORD PTR [edx+eax+8]
	and	ecx, -2147483641			; 80000007H
	jns	SHORT $LN19@move
	dec	ecx
	or	ecx, -8					; fffffff8H
	inc	ecx
$LN19@move:
	mov	edx, DWORD PTR ?pivot@@3PAUNode@@A	; pivot
	mov	BYTE PTR [edx+1], cl
; Line 69
	mov	eax, DWORD PTR ?food@@3PAUNode@@A	; food
	movzx	ecx, BYTE PTR [eax]
	mov	edx, DWORD PTR ?pivot@@3PAUNode@@A	; pivot
	movzx	eax, BYTE PTR [edx]
	cmp	ecx, eax
	jne	$LN12@move
	mov	ecx, DWORD PTR ?food@@3PAUNode@@A	; food
	movzx	edx, BYTE PTR [ecx+1]
	mov	eax, DWORD PTR ?pivot@@3PAUNode@@A	; pivot
	movzx	ecx, BYTE PTR [eax+1]
	cmp	edx, ecx
	jne	$LN12@move
; Line 72
	mov	edx, DWORD PTR ?head@@3PAUNode@@A	; head
	mov	eax, DWORD PTR ?pivot@@3PAUNode@@A	; pivot
	mov	DWORD PTR [edx+4], eax
	mov	ecx, DWORD PTR ?pivot@@3PAUNode@@A	; pivot
	mov	DWORD PTR ?head@@3PAUNode@@A, ecx	; head
; Line 73
	mov	dl, BYTE PTR ?len@@3EA			; len
	add	dl, 1
	mov	BYTE PTR ?len@@3EA, dl			; len
; Line 74
	movzx	eax, BYTE PTR ?len@@3EA			; len
	movzx	ecx, BYTE PTR ?winLen@@3EA		; winLen
	cmp	eax, ecx
	jl	SHORT $LN11@move
	call	?win@@YAXXZ				; win
$LN11@move:
; Line 76
	push	8
	call	??2@YAPAXI@Z				; operator new
	add	esp, 4
	mov	DWORD PTR $T2682[ebp], eax
	cmp	DWORD PTR $T2682[ebp], 0
	je	SHORT $LN16@move
	mov	edx, DWORD PTR ?head@@3PAUNode@@A	; head
	mov	eax, DWORD PTR [edx+4]
	push	eax
	push	0
	push	0
	mov	ecx, DWORD PTR $T2682[ebp]
	call	??0Node@@QAE@EEPAU0@@Z			; Node::Node
	mov	DWORD PTR tv138[ebp], eax
	jmp	SHORT $LN17@move
$LN16@move:
	mov	DWORD PTR tv138[ebp], 0
$LN17@move:
	mov	ecx, DWORD PTR tv138[ebp]
	mov	DWORD PTR ?pivot@@3PAUNode@@A, ecx	; pivot
; Line 79
	call	?rand@@YAEXZ				; rand
	movzx	eax, al
	movzx	edx, BYTE PTR ?len@@3EA			; len
	mov	ecx, 64					; 00000040H
	sub	ecx, edx
	cdq
	idiv	ecx
	mov	BYTE PTR _index$2609[ebp], dl
; Line 80
	mov	dl, BYTE PTR _index$2609[ebp]
	add	dl, 1
	mov	BYTE PTR _index$2609[ebp], dl
; Line 81
	call	?createGraph@@YAXXZ			; createGraph
; Line 82
	mov	DWORD PTR _pg$2610[ebp], OFFSET ?graph@@3PAY07EA ; graph
; Line 83
	mov	BYTE PTR _ipg$2611[ebp], 0
$LN10@move:
; Line 84
	movzx	eax, BYTE PTR _index$2609[ebp]
	test	eax, eax
	je	SHORT $LN9@move
	movzx	ecx, BYTE PTR _ipg$2611[ebp]
	mov	edx, DWORD PTR _pg$2610[ebp]
	movzx	eax, BYTE PTR [edx+ecx]
	mov	cl, BYTE PTR _ipg$2611[ebp]
	add	cl, 1
	mov	BYTE PTR _ipg$2611[ebp], cl
	test	eax, eax
	jne	SHORT $LN8@move
	mov	dl, BYTE PTR _index$2609[ebp]
	sub	dl, 1
	mov	BYTE PTR _index$2609[ebp], dl
$LN8@move:
	jmp	SHORT $LN10@move
$LN9@move:
; Line 85
	mov	al, BYTE PTR _ipg$2611[ebp]
	sub	al, 1
	mov	BYTE PTR _ipg$2611[ebp], al
; Line 87
	movzx	eax, BYTE PTR _ipg$2611[ebp]
	cdq
	and	edx, 7
	add	eax, edx
	sar	eax, 3
	mov	ecx, DWORD PTR ?food@@3PAUNode@@A	; food
	mov	BYTE PTR [ecx], al
; Line 88
	movzx	edx, BYTE PTR _ipg$2611[ebp]
	and	edx, -2147483641			; 80000007H
	jns	SHORT $LN20@move
	dec	edx
	or	edx, -8					; fffffff8H
	inc	edx
$LN20@move:
	mov	eax, DWORD PTR ?food@@3PAUNode@@A	; food
	mov	BYTE PTR [eax+1], dl
; Line 90
	jmp	$LN14@move
; Line 91
	jmp	$LN14@move
$LN12@move:
; Line 92
	mov	ecx, DWORD PTR ?head@@3PAUNode@@A	; head
	mov	DWORD PTR _p$[ebp], ecx
$LN6@move:
; Line 93
	mov	edx, DWORD PTR _p$[ebp]
	mov	eax, DWORD PTR [edx+4]
	mov	DWORD PTR _p$[ebp], eax
	mov	ecx, DWORD PTR _p$[ebp]
	cmp	ecx, DWORD PTR ?head@@3PAUNode@@A	; head
	je	SHORT $LN5@move
	mov	edx, DWORD PTR _p$[ebp]
	movzx	eax, BYTE PTR [edx]
	mov	ecx, DWORD PTR ?pivot@@3PAUNode@@A	; pivot
	movzx	edx, BYTE PTR [ecx]
	cmp	eax, edx
	jne	SHORT $LN4@move
	mov	eax, DWORD PTR _p$[ebp]
	movzx	ecx, BYTE PTR [eax+1]
	mov	edx, DWORD PTR ?pivot@@3PAUNode@@A	; pivot
	movzx	eax, BYTE PTR [edx+1]
	cmp	ecx, eax
	jne	SHORT $LN4@move
	jmp	SHORT $LN5@move
$LN4@move:
; Line 94
	jmp	SHORT $LN6@move
$LN5@move:
	mov	ecx, DWORD PTR _p$[ebp]
	mov	edx, DWORD PTR [ecx+4]
	cmp	edx, DWORD PTR ?head@@3PAUNode@@A	; head
	jne	SHORT $LN3@move
; Line 96
	mov	al, BYTE PTR ?idir@@3EA			; idir
	mov	BYTE PTR _tdir$[ebp], al
; Line 97
	movzx	ecx, BYTE PTR _tdir$[ebp]
	mov	dx, WORD PTR ?dirs@@3PAUDir@@A[ecx*2]
	mov	WORD PTR _dir$[ebp], dx
; Line 98
	mov	eax, DWORD PTR ?head@@3PAUNode@@A	; head
	movzx	ecx, BYTE PTR [eax]
	movzx	edx, BYTE PTR _dir$[ebp]
	add	ecx, edx
	and	ecx, -2147483641			; 80000007H
	jns	SHORT $LN21@move
	dec	ecx
	or	ecx, -8					; fffffff8H
	inc	ecx
$LN21@move:
	mov	eax, DWORD PTR ?pivot@@3PAUNode@@A	; pivot
	mov	BYTE PTR [eax], cl
; Line 99
	mov	ecx, DWORD PTR ?head@@3PAUNode@@A	; head
	movzx	edx, BYTE PTR [ecx+1]
	movzx	eax, BYTE PTR _dir$[ebp+1]
	add	edx, eax
	and	edx, -2147483641			; 80000007H
	jns	SHORT $LN22@move
	dec	edx
	or	edx, -8					; fffffff8H
	inc	edx
$LN22@move:
	mov	ecx, DWORD PTR ?pivot@@3PAUNode@@A	; pivot
	mov	BYTE PTR [ecx+1], dl
	jmp	SHORT $LN2@move
$LN3@move:
; Line 100
	mov	edx, DWORD PTR _p$[ebp]
	cmp	edx, DWORD PTR ?head@@3PAUNode@@A	; head
	je	SHORT $LN2@move
; Line 101
	call	?lose@@YAXXZ				; lose
; Line 102
	jmp	SHORT $LN14@move
$LN2@move:
; Line 104
	mov	al, BYTE PTR _tdir$[ebp]
	mov	BYTE PTR ?idir@@3EA, al			; idir
; Line 107
	mov	ecx, DWORD PTR ?head@@3PAUNode@@A	; head
	mov	edx, DWORD PTR ?pivot@@3PAUNode@@A	; pivot
	mov	DWORD PTR [ecx+4], edx
	mov	eax, DWORD PTR ?pivot@@3PAUNode@@A	; pivot
	mov	DWORD PTR ?head@@3PAUNode@@A, eax	; head
; Line 108
	mov	ecx, DWORD PTR ?pivot@@3PAUNode@@A	; pivot
	mov	edx, DWORD PTR [ecx+4]
	mov	DWORD PTR ?pivot@@3PAUNode@@A, edx	; pivot
; Line 109
	mov	eax, DWORD PTR ?head@@3PAUNode@@A	; head
	mov	ecx, DWORD PTR ?pivot@@3PAUNode@@A	; pivot
	mov	edx, DWORD PTR [ecx+4]
	mov	DWORD PTR [eax+4], edx
$LN14@move:
; Line 113
	mov	esp, ebp
	pop	ebp
	ret	0
?move@@YAXE@Z ENDP					; move
_TEXT	ENDS
PUBLIC	?converToHex@@YAEE@Z				; converToHex
; Function compile flags: /Odtp
_TEXT	SEGMENT
_ch$ = 8						; size = 1
?converToHex@@YAEE@Z PROC				; converToHex
; Line 115
	push	ebp
	mov	ebp, esp
; Line 117
	movzx	eax, BYTE PTR _ch$[ebp]
	test	eax, eax
	jl	SHORT $LN2@converToHe
	movzx	ecx, BYTE PTR _ch$[ebp]
	cmp	ecx, 9
	jg	SHORT $LN2@converToHe
	movzx	eax, BYTE PTR _ch$[ebp]
	add	eax, 48					; 00000030H
	jmp	SHORT $LN3@converToHe
	jmp	SHORT $LN3@converToHe
$LN2@converToHe:
; Line 118
	movzx	eax, BYTE PTR _ch$[ebp]
	add	eax, 55					; 00000037H
$LN3@converToHe:
; Line 120
	pop	ebp
	ret	0
?converToHex@@YAEE@Z ENDP				; converToHex
_TEXT	ENDS
PUBLIC	?createOutputData@@YAXXZ			; createOutputData
; Function compile flags: /Odtp
_TEXT	SEGMENT
_j$ = -2						; size = 1
_i$ = -1						; size = 1
?createOutputData@@YAXXZ PROC				; createOutputData
; Line 121
	push	ebp
	mov	ebp, esp
	push	ecx
	push	esi
; Line 123
	call	?createGraph@@YAXXZ			; createGraph
; Line 124
	mov	BYTE PTR _i$[ebp], 0
	jmp	SHORT $LN6@createOutp
$LN5@createOutp:
	mov	al, BYTE PTR _i$[ebp]
	add	al, 1
	mov	BYTE PTR _i$[ebp], al
$LN6@createOutp:
	movzx	ecx, BYTE PTR _i$[ebp]
	cmp	ecx, 8
	jge	SHORT $LN7@createOutp
; Line 125
	movzx	edx, BYTE PTR _i$[ebp]
	mov	BYTE PTR ?outputData@@3PAEA[edx], 0
; Line 126
	mov	BYTE PTR _j$[ebp], 0
	jmp	SHORT $LN3@createOutp
$LN2@createOutp:
	mov	al, BYTE PTR _j$[ebp]
	add	al, 1
	mov	BYTE PTR _j$[ebp], al
$LN3@createOutp:
	movzx	ecx, BYTE PTR _j$[ebp]
	cmp	ecx, 8
	jge	SHORT $LN1@createOutp
; Line 127
	movzx	edx, BYTE PTR _i$[ebp]
	mov	al, BYTE PTR ?outputData@@3PAEA[edx]
	shl	al, 1
	movzx	ecx, BYTE PTR _i$[ebp]
	mov	BYTE PTR ?outputData@@3PAEA[ecx], al
; Line 128
	movzx	edx, BYTE PTR _i$[ebp]
	movzx	eax, BYTE PTR _i$[ebp]
	movzx	ecx, BYTE PTR _j$[ebp]
	mov	esi, 7
	sub	esi, ecx
	movzx	eax, BYTE PTR ?graph@@3PAY07EA[esi+eax*8]
	neg	eax
	sbb	eax, eax
	neg	eax
	movzx	ecx, BYTE PTR ?outputData@@3PAEA[edx]
	add	ecx, eax
	movzx	edx, BYTE PTR _i$[ebp]
	mov	BYTE PTR ?outputData@@3PAEA[edx], cl
; Line 129
	jmp	SHORT $LN2@createOutp
$LN1@createOutp:
; Line 130
	jmp	$LN5@createOutp
$LN7@createOutp:
; Line 132
	pop	esi
	mov	esp, ebp
	pop	ebp
	ret	0
?createOutputData@@YAXXZ ENDP				; createOutputData
_TEXT	ENDS
PUBLIC	?convert@@YAEE@Z				; convert
; Function compile flags: /Odtp
_TEXT	SEGMENT
tv65 = -4						; size = 4
_ch$ = 8						; size = 1
?convert@@YAEE@Z PROC					; convert
; Line 134
	push	ebp
	mov	ebp, esp
	push	ecx
; Line 135
	movzx	eax, BYTE PTR _ch$[ebp]
	mov	DWORD PTR tv65[ebp], eax
	mov	ecx, DWORD PTR tv65[ebp]
	sub	ecx, 1
	mov	DWORD PTR tv65[ebp], ecx
	cmp	DWORD PTR tv65[ebp], 4
	ja	SHORT $LN5@convert
	mov	edx, DWORD PTR tv65[ebp]
	jmp	DWORD PTR $LN9@convert[edx*4]
$LN4@convert:
; Line 136
	mov	al, 1
	jmp	SHORT $LN7@convert
$LN3@convert:
; Line 137
	mov	al, 4
	jmp	SHORT $LN7@convert
$LN2@convert:
; Line 138
	mov	al, 3
	jmp	SHORT $LN7@convert
$LN1@convert:
; Line 139
	mov	al, 2
	jmp	SHORT $LN7@convert
$LN5@convert:
; Line 141
	xor	al, al
$LN7@convert:
; Line 142
	mov	esp, ebp
	pop	ebp
	ret	0
	npad	2
$LN9@convert:
	DD	$LN4@convert
	DD	$LN3@convert
	DD	$LN2@convert
	DD	$LN5@convert
	DD	$LN1@convert
?convert@@YAEE@Z ENDP					; convert
_TEXT	ENDS
PUBLIC	_main
; Function compile flags: /Odtp
_TEXT	SEGMENT
_idir$ = -1						; size = 1
_main	PROC
; Line 143
	push	ebp
	mov	ebp, esp
	push	ecx
; Line 144
	call	?init@@YAXXZ				; init
; Line 145
	mov	BYTE PTR _idir$[ebp], 0
; Line 146
	movzx	eax, BYTE PTR _idir$[ebp]
	push	eax
	call	?convert@@YAEE@Z			; convert
	add	esp, 4
	mov	BYTE PTR _idir$[ebp], al
; Line 147
	movzx	ecx, BYTE PTR _idir$[ebp]
	push	ecx
	call	?move@@YAXE@Z				; move
	add	esp, 4
; Line 148
	call	?createOutputData@@YAXXZ		; createOutputData
; Line 149
	xor	eax, eax
; Line 150
	mov	esp, ebp
	pop	ebp
	ret	0
_main	ENDP
_TEXT	ENDS
END
