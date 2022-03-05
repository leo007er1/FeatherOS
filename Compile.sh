

# Compilazione Cagos
nasm "Cagos/CagosMain.asm" -f bin -o "FileCompilati/Cagos.bin"
nasm "Cagos/ExtendedProgram.asm" -f elf64 -o "FileCompilati/ExtendedProgram.o"

# Compilazione kernel
x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "Kernel/KernelMain.cpp" -o "FileCompilati/KernelMain.o"

# Linking di ExtendedProgram in KernelMain, creando il file Kernel.bin
ld -T "Link.ld"

cat "FileCompilati/Cagos.bin" "FileCompilati/Kernel.bin" > "FileCompilati/boot.bin"

echo "Compilazione terminata"