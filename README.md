# FeatherOS

A simple x86_64 operating system I'm working on my free time. For now it features a bootloader and some setup files for the kernel.

# Compiling and running the os in QEMU

To compile the operating system just run the Compile.sh bash script.
```
./Compile.sh
```

In this repository there's included the RunOS.sh bash script, that let's you run the os in QEMU.
```
./RunOS.sh
```
Or in alternative just run this command:
```
qemu-system-x86_64 FileCompilati/boot.bin
```
