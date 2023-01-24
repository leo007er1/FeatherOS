

KernelName := Kernel.elf
BuildDir := ../Build/Kernel

CC := gcc
LD := ld

# All the flags for linker and compiler
CFlags ?= -g -O3 -pipe -Wall -Wextra -ffreestanding -fno-stack-protector -fno-stack-check \
    -fno-lto -fno-pie -fno-pic -m64 -march=x86-64 -mabi=sysv -mno-80387 \
    -mno-mmx -mno-sse -mno-sse2 -mno-red-zone -mcmodel=kernel -MMD -I.

NasmFlags ?= -F dwarf -g
LdFLags ?= -nostdlib -static -m elf_x86_64 -z max-page-size=0x1000 -no-pie -T Linker.ld


# Finds all .c and .asm files and gets the .o file names
CFiles := $(shell find -type f -name '*.c')
NasmFiles := $(shell find -type f -name '*.asm')
# Obj := $(CFiles:.c=.o) $(NasmFiles:.asm=.o)
Obj = $(patsubst %.c, ../Build/Kernel/%.o, $(CFiles))



.PHONY: all
all: CheckUser limine.h $(KernelName)


$(KernelName): $(Obj)
	@echo -e "\n\e[0;32m==> Linking kernel...\e[0m"
	$(LD) $(Obj) $(LdFlags) -o $(BuildDir)/$@


%.o: %.c
	@$(CC) $(CFlags) -c $< -o $@


%.o: %.asm
	nasm -f elf64 $< -o $(BuildDir)/$@


limine.h:
	@if ! [ -f $(BuildDir)/$@ ]; then \
		curl https://raw.githubusercontent.com/limine-bootloader/limine/trunk/limine.h -o $(BuildDir)/$@; \
	fi

	@echo -e "\n\e[0;32m==> Compiling Kernel...\e[0m"


# Checks if the user has root permissions
CheckUser:
	@if ! [ "$(shell id -u)" = 0 ]; then \
		echo -e "\e[0;31mYou need to be root compile the kernel.\n\e[0mUse \"sudo su\" to give yourself permission or add a \"sudo\" before your command\n"; \
		exit 1; \
	fi


.PHONY: clean
clean:
	rm -rf $(BuildDir)/*
	mkdir -p $(BuildDir)/Arch/x86/CPU
