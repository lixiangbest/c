	.file	"test.c"
	.section	.rodata
.LC0:
	.string	"linux.mk"
	.align 4
.LC1:
	.string	"STDIN_FILENO=%d,STDOUT_FILENO=%d,STDERR_FILENO=%d\n"
.LC2:
	.string	"f_desc=%d\n"
	.align 4
.LC3:
	.string	"%d,%d,%d,O_RDONLY|O_WRONLY|O_RDWR=%d"
.LC4:
	.string	"\nILP32_OFF32=%ld\n"
	.text
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$48, %esp
	movl	$2, (%esp)
	call	close
	movl	$0, 4(%esp)
	movl	$.LC0, (%esp)
	call	open
	movl	%eax, 44(%esp)
	movl	$.LC1, %eax
	movl	$2, 12(%esp)
	movl	$1, 8(%esp)
	movl	$0, 4(%esp)
	movl	%eax, (%esp)
	call	printf
	movl	$.LC2, %eax
	movl	44(%esp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	printf
	movl	$.LC3, %eax
	movl	$3, 16(%esp)
	movl	$2, 12(%esp)
	movl	$1, 8(%esp)
	movl	$0, 4(%esp)
	movl	%eax, (%esp)
	call	printf
	movl	$176, (%esp)
	call	sysconf
	movl	$.LC4, %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	printf
	leave
	ret
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5.1) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
