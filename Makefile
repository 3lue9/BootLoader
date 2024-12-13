CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
         -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -Wno-error=main -ggdb -c \
         -Ikernel/include -Ikernel/vga

AS = nasm
ASFLAGS = -f elf
LDFLAGS = -T link.ld -melf_i386

SRC_C = $(shell find kernel -type f -name '*.c')
SRC_ASM = $(shell find kernel -type f -name '*.asm')
OBJS = multiboot_header.o $(SRC_C:.c=.o) $(SRC_ASM:.asm=.o)

all: kernel iso

kernel: $(OBJS)
	ld $(LDFLAGS) $(OBJS) -o kernel.elf

iso: kernel
	mkdir -p iso
	mkdir -p iso/boot
	mkdir -p iso/boot/grub
	cp kernel.elf iso/boot/kernel.elf
	cp grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue -o os.iso iso/

run: iso
	qemu-system-i386 -boot d -cdrom os.iso -m 512 

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf $(OBJS)
	rm -rf os.iso
	rm -rf kernel.elf


