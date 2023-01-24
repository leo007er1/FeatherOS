
IsoName := FeatherOS.iso
BuildDir := Build


.PHONY: all
all: CheckUser BuildIso


BuildIso:
	@echo -e "\n\e[0;32m==> Building .iso image...\e[0m"

	@sudo rm -rf $(BuildDir)/IsoRoot/*
	@mkdir -p $(BuildDir)/IsoRoot

	@sudo cp -v $(BuildDir)/Kernel/Kernel.elf Limine.cfg limine/limine.sys limine/limine-cd.bin limine/limine-cd-efi.bin $(BuildDir)/IsoRoot

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


# Checks if the user has permissions to create the image
CheckUser:
	@if ! [ "$(shell id -u)" = 0 ]; then \
		echo -e "\e[0;31mYou need to be root to create the image.\n\e[0mUse \"sudo su\" to give yourself permission or add a \"sudo\" before your command\n"; \
		exit 1; \
	fi


.PHONY: run
run:
	@qemu-system-x86_64 -hda $(BuildDir)/$(IsoName) -d int


.PHONY: clean
clean:
	sudo rm -rf $(BuildDir)/*