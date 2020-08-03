# Setup
* Run `vagrant up`
* `vagrant ssh` then `sudo apt install build-essential nasm genisoimage bochs bochs-sdl`

# Hello CAFEBABE
* to compile, run `nasm -f elf32 -g loader.s`
* link with the link.ld with `ld -T link.ld -melf_i386 loader.o -o kernel.elf`

## Building CAFEBABE
```
mkdir -p iso/boot/grub
cp stage2_eltorito iso/boot/grub/
cp kernel.elf iso/boot/
cp menu.lst iso/boot/grub/

genisoimage -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -A os -input-charset utf8 -quiet -boot-info-table -o os.iso iso
```

## Running OS in Bochs
`bochs -f bochsrc.txt -q`
* use con(-f)iguration file bochsrc.txt and (-q) skip the interactive prompt
* make sure your Vagrant / setup has a windows manager, or bochs will not be able to start properly
* you may need to prompt bochs to continue in order for it to start booting into GRUB
* `cat bochslog.txt` after quitting should show 'cafebabe' in the EAX register -- or you can directly inspect (`x eax`)

# Using C
* prerequisite: have a stack, esp points to beginning
    * method: reserve in bss section using `resb` (reserve bytes?)
* calling c function from assembly using cdecl
* using __attribute__((packed)) for configuration bytes
* extern and call used to call defined function from assembly
* make run w/ makefile now deploys the os to bochs

# Output
* m-mapped i/o or i/o ports
    * i/o ports use `out <address> <data>` and `in <address> => data`

## framebuffer (mmap)
* start at 0x000B800, bits 15-8 = ascii, 7-4 fg, 3-0 bg color
    * black 0 white 15 red 4
    * eg `mov [0x000B800], word 0x4128` print green A on grey background
* we can write a function in C to make this easier to manage