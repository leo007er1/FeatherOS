#! /bin/bash

buildDir=Build
buildDirKernel=Build/Kernel
cagosDir=Cagos
kernelDir=Kernel

# Checks if the build directory exists
if [ ! -d $buildDir ]; then
    mkdir $buildDir
    mkdir $buildDir/Kernel
fi


# Clears the screen
# echo -e "\e[1;1H\e[2J"


# --- Compiling --- #


echo -e "\e[0;32m==> \e[1;32mCompiling Cagos...\e[0m"
nasm $cagosDir/CagosMain.asm -f bin -o $buildDir/CagosMain.bin
nasm $cagosDir/SecondSector.asm -f bin -o $buildDir/SecondSector.bin
nasm $cagosDir/EmptySectors.asm -f bin -o $buildDir/Empty.bin
cat "$buildDir/CagosMain.bin" "$buildDir/SecondSector.bin" > "$buildDir/Cagos.bin"


echo -e "\n\e[0;32m==> \e[1;32mCompiling kernel...\e[0m"
nasm $kernelDir/KernelEntry.asm -f elf64 -o $buildDirKernel/KernelEntry.o
nasm $kernelDir/IncludeBins.asm -f elf64 -o $buildDirKernel/IncludeBins.o
x86_64-elf-gcc -ffreestanding -m64 -mgeneral-regs-only -mno-red-zone -g -c $kernelDir/KernelMain.c -o $buildDirKernel/KernelMain.o
x86_64-elf-gcc -ffreestanding -m64 -mgeneral-regs-only -mno-red-zone -g -c $kernelDir/IO.c -o $buildDirKernel/IO.o
x86_64-elf-gcc -ffreestanding -m64 -mgeneral-regs-only -mno-red-zone -g -c $kernelDir/Drivers/VGA.c -o $buildDirKernel/VGA.o


echo -e "\n\e[0;32m==> \e[1;32mLinking...\e[0m"
x86_64-elf-ld -o $buildDir/Kernel.bin -Ttext 0x1000 $buildDirKernel/KernelEntry.o $buildDirKernel/KernelMain.o $buildDirKernel/IncludeBins.o $buildDirKernel/IO.o $buildDirKernel/VGA.o --oformat binary


echo -e "\n\e[0;32m==> \e[1;32mFinishing...\e[0m"
cat "$buildDir/Cagos.bin" "$buildDir/Kernel.bin" "$buildDir/Empty.bin" > "$buildDir/boot.img"
# dd if="$buildDir/boot.img" of="/dev/zero" bs=512 count=2880
# cat "$buildDir/Cagos.bin" "$buildDir/Kernel.bin" "$buildDir/Empty.bin" > "$buildDir/all.bin"
# dd if="$buildDir/boot.img" of="$buildDir/all.bin" conv=notrunc


echo -e "\n\n\e[0;32m==> \e[1;32mCompilation terminated\e[0m"