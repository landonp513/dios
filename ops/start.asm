bits 32 ; Grub starts cpu in 16 bit mode, so we need to tell the assembler that our code is 32 bit
global _start ; defines the entry point
extern kernel_early ; defines an external function in our C code for pre-kernel operations
extern main ; defines an external function in our C code for the main function and entry point for our kernel

section .text ; start of the text section, used for our main ASM code
    align 4 ; align the code to 4 bytes
    dd 0x1BADB002 ; magic number for multiboot
    dd 0x00 ; flags
    dd - (0x1BADB002 + 0x00) ; checksum

_start: ; starts kernel prep
    cli ; clear interupts
    mov esp, stack ; sets the pointer to the stack
    call kernel_early ; starts the kernel prep
    call main ; starts the main kernel
    hlt ; halts the cpu

section .bss ; used to define variables
    resb 8192 ; reserve 8192 bytes for the stack
    stack: ; defines the stack