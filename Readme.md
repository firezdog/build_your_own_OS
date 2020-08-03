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
* c flags
    * `-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror`