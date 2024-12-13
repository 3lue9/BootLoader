#ifndef VGA_PRINT_H
#define VGA_PRINT_H

#include <stddef.h>
#include <stdint.h>

// Print a string to the VGA screen
void print(const char* str);

// Print an integer to the VGA screen
void print_int(int num);

// Print formatted output (supports %d, %c, %s)
void print_formatted(const char* format, ...);

#endif // VGA_PRINT_H

