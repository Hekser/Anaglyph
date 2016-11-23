.data

maxValue REAL8 255.0
minValue REAL8 0.0

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

	;mov	qword ptr [rsp + 8h], rcx		; get unsigned char *leftPic
	;mov	qword ptr [rsp + 10h], rdx		; get unsigned char *rightPic
	mov dword ptr [rsp + 18h], r8d			; get int width
	;mov dword ptr [rsp + 20h], r9d			; get int height

	mov byte ptr [rsp + 28h], 0				; unsigned char pad = 0

; if ((width * 3) % 4 != 0)
	imul eax, dword ptr [rsp + 18h], 3		; width * 3
	and eax, 3								; (width * 3) % 4
	cmp eax, 0								; ((width * 3) % 4) != 0
	je falseIf								; jump if equal

; pad = 4 - ((width * 3) % 4)
	mov byte ptr [rsp + 28h], 4				; pad = 4
	sub byte ptr [rsp + 28h], al			; pad = 4 - ((width * 3) % 4)

falseIf:
	mov r10, 0								; r10 (pos) = 0

; for (int j = 0; j < height; ++j)
; for (int i = 0; i < width; ++i)
	j:										; inner loop
		;movzx r13d, byte ptr [rcx + r10 + 2]; red - left pic
		;movzx r14d, byte ptr [rcx + r10 + 1]; green - left pic
		;movzx r15d, byte ptr [rcx + r10 ]	; blue - left pic

; pixel conversion
		movzx eax, byte ptr [rcx + r10 + 2]	; eax = red - left pic
		cvtsi2sd xmm0, eax
		mulsd xmm0, rl1
		movaps xmm1, xmm0

		movzx eax, byte ptr [rcx + r10 + 1]	; eax = green - left pic
		cvtsi2sd xmm0, eax
		mulsd xmm0, rl2
		addsd xmm1, xmm0
		
		movzx eax, byte ptr [rcx + r10]		; eax = blue - left pic
		cvtsi2sd xmm0, eax
		mulsd xmm0, rl3
		addsd xmm1, xmm0

		movzx eax, byte ptr [rdx + r10 + 2]	; eax = red - right pic
		cvtsi2sd xmm0, eax
		mulsd xmm0, rr1
		subsd xmm1, xmm0

		movzx eax, byte ptr [rdx + r10 + 1]	; eax = green - right pic
		cvtsi2sd xmm0, eax
		mulsd xmm0, rr2
		subsd xmm1, xmm0

		movzx eax, byte ptr [rdx + r10]		; eax = blue - right pic
		cvtsi2sd xmm0, eax
		mulsd xmm0, rr3
		subsd xmm1, xmm0

		cvttsd2si rax, xmm1

; if (r > 255.0 && r < 0.0)
		
		;cmp rax, 0

; <><><><><><><><><><><><><>

		mov byte ptr [rcx + r10 + 2], al	; red - set pixel value

		; <><><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		movzx eax, byte ptr [rdx + r10 + 2]	; eax = red - right pic
		cvtsi2sd xmm0, eax
		mulsd xmm0, gr1
		movaps xmm1, xmm0

		movzx eax, byte ptr [rcx + r10 + 2]	; eax = red - left pic
		cvtsi2sd xmm0, eax
		mulsd xmm0, gl1
		subsd xmm1, xmm0

		movzx eax, byte ptr [rcx + r10 + 1]	; eax = green - left pic
		cvtsi2sd xmm0, eax
		mulsd xmm0, gl2
		subsd xmm1, xmm0

		movzx eax, byte ptr [rcx + r10]		; eax = blue - left pic
		cvtsi2sd xmm0, eax
		mulsd xmm0, gl3
		subsd xmm1, xmm0

		movzx eax, byte ptr [rdx + r10 + 1]	; eax = green - right pic
		cvtsi2sd xmm0, eax
		mulsd xmm0, gr2
		addsd xmm1, xmm0

		movzx eax, byte ptr [rdx + r10]		; eax = blue - right pic
		cvtsi2sd xmm0, eax
		mulsd xmm0, gr3
		subsd xmm1, xmm0

		cvttsd2si rax, xmm1
		mov byte ptr [rcx + r10 + 1], al	; green - set pixel value

		; <><><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

		movzx eax, byte ptr [rdx + r10]		; eax = blue - right pic
		cvtsi2sd xmm0, eax
		mulsd xmm0, br3
		movaps xmm1, xmm0

		movzx eax, byte ptr [rcx + r10 + 2]	; eax = red - left pic
		cvtsi2sd xmm0, eax
		mulsd xmm0, bl1
		subsd xmm1, xmm0

		movzx eax, byte ptr [rcx + r10 + 1]	; eax = green - left pic
		cvtsi2sd xmm0, eax
		mulsd xmm0, bl2
		subsd xmm1, xmm0

		movzx eax, byte ptr [rcx + r10]		; eax = blue - left pic
		cvtsi2sd xmm0, eax
		mulsd xmm0, bl3
		subsd xmm1, xmm0

		movzx eax, byte ptr [rdx + r10 + 2]	; eax = red - right pic
		cvtsi2sd xmm0, eax
		mulsd xmm0, br1
		subsd xmm1, xmm0

		movzx eax, byte ptr [rdx + r10 + 1]	; eax = green - right pic
		cvtsi2sd xmm0, eax
		mulsd xmm0, br2
		subsd xmm1, xmm0

		cvttsd2si rax, xmm1
		mov byte ptr [rcx + r10], al		; blue - set pixel value

; end of conversion
		add r10, 3							; r10 (pos) += 3
		dec r8								; --r8 (width)
		jnz j								; jump if not zero
	i:										; outer loop
		movsxd r8, dword ptr [rsp + 18h]	; r8 = width
		movzx eax, byte ptr [rsp + 28h]		; eax = pad
		add r10, rax						; r10 (pos) += pad
		dec r9								; --r9 (height)
		jz endLoop							; end of outer loop
		jmp j								; next inner loop

endLoop:
	ret

generate endp

end