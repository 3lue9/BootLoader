#include "vga/vga_print.h"
#include "./time/time.h"

void kernel_main() {
  int i;
  for ( i=1; i<10; i++){
    print_int(i);
    print("This is a for loop at kernel level \n");
  }
  
  display_time();


  while (1) {
    __asm__ volatile ("hlt");
  }
}

