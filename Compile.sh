
# Cagos compilation
nasm "Cagos/CagosMain.asm" -f bin -o "CompiledFiles/Cagos.bin"
nasm "Cagos/ExtendedProgram.asm" -f elf64 -o "CompiledFiles/ExtendedProgram.o"

# Kernel compilation
x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "Kernel/KernelMain.cpp" -o "CompiledFiles/KernelMain.o"

ld -T "Link.ld"

cat "CompiledFiles/Cagos.bin" "CompiledFiles/Kernel.bin" > "CompiledFiles/boot.bin"

echo "Compilation terminated"
