	.file	"philo.c"
	.text
	.globl	ft_date_update
	.type	ft_date_update, @function
ft_date_update:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	addq	$16, %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	gettimeofday@PLT
	testl	%eax, %eax
	jne	.L3
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	imulq	$1000, %rax, %rsi
	movq	-8(%rbp), %rax
	movq	24(%rax), %rcx
	movabsq	$2361183241434822607, %rdx
	movq	%rcx, %rax
	imulq	%rdx
	movq	%rdx, %rax
	sarq	$7, %rax
	sarq	$63, %rcx
	movq	%rcx, %rdx
	subq	%rdx, %rax
	leaq	(%rsi,%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 32(%rax)
.L3:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	ft_date_update, .-ft_date_update
	.section	.rodata
.LC0:
	.string	"%lu %u %s\n"
	.text
	.globl	ft_push_log
	.type	ft_push_log, @function
ft_push_log:
.LFB7:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	ft_date_update
	movq	-8(%rbp), %rax
	movl	80(%rax), %edx
	movq	-8(%rbp), %rax
	movq	32(%rax), %rax
	movq	-16(%rbp), %rcx
	movq	%rax, %rsi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	ft_push_log, .-ft_push_log
	.globl	ft_eat
	.type	ft_eat, @function
ft_eat:
.LFB8:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	96(%rax), %rax
	movl	84(%rax), %eax
	testl	%eax, %eax
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	ft_eat, .-ft_eat
	.section	.rodata
.LC1:
	.string	"Soy el hilo: %u\n"
	.text
	.globl	ft_life_philo
	.type	ft_life_philo, @function
ft_life_philo:
.LFB9:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	addq	$48, %rax
	movq	%rax, %rdi
	call	pthread_mutex_lock@PLT
	movq	-16(%rbp), %rax
	movq	96(%rax), %rcx
	movq	-16(%rbp), %rax
	movl	88(%rax), %eax
	leal	-1(%rax), %edx
	movq	-16(%rbp), %rax
	movl	%edx, 88(%rax)
	movq	-16(%rbp), %rax
	movl	88(%rax), %eax
	movl	%eax, %edx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movq	%rax, -8(%rbp)
	movq	-16(%rbp), %rax
	movl	88(%rax), %edx
	movq	-8(%rbp), %rax
	movl	%edx, 80(%rax)
	movq	-8(%rbp), %rax
	movl	80(%rax), %eax
	movl	%eax, %esi
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-16(%rbp), %rax
	addq	$48, %rax
	movq	%rax, %rdi
	call	pthread_mutex_unlock@PLT
	movq	-8(%rbp), %rax
	movl	$1, 84(%rax)
	movq	-16(%rbp), %rax
	movl	4(%rax), %edx
	movq	-8(%rbp), %rax
	movl	%edx, (%rax)
	movq	-16(%rbp), %rax
	movl	8(%rax), %edx
	movq	-8(%rbp), %rax
	movl	%edx, 4(%rax)
	movq	-16(%rbp), %rax
	movl	12(%rax), %edx
	movq	-8(%rbp), %rax
	movl	%edx, 8(%rax)
	movq	-8(%rbp), %rax
	movl	$0, 88(%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	ft_date_update
	nop
.L8:
	movq	-16(%rbp), %rax
	movzwl	40(%rax), %eax
	testw	%ax, %ax
	jne	.L8
	jmp	.L9
.L10:
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	ft_eat
.L9:
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	jne	.L10
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	ft_life_philo, .-ft_life_philo
	.globl	ft_init_philo
	.type	ft_init_philo, @function
ft_init_philo:
.LFB10:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	addl	$1, %eax
	cltq
	salq	$3, %rax
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, 32(%rax)
	movq	-24(%rbp), %rax
	movl	16(%rax), %eax
	testl	%eax, %eax
	je	.L13
	movl	-4(%rbp), %eax
	cltq
	salq	$2, %rax
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, 24(%rax)
	movq	-24(%rbp), %rax
	movq	24(%rax), %rax
	testq	%rax, %rax
	jne	.L14
	movl	$-1, %edi
	call	exit@PLT
.L14:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	movl	16(%rax), %ecx
	movq	-24(%rbp), %rax
	movq	24(%rax), %rax
	movl	%ecx, %esi
	movq	%rax, %rdi
	call	memset@PLT
.L13:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, 96(%rax)
	movq	-24(%rbp), %rax
	movq	32(%rax), %rax
	testq	%rax, %rax
	je	.L15
	movq	-24(%rbp), %rax
	movq	96(%rax), %rax
	testq	%rax, %rax
	jne	.L16
.L15:
	movl	$-1, %edi
	call	exit@PLT
.L16:
	movq	-24(%rbp), %rax
	movq	32(%rax), %rdx
	movl	-4(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	%rdx, %rax
	movq	$0, (%rax)
	movq	-24(%rbp), %rax
	addq	$48, %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_mutex_init@PLT
	movq	-24(%rbp), %rax
	movw	$1, 40(%rax)
	movl	-4(%rbp), %edx
	movq	-24(%rbp), %rax
	movl	%edx, 88(%rax)
	movq	-24(%rbp), %rax
	movq	96(%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	leaq	-104(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	96(%rax), %rax
	addq	%rcx, %rdx
	movq	%rdx, 96(%rax)
	jmp	.L17
.L18:
	movq	-24(%rbp), %rax
	movq	32(%rax), %rdx
	movl	-4(%rbp), %eax
	cltq
	salq	$3, %rax
	leaq	(%rdx,%rax), %rdi
	movq	-24(%rbp), %rax
	movq	%rax, %rcx
	leaq	ft_life_philo(%rip), %rax
	movq	%rax, %rdx
	movl	$0, %esi
	call	pthread_create@PLT
	cmpl	$0, -4(%rbp)
	jle	.L17
	movq	-24(%rbp), %rax
	movq	96(%rax), %rcx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	leaq	-104(%rax), %rdi
	movq	-24(%rbp), %rax
	movq	96(%rax), %rsi
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	%rsi, %rax
	leaq	(%rcx,%rdi), %rdx
	movq	%rdx, 96(%rax)
.L17:
	movl	-4(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, -4(%rbp)
	testl	%eax, %eax
	jne	.L18
	movq	-24(%rbp), %rax
	movw	$0, 40(%rax)
	movq	-24(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, -4(%rbp)
	jmp	.L19
.L20:
	movq	-24(%rbp), %rax
	movq	32(%rax), %rdx
	movl	-4(%rbp), %eax
	cltq
	salq	$3, %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_join@PLT
.L19:
	movl	-4(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, -4(%rbp)
	testl	%eax, %eax
	jne	.L20
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	ft_init_philo, .-ft_init_philo
	.globl	main
	.type	main, @function
main:
.LFB11:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	addq	$-128, %rsp
	movl	%edi, -116(%rbp)
	movq	%rsi, -128(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	-112(%rbp), %rdx
	movq	-128(%rbp), %rcx
	movl	-116(%rbp), %eax
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	ft_init_args@PLT
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	ft_init_philo
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L23
	call	__stack_chk_fail@PLT
.L23:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
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
