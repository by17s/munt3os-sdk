.global _start
.section .text
_start:
    xorq %rbp, %rbp
    andq $-16, %rsp    
    call main
    movq %rax, %rdi
    call _exit
