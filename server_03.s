	.file	"server_03.c"
	.text
	.section	.rodata
	.align 8
.LC0:
	.string	"entering main function successful"
.LC1:
	.string	"socket"
.LC2:
	.string	"creating socket successful"
.LC3:
	.string	"/tmp/unix_sock"
.LC4:
	.string	"removing file"
	.align 8
.LC5:
	.string	"removing old socket successful"
.LC6:
	.string	"bind"
.LC7:
	.string	"listen"
.LC8:
	.string	"listen successful"
.LC9:
	.string	"Accepting failed"
.LC10:
	.string	"Received message: %.*s\n"
.LC11:
	.string	"write failed!"
	.text
	.globl	main
	.type	main, @function
main:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$416, %rsp
	movl	%edi, -404(%rbp)
	movq	%rsi, -416(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %edx
	movl	$1, %esi
	movl	$1, %edi
	call	socket@PLT
	movl	%eax, -400(%rbp)
	cmpl	$-1, -400(%rbp)
	jne	.L2
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	perror@PLT
	movl	$1, %edi
	call	exit@PLT
.L2:
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	remove@PLT
	cmpl	$-1, %eax
	jne	.L3
	call	__errno_location@PLT
	movl	(%rax), %eax
	cmpl	$2, %eax
	je	.L3
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	call	perror@PLT
	movl	$1, %edi
	call	exit@PLT
.L3:
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	-384(%rbp), %rax
	movl	$110, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset@PLT
	movw	$1, -384(%rbp)
	leaq	-384(%rbp), %rax
	addq	$2, %rax
	movl	$107, %edx
	leaq	.LC3(%rip), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	strncpy@PLT
	leaq	-384(%rbp), %rcx
	movl	-400(%rbp), %eax
	movl	$110, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	bind@PLT
	cmpl	$-1, %eax
	jne	.L4
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	call	perror@PLT
	movl	-400(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	movl	$-1, %edi
	call	exit@PLT
.L4:
	movl	-400(%rbp), %eax
	movl	$5, %esi
	movl	%eax, %edi
	call	listen@PLT
	cmpl	$-1, %eax
	jne	.L5
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	call	perror@PLT
	movl	$-1, %edi
	call	exit@PLT
.L5:
	leaq	.LC8(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L10:
	movl	-400(%rbp), %eax
	movl	$0, %edx
	movl	$0, %esi
	movl	%eax, %edi
	call	accept@PLT
	movl	%eax, -396(%rbp)
	cmpl	$-1, -396(%rbp)
	jne	.L8
	leaq	.LC9(%rip), %rax
	movq	%rax, %rdi
	call	perror@PLT
	movl	-400(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	movl	$1, %edi
	call	exit@PLT
.L9:
	movq	-392(%rbp), %rax
	movl	%eax, %ecx
	leaq	-272(%rbp), %rax
	movq	%rax, %rdx
	movl	%ecx, %esi
	leaq	.LC10(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-392(%rbp), %rdx
	leaq	-272(%rbp), %rax
	movq	%rax, %rsi
	movl	$1, %edi
	call	write@PLT
	cmpq	%rax, -392(%rbp)
	je	.L8
	leaq	.LC11(%rip), %rax
	movq	%rax, %rdi
	call	perror@PLT
.L8:
	leaq	-272(%rbp), %rcx
	movl	-396(%rbp), %eax
	movl	$256, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	read@PLT
	movq	%rax, -392(%rbp)
	cmpq	$0, -392(%rbp)
	jg	.L9
	jmp	.L10
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 12.2.0-17ubuntu1) 12.2.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
