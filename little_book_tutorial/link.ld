ENTRY(loader)

SECTIONS {
    . = 0x00100000;     /* load code at 1MB after GRUB */

    /* align text, read-only data, data, common, and bss sections at 4kb */    
    .text ALIGN (0x1000):
    {
        *(.text)
    }
    .rodata ALIGN (0x1000):
    {
        *(.rodata*)
    }
    .data ALIGN (0x1000):
    {
        *(.data)
    }
    .bss ALIGN (0x1000):
    {
        *(COMMON)
        *(.bss)
    }
}