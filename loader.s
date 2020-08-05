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
    extern kmain
loader:
    mov esp, kernel_stack + KERNEL_STACK_SIZE     ; move stack pointer to start of allocated stack
    .loop:
        call kmain
        ; put 0x0050 into the frame buffer cursor port
        mov eax, 14
        out 0x3D4, eax  ; put the first 8 bits
        mov eax, 0x00
        out 0x3D5, eax
        mov eax, 15 ; put the last 8 bits
        out 0x3D4, eax
        mov eax, 0xFF
        out 0x3D5, eax
        jmp .loop