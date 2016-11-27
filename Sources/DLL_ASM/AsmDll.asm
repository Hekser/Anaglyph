.data

rl1 REAL8 0.4561		; +
rl2 REAL8 0.500484		; +
rl3 REAL8 0.176381		; +

rr1 REAL8 0.0434706		; -
rr2 REAL8 0.0879388		; -
rr3 REAL8 0.00155529	; -

gl1 REAL8 0.0400822		; -
gl2 REAL8 0.0378246		; -
gl3 REAL8 0.0157589		; -

gr1 REAL8 0.378476		; +
gr2 REAL8 0.73364		; +
gr3 REAL8 0.0184503		; -

bl1 REAL8 0.0152161		; -
bl2 REAL8 0.0205971		; -
bl3 REAL8 0.00546856	; -

br1 REAL8 0.0721527		; -
br2 REAL8 0.112961		; -
br3 REAL8 1.2264		; +

.code

generate PROC

	emms										; When the CPU is in MMX mode, it sets the unused fpu bits to invalid values, which will cause any floating point instructions to behave strangely

	;mov	qword ptr [rsp + 8h], rcx			; get unsigned char *leftPic
	;mov	qword ptr [rsp + 10h], rdx			; get unsigned char *rightPic
	mov dword ptr [rsp + 18h], r8d				; get int width
	;mov dword ptr [rsp + 20h], r9d				; get int height

	mov byte ptr [rsp + 28h], 0					; unsigned char pad = 0

; if ((width * 3) % 4 != 0)
	imul eax, dword ptr [rsp + 18h], 3			; width * 3
	and eax, 3									; (width * 3) % 4
	cmp eax, 0									; ((width * 3) % 4) != 0
	je falseIf									; jump if equal

; pad = 4 - ((width * 3) % 4)
	mov byte ptr [rsp + 28h], 4					; pad = 4
	sub byte ptr [rsp + 28h], al				; pad = 4 - ((width * 3) % 4)

falseIf:
	mov r10, 0									; r10 (pos) = 0

; for (int j = 0; j < height; ++j)
; for (int i = 0; i < width; ++i)
	j:											; inner loop

; tests <><><><><><><><><><><><><><><><><><><><><><><><><><><>

; SSE
		;movaps xmm0, [rcx]						; Moves a 128bit value

			; xmm0 -> first 64bit	g2b2 r1g1b1 r0g0b0
			; xmm0 -> second 64bit	b5 r4g4b4 r3g3b3 r2
; MMX
		;movq xmm1, rl1

; SSE
		;movhps xmm2, rl1						; Moves 64bit value into top half of an xmm register
		;movlps xmm3, qword ptr [rdx]			; Moves 64bit value into bottom half of an xmm register

; SSE2
		;mulpd xmm1, xmm0

		;pmaddwd mm0, mm1

; SSE2
		; cvtsi2sd - Converts a 32bit integer to the bottom 64bit double
		; mulsd - Multiplies bottom 64bit doubles
		; addsd - Adds bottom 64bit doubles
		; subsd - Subtracts bottom 64bit doubles
		; cvttsd2si - Converts a 64bit double to a 32bit integer using truncation into a GPR

; <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

; r = 0.4561 * leftPic[pos + 2] + 0.500484 * leftPic[pos + 1] + 0.176381 * leftPic[pos] - 0.0434706 * rightPic[pos + 2] - 0.0879388 * rightPic[pos + 1] - 0.00155529 * rightPic[pos]
		movzx eax, byte ptr [rcx + r10 + 2]		; eax = red - left pic
		cvtsi2sd xmm0, eax
		mulsd xmm0, rl1
		movaps xmm1, xmm0

		movzx eax, byte ptr [rcx + r10 + 1]		; eax = green - left pic
		cvtsi2sd xmm0, eax
		mulsd xmm0, rl2
		addsd xmm1, xmm0
		
		movzx eax, byte ptr [rcx + r10]			; eax = blue - left pic
		cvtsi2sd xmm0, eax
		mulsd xmm0, rl3
		addsd xmm1, xmm0

		movzx eax, byte ptr [rdx + r10 + 2]		; eax = red - right pic
		cvtsi2sd xmm0, eax
		mulsd xmm0, rr1
		subsd xmm1, xmm0

		movzx eax, byte ptr [rdx + r10 + 1]		; eax = green - right pic
		cvtsi2sd xmm0, eax
		mulsd xmm0, rr2
		subsd xmm1, xmm0

		movzx eax, byte ptr [rdx + r10]			; eax = blue - right pic
		cvtsi2sd xmm0, eax
		mulsd xmm0, rr3
		subsd xmm1, xmm0

		cvttsd2si rax, xmm1

		cmp rax, 255
		jle falseRedMax							; jump if lower or equal
		mov rax, 255
falseRedMax:
		cmp rax, 0
		jge falseRedMin							; jump if greater or equal
		mov rax, 0
falseRedMin:

		mov byte ptr [rcx + r10 + 2], al		; red - set pixel value

; g = -0.0400822 * leftPic[pos + 2] - 0.0378246 * leftPic[pos + 1] - 0.0157589 * leftPic[pos] + 0.378476 * rightPic[pos + 2] + 0.73364 * rightPic[pos + 1] - 0.0184503 * rightPic[pos]

		movzx eax, byte ptr [rdx + r10 + 2]		; eax = red - right pic
		cvtsi2sd xmm0, eax
		mulsd xmm0, gr1
		movaps xmm1, xmm0

		movzx eax, byte ptr [rcx + r10 + 2]		; eax = red - left pic
		cvtsi2sd xmm0, eax
		mulsd xmm0, gl1
		subsd xmm1, xmm0

		movzx eax, byte ptr [rcx + r10 + 1]		; eax = green - left pic
		cvtsi2sd xmm0, eax
		mulsd xmm0, gl2
		subsd xmm1, xmm0

		movzx eax, byte ptr [rcx + r10]			; eax = blue - left pic
		cvtsi2sd xmm0, eax
		mulsd xmm0, gl3
		subsd xmm1, xmm0

		movzx eax, byte ptr [rdx + r10 + 1]		; eax = green - right pic
		cvtsi2sd xmm0, eax
		mulsd xmm0, gr2
		addsd xmm1, xmm0

		movzx eax, byte ptr [rdx + r10]			; eax = blue - right pic
		cvtsi2sd xmm0, eax
		mulsd xmm0, gr3
		subsd xmm1, xmm0

		cvttsd2si rax, xmm1

		cmp rax, 255
		jle falseGreenMax						; jump if lower or equal
		mov rax, 255
falseGreenMax:
		cmp rax, 0
		jge falseGreenMin						; jump if greater or equal
		mov rax, 0
falseGreenMin:

		mov byte ptr [rcx + r10 + 1], al		; green - set pixel value

; b = -0.0152161 * leftPic[pos + 2] - 0.0205971 * leftPic[pos + 1] - 0.00546856 * leftPic[pos] - 0.0721527 * rightPic[pos + 2] - 0.112961 * rightPic[pos + 1] + 1.2264 * rightPic[pos]

		movzx eax, byte ptr [rdx + r10]			; eax = blue - right pic
		cvtsi2sd xmm0, eax
		mulsd xmm0, br3
		movaps xmm1, xmm0

		movzx eax, byte ptr [rcx + r10 + 2]		; eax = red - left pic
		cvtsi2sd xmm0, eax
		mulsd xmm0, bl1
		subsd xmm1, xmm0

		movzx eax, byte ptr [rcx + r10 + 1]		; eax = green - left pic
		cvtsi2sd xmm0, eax
		mulsd xmm0, bl2
		subsd xmm1, xmm0

		movzx eax, byte ptr [rcx + r10]			; eax = blue - left pic
		cvtsi2sd xmm0, eax
		mulsd xmm0, bl3
		subsd xmm1, xmm0

		movzx eax, byte ptr [rdx + r10 + 2]		; eax = red - right pic
		cvtsi2sd xmm0, eax
		mulsd xmm0, br1
		subsd xmm1, xmm0

		movzx eax, byte ptr [rdx + r10 + 1]		; eax = green - right pic
		cvtsi2sd xmm0, eax
		mulsd xmm0, br2
		subsd xmm1, xmm0

		cvttsd2si rax, xmm1

		cmp rax, 255
		jle falseBlueMax						; jump if lower or equal
		mov rax, 255
falseBlueMax:
		cmp rax, 0
		jge falseBlueMin						; jump if greater or equal
		mov rax, 0
falseBlueMin:

		mov byte ptr [rcx + r10], al			; blue - set pixel value

; <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

		add r10, 3								; r10 (pos) += 3
		dec r8									; --r8 (width)
		jnz j									; jump if not zero
	i:											; outer loop
		movsxd r8, dword ptr [rsp + 18h]		; r8 = width
		movzx eax, byte ptr [rsp + 28h]			; eax = pad
		add r10, rax							; r10 (pos) += pad
		dec r9									; --r9 (height)
		jz endLoop								; end of outer loop
		jmp j									; next inner loop

endLoop:
	ret

generate endp

end