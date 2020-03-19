	.text
	.file	"kernel.cpp"
	.globl	kernel_start            # -- Begin function kernel_start
	.p2align	4, 0x90
	.type	kernel_start,@function
kernel_start:                           # @kernel_start
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rdi
	callq	_Z6kernelP11FrameBuffer
	addq	$16, %rsp
	popq	%rbp
	retq
.Lfunc_end0:
	.size	kernel_start, .Lfunc_end0-kernel_start
	.cfi_endproc
                                        # -- End function
	.globl	_Z6kernelP11FrameBuffer # -- Begin function _Z6kernelP11FrameBuffer
	.p2align	4, 0x90
	.type	_Z6kernelP11FrameBuffer,@function
_Z6kernelP11FrameBuffer:                # @_Z6kernelP11FrameBuffer
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$80, %rsp
	movq	%rdi, -8(%rbp)
	movl	.L_ZZ6kernelP11FrameBufferE3Red, %eax
	movl	%eax, -16(%rbp)
	movslq	p, %rdi
	movq	%rdi, -24(%rbp)
.LBB1_1:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB1_3 Depth 2
	movq	-24(%rbp), %rax
	movq	-8(%rbp), %rcx
	movl	16(%rcx), %edx
	movl	%edx, %ecx
	cmpq	%rcx, %rax
	jae	.LBB1_8
# %bb.2:                                #   in Loop: Header=BB1_1 Depth=1
	movslq	p, %rax
	movq	%rax, -32(%rbp)
.LBB1_3:                                #   Parent Loop BB1_1 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movq	-32(%rbp), %rax
	movq	-8(%rbp), %rcx
	movl	20(%rcx), %edx
	movl	%edx, %ecx
	cmpq	%rcx, %rax
	jae	.LBB1_6
# %bb.4:                                #   in Loop: Header=BB1_3 Depth=2
	movabsq	$p, %r8
	movq	-24(%rbp), %rax
	movl	%eax, %ecx
	movq	-32(%rbp), %rax
	movl	%eax, %edx
	callq	check_hlt
	movq	-24(%rbp), %rax
	movl	%eax, %ecx
	movq	-32(%rbp), %rax
	movl	%eax, %edx
	movl	-16(%rbp), %esi
	movl	%esi, -40(%rbp)
	movq	-8(%rbp), %rax
	movl	-40(%rbp), %esi
	movl	%ecx, %edi
	movl	%esi, -44(%rbp)         # 4-byte Spill
	movl	%edx, %esi
	movl	-44(%rbp), %edx         # 4-byte Reload
	movq	%rax, %rcx
	callq	_Z10draw_pixeljj11PixelFormatP11FrameBuffer
# %bb.5:                                #   in Loop: Header=BB1_3 Depth=2
	movq	-32(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -32(%rbp)
	jmp	.LBB1_3
.LBB1_6:                                #   in Loop: Header=BB1_1 Depth=1
	jmp	.LBB1_7
.LBB1_7:                                #   in Loop: Header=BB1_1 Depth=1
	movq	-24(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -24(%rbp)
	jmp	.LBB1_1
.LBB1_8:
	movabsq	$.L.str, %rsi
	movq	-8(%rbp), %rdi
	callq	_Z4putsP11FrameBufferPc
	callq	sleep_hlt
	addq	$80, %rsp
	popq	%rbp
	retq
.Lfunc_end1:
	.size	_Z6kernelP11FrameBuffer, .Lfunc_end1-_Z6kernelP11FrameBuffer
	.cfi_endproc
                                        # -- End function
	.type	p,@object               # @p
	.data
	.globl	p
	.p2align	2
p:
	.long	100                     # 0x64
	.size	p, 4

	.type	.L_ZZ6kernelP11FrameBufferE3Red,@object # @_ZZ6kernelP11FrameBufferE3Red
	.section	.rodata.cst4,"aM",@progbits,4
.L_ZZ6kernelP11FrameBufferE3Red:
	.byte	255                     # 0xff
	.byte	255                     # 0xff
	.byte	255                     # 0xff
	.byte	255                     # 0xff
	.size	.L_ZZ6kernelP11FrameBufferE3Red, 4

	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"KizunaOS boot up!\n"
	.size	.L.str, 19


	.ident	"clang version 6.0.0-1ubuntu2 (tags/RELEASE_600/final)"
	.section	".note.GNU-stack","",@progbits
