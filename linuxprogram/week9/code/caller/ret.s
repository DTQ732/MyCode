	.file	"ret.c"
	.globl	addr
	.bss
	.align 4
	.type	addr, @object
	.size	addr, 4
addr:
	.zero	4
	.section	.rodata
.LC0:
	.string	"loop %x\n"
.LC1:
	.string	"p    %x\n"
.LC2:
	.string	"add -4 %x\n"
.LC3:
	.string	"add +4 %x\n"
.LC4:
	.string	"$p = %d\n"
	.text
	.globl	loop
	.type	loop, @function
loop:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	subl	$8, %esp
	pushl	$loop
	pushl	$.LC0
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	leal	8(%ebp), %eax
	pushl	%eax
	pushl	$.LC1
	call	printf
	addl	$16, %esp
	leal	4(%ebp), %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$.LC2
	call	printf
	addl	$16, %esp
	leal	4(%ebp), %eax
	movl	$loop, %edx
	movl	%edx, (%eax)
	leal	12(%ebp), %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$.LC3
	call	printf
	addl	$16, %esp
	leal	12(%ebp), %eax
	movl	$loop, %edx
	movl	%edx, (%eax)
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$.LC4
	call	printf
	addl	$16, %esp
	movl	8(%ebp), %eax
	addl	$4, %eax
	movl	%eax, 8(%ebp)
	call	getchar
	movl	$0, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	loop, .-loop
	.section	.rodata
.LC5:
	.string	"end"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	movl	%esp, %ebp
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x7c,0x6
	subl	$20, %esp
	movl	%gs:20, %eax
	movl	%eax, -12(%ebp)
	xorl	%eax, %eax
	movl	$1, -20(%ebp)
	leal	-20(%ebp), %eax
	movl	%eax, -16(%ebp)
	subl	$12, %esp
	pushl	-16(%ebp)
	call	loop
	addl	$16, %esp
	subl	$12, %esp
	pushl	$.LC5
	call	puts
	addl	$16, %esp
	movl	$0, %eax
	movl	-12(%ebp), %edx
	xorl	%gs:20, %edx
	je	.L5
	call	__stack_chk_fail
.L5:
	movl	-4(%ebp), %ecx
	.cfi_def_cfa 1, 0
	leave
	.cfi_restore 5
	leal	-4(%ecx), %esp
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.11) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
