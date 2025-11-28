; Teleport VX Next - boot.asm
; NASM, Multiboot 1

BITS 32

section .multiboot
align 4
    dd 0x1BADB002        ; magic
    dd 0x00000000        ; flags (0)
    dd -(0x1BADB002 + 0x00000000) ; checksum

section .text
global _start
extern vx_kernel_main

_start:
    cli                 ; отключаем прерывания
    call vx_kernel_main ; вызываем вход ядра

.hang:
    hlt                 ; остановка CPU
    jmp .hang
