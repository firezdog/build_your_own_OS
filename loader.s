; the entry symbol for ELF
global loader

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
    mov eax, 0xCAFEBABE    ; put 0xCAFEBABE in the eax register
.loop:
    jmp .loop   ; loop forever
