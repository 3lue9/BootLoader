#include "vga/vga_print.h"
#include "./time/time.h"

void kernel_main() {
    display_time();
    print("Sleeping for 5 seconds...\n");
    sleep(5);

    print("Woke up!\n");
    display_time();

  while (1) {
    __asm__ volatile ("hlt");
  }
}

