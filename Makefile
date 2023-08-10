
override IsoName := FeatherOS.iso
override BuildDir := Build/
override KernelName := Kernel.elf
override CC := gcc
override LD := ld

# All the flags for linker and compiler
CFlags ?= -Wall -Wextra -std=gnu11 -ffreestanding -fno-stack-protector -fno-stack-check -fno-lto -fno-PIE -fno-PIC \
	-m64 -march=x86-64 -mabi=sysv -mno-80387 -mno-mmx -mno-red-zone -mcmodel=kernel -I Kernel/Include/

NasmFlags ?= -F dwarf -g
LdFlags ?= -nostdlib -static -m elf_x86_64 -z max-page-size=0x1000 -no-pie -T Kernel/Linker.ld

# Finds all .c and .asm files and gets the .o file names
CFiles := $(shell find -L Kernel/ -type f -name '*.c')
NasmFiles := $(shell find -L Kernel/ -type f -name '*.asm')
Obj := $(addprefix $(BuildDir), $(patsubst %.c, %.o, $(CFiles)) $(patsubst %.asm, %.o, $(NasmFiles)))


.PHONY: all compile
all: compile BuildIso

compile: CheckUser limine.h $(KernelName)

$(KernelName): $(Obj)
	@echo -e "\n\e[0;32m==> Linking kernel...\e[0m"
	$(LD) $(Obj) $(LdFlags) -o $(BuildDir)$@


$(addprefix $(BuildDir), %.o): %.c
	$(CC) $(CFlags) -c $< -o $@


$(addprefix $(BuildDir), %.o): %.asm
	nasm -f elf64 $< -o $@


BuildIso:
	@echo -e "\n\e[0;32m==> Building .iso image...\e[0m"

	@sudo rm -rf $(BuildDir)IsoRoot/*
	mkdir -p $(BuildDir)IsoRoot
	sudo cp -v $(BuildDir)Kernel.elf Limine.cfg limine/limine.sys limine/limine-cd.bin limine/limine-cd-efi.bin 12.jpeg $(BuildDir)IsoRoot

	xorriso -as mkisofs -b limine-cd.bin \
        -no-emul-boot -boot-load-size 4 -boot-info-table \
        --efi-boot limine-cd-efi.bin \
        -efi-boot-part --efi-boot-image --protective-msdos-label \
        $(BuildDir)IsoRoot -o $(BuildDir)$(IsoName)

	limine/limine-deploy $(BuildDir)$(IsoName)

	sudo chmod -R a=rwx $(BuildDir)


.PHONY: limine
limine:
	git clone https://github.com/limine-bootloader/limine.git --branch=v4.x-branch-binary --depth=1
	make -C limine


limine.h:
	@if ! [ -f $(BuildDir)$@ ]; then \
		curl https://raw.githubusercontent.com/limine-bootloader/limine/trunk/limine.h -o $(BuildDir)$@; \
	fi

	@echo -e "\n\e[0;32m==> Compiling Kernel...\e[0m"
	


# Checks if the user has permissions to create the image
CheckUser:
	@if ! [ "$(shell id -u)" = 0 ]; then \
		echo -e "\e[0;31mYou need to be root to create the image.\n\e[0mUse \"sudo su\" to give yourself permission or add \"sudo\" before your command\n"; \
		exit 1; \
	fi


.PHONY: run debug clean
run:
	qemu-system-x86_64 -hda $(BuildDir)$(IsoName) -d int

debug:
	qemu-system-x86_64 -hda $(BuildDir)$(IsoName) -d int -monitor stdio 

clean:
	rm -rf $(BuildDir)*
	mkdir -p $(BuildDir)Kernel/Arch/x86/
	mkdir -p $(BuildDir)Kernel/Screen/
	mkdir -p $(BuildDir)Kernel/IO/

.PHONY: push
push: CheckUser
	git status

	@echo -e "\n"
	@read -n 1 -p "Push changes to github? [y to continue] "; \
	if ! [ $$REPLY = "y" ]; then \
		echo -e "\n"; \
		exit 1; \
	fi

	@echo -e "\n"
	git push origin main