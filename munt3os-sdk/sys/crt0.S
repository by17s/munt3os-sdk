.global _start
.section .text
_start:
    xorq %rbp, %rbp
    movq $0, %rdi      # Опционально: заглушка argc
    movq $0, %rsi      # Опционально: заглушка argv
    andq $-16, %rsp    # Выравнивание стека по 16 байт
    call main
    movq %rax, %rdi
    call _exit
