# Makefile для Teleport VX Next

CC   = i386-elf-gcc
LD   = i386-elf-ld
AS   = nasm

CFLAGS  = -ffreestanding -O2 -Wall -Wextra -m32
LDFLAGS = -T linker.ld -nostdlib

KERNEL_OBJS = \
    kernel/kernel.o \
    kernel/task.o \
    kernel/scheduler.o \
    kernel/space.o \
    kernel/system_space.o \
    kernel/capability.o \
    kernel/ipc.o \
    kernel/test_tasks.o

BOOT_OBJS = boot/boot.o

all: kernel.elf

boot/boot.o: boot/boot.asm
	$(AS) -f elf32 $< -o $@

kernel/%.o: kernel/%.c
	$(CC) $(CFLAGS) -c $< -o $@

kernel.elf: $(BOOT_OBJS) $(KERNEL_OBJS)
	$(LD) $(LDFLAGS) -o $@ $(BOOT_OBJS) $(KERNEL_OBJS)

clean:
	rm -f $(KERNEL_OBJS) $(BOOT_OBJS) kernel.elf
