#include "vga/vga_print.h"

void kernel_main() {
    print("Hello, Multiboot World!\n");
    while (1) {
        __asm__ volatile ("hlt");
    }
}

