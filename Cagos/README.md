# Cagos(bootloader)
Simple x86 second stage bootloader.

## Features
Cagos can:
- Can read disk
- Load a 32 bits and 64 bits GDT
- Enable A20 line
- Get to the second stage located in 0x7e00
- Check for CPUID and Long Mode support
- Identity paging