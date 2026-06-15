ASM=nasm
CC=gcc
LD=ld
ASMFLAGS=-f elf32
CFLAGS=-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -c -Ikernel/core -Ikernel/drivers/display -Ikernel/drivers/input -Ikernel/proc -Ikernel/mem -Ikernel/fs -Ikernel/shell -Ilibc
LDFLAGS=-m elf_i386 -T linker.ld

all: sles.iso

bootloader/boot.o: bootloader/boot.asm
	$(ASM) $(ASMFLAGS) $< -o $@

kernel/core/%.o: kernel/core/%.c
	$(CC) $(CFLAGS) $< -o $@

kernel/drivers/display/%.o: kernel/drivers/display/%.c
	$(CC) $(CFLAGS) $< -o $@

kernel/drivers/input/%.o: kernel/drivers/input/%.c
	$(CC) $(CFLAGS) $< -o $@

kernel/proc/%.o: kernel/proc/%.c
	$(CC) $(CFLAGS) $< -o $@

kernel/mem/%.o: kernel/mem/%.c
	$(CC) $(CFLAGS) $< -o $@

kernel/fs/%.o: kernel/fs/%.c
	$(CC) $(CFLAGS) $< -o $@

kernel/shell/%.o: kernel/shell/%.c
	$(CC) $(CFLAGS) $< -o $@

libc/%.o: libc/%.c
	$(CC) $(CFLAGS) $< -o $@

OBJS=bootloader/boot.o kernel/core/kernel.o kernel/core/login.o kernel/drivers/display/vga.o kernel/drivers/display/console.o kernel/drivers/input/keyboard.o kernel/proc/process.o kernel/proc/scheduler.o kernel/mem/paging.o kernel/mem/memory.o kernel/fs/file.o kernel/fs/vfs.o kernel/shell/commands.o kernel/shell/shell.o libc/string.o libc/stdio.o

sles.bin: $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $@

sles.iso: sles.bin
	@mkdir -p iso/boot/grub
	@cp sles.bin iso/boot/
	@echo 'set timeout=0' > iso/boot/grub/grub.cfg
	@echo 'set default=0' >> iso/boot/grub/grub.cfg
	@echo 'menuentry "Sierra Leone OS" {' >> iso/boot/grub/grub.cfg
	@echo '    multiboot /boot/sles.bin' >> iso/boot/grub/grub.cfg
	@echo '}' >> iso/boot/grub/grub.cfg
	@grub-mkrescue -o sles.iso iso/ 2>/dev/null
	@rm -rf iso/
	@echo "[DONE] sles.iso created!"

run: sles.iso
	qemu-system-i386 -cdrom sles.iso -m 128M -no-reboot

clean:
	rm -f bootloader/*.o kernel/core/*.o kernel/drivers/display/*.o kernel/drivers/input/*.o kernel/proc/*.o kernel/mem/*.o kernel/fs/*.o kernel/shell/*.o libc/*.o sles.bin sles.iso
	rm -rf iso/
