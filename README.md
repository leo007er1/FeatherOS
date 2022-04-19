# FeatherOS
A simple x86 operating system I'm working on in my free time. 

## Current state of this project
The last commit on this repository overhauled the bootloader, making it more reliable, with more features and support for 64 bits Long Mode. I haven't tested the kernel files yet but I will soon. **The bootloader doesn't actually load the kernel, I'm trying to fix this issue.** Keep in mind that **this is a learning project**, I know there's terrible code everywhere, I'm focusing on learning and improving what I can with my current knoweldge.

## Features
- 64 bits second stage bootloader
- A crappy VGA driver
- Include bins
- Few kernel setup files

Not much right?

## Work in progress
- Making the bootloader load the kernel(that's what a bootloader is supposed to do, right?)
- File system(ext2)
- PS2/2 keyboard driver

## Compiling
If you are willing to compile this pretty trash os there's a bash script for you, just execute the `Build.sh` file located in the main directory of the repository. This script creates a Build directory with inside all compilation files.

## Running the OS in QEMU
Just like compiling there's not 1 bash script, but 2! Both located in the main directory of this repository, `Run.sh` and `Debug.sh` let you run the operating system. The obly difference between the two is that `Debug.sh` runs QEMU monitor too for debugging.
