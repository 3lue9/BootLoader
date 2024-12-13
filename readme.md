
# VGA Print Utility

This project provides a simple utility for printing text and integers to the VGA screen in a low-level environment, typically for operating system development or kernel debugging.

## Features
- Print strings (`print`)
- Print integers (`print_int`)

## Requirements
- make for cross-compilation (`make`)
- A toolchain supporting 32-bit compilation (`-m32` flag)
- Basic knowledge of linking in a kernel development environment
- A virtual machine (only tested with qemu-full) 

## Compilation Instructions
1. Ensure you have the necessary toolchain installed (e.g., `gcc` for i386).
2. Use the provided makefile to compile and run the bootloader 
   ```bash
   make run
      ```


## Notes
- This utility assumes a 32-bit environment and direct access to the VGA buffer.
- It is suitable for bare-metal or kernel-level programming, not for use in user-space applications.


