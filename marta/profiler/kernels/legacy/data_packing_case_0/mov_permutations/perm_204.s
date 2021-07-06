	.file	"data_packing_case_0.c"
	.intel_syntax noprefix
	.text
	.p2align 4
	.globl	data_packing_case_0
	.type	data_packing_case_0, @function
data_packing_case_0:
.LFB5277:
	.cfi_startproc
	vmovq	xmm1, QWORD PTR [rdx]
	vmovhps	xmm1, xmm1, QWORD PTR [rdx+168]
	vmovq	xmm0, QWORD PTR [rsi]
	vmovq	xmm0, QWORD PTR [rdi]
	vmovhps	xmm2, xmm0, QWORD PTR [rdi+168]
	vmovhps	xmm0, xmm0, QWORD PTR [rsi+168]
	vfmadd132ps	xmm0, xmm1, xmm2
	vfmadd231ps	xmm1, xmm2, xmm0
	vmovlps	QWORD PTR [rdx], xmm1
	vmovhps	QWORD PTR [rdx+168], xmm1
	ret
	.cfi_endproc
.LFE5277:
	.size	data_packing_case_0, .-data_packing_case_0
	.ident	"GCC: (GNU) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
