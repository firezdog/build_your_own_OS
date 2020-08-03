; the entry symbol for ELF
global loader

; allocating memory for a C stack
KERNEL_STACK_SIZE equ 4096
section .bss
align 4
kernel_stack:
    resb KERNEL_STACK_SIZE

; multi-boot flags -- magic number + checksum + flags = 0
MAGIC_NUMBER equ 0x1BADB002
FLAGS equ 0x0 
CHECKSUM equ -MAGIC_NUMBER
; 4 byte aligned code -- write constants to machine code
section .text:
align 4
    dd MAGIC_NUMBER
    dd FLAGS
    dd CHECKSUM

loader:
    mov esp, kernel_stack + KERNEL_STACK_SIZE     ; move stack pointer to start of allocated stack
    extern kmain
    call kmain
.loop:
    jmp .loop   ; loop forever
