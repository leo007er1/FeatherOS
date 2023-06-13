
IsoName := FeatherOS.iso
BuildDir := Build
KernelName := Kernel.elf
CC := gcc
LD := ld

# All the flags for linker and compiler
CFlags ?= -Wall -Wextra -std=gnu11 -ffreestanding -fno-stack-protector -fno-stack-check -fno-lto -fno-PIE -fno-PIC \
	-m64 -march=x86-64 -mabi=sysv -mno-80387 -mno-mmx -mno-sse -mno-sse2 -mno-red-zone -mcmodel=kernel -I Kernel/Include/

NasmFlags ?= -F dwarf -g
LdFlags ?= -nostdlib -static -m elf_x86_64 -z max-page-size=0x1000 -no-pie -T Kernel/Linker.ld

# Finds all .c and .asm files and gets the .o file names
CFiles := $(shell find -L Kernel/ -type f -name '*.c')
NasmFiles := $(shell find -L Kernel/ -type f -name '*.asm')
Obj := $(addprefix $(BuildDir)/, $(patsubst %.c, %.o, $(CFiles)) $(patsubst %.asm, %.o, $(NasmFiles)))


.PHONY: all compile
all: CheckUser compile BuildIso

compile: limine.h $(KernelName)

$(KernelName): $(Obj)
	@echo -e "\n\e[0;32m==> Linking kernel...\e[0m"
	$(LD) $(Obj) $(LdFlags) -o $(BuildDir)/$@


$(addprefix $(BuildDir)/, %.o): %.c
	$(CC) $(CFlags) -c $< -o $@


$(addprefix $(BuildDir)/, %.o): %.asm
	nasm -f elf64 $< -o $@


BuildIso:
	@echo -e "\n\e[0;32m==> Building .iso image...\e[0m"

	@sudo rm -rf $(BuildDir)/IsoRoot/*
	@mkdir -p $(BuildDir)/IsoRoot
	@sudo cp -v $(BuildDir)/Kernel.elf Limine.cfg limine/limine.sys limine/limine-cd.bin limine/limine-cd-efi.bin 12.jpeg $(BuildDir)/IsoRoot

	xorriso -as mkisofs -b limine-cd.bin \
        -no-emul-boot -boot-load-size 4 -boot-info-table \
        --efi-boot limine-cd-efi.bin \
        -efi-boot-part --efi-boot-image --protective-msdos-label \
        $(BuildDir)/IsoRoot -o $(BuildDir)/$(IsoName)

	limine/limine-deploy $(BuildDir)/$(IsoName)


.PHONY: limine
limine:
	git clone https://github.com/limine-bootloader/limine.git --branch=v4.x-branch-binary --depth=1
	make -C limine


limine.h:
	@if ! [ -f $(BuildDir)/$@ ]; then \
		curl https://raw.githubusercontent.com/limine-bootloader/limine/trunk/limine.h -o $(BuildDir)/$@; \
	fi

	@echo -e "\n\e[0;32m==> Compiling Kernel...\e[0m"
	


# Checks if the user has permissions to create the image
CheckUser:
	@if ! [ "$(shell id -u)" = 0 ]; then \
		echo -e "\e[0;31mYou need to be root to create the image.\n\e[0mUse \"sudo su\" to give yourself permission or add \"sudo\" before your command\n"; \
		exit 1; \
	fi


.PHONY: run debug
run:
	@qemu-system-x86_64 -hda $(BuildDir)/$(IsoName) -d int

debug:
	@qemu-system-x86_64 -hda $(BuildDir)/$(IsoName) -d int -monitor stdio 

.PHONY: clean
clean:
	sudo rm -rf $(BuildDir)/*
	mkdir -p $(BuildDir)/Kernel/Arch/x86/CPU