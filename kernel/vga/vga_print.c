#include <stdint.h>
#include <stddef.h>
// VGA text buffer address
#define VGA_ADDRESS 0xB8000

// Screen dimensions
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

// Foreground and background colors
#define WHITE_ON_BLACK 0x0F

// Global cursor position
uint16_t cursor_pos = 0;

// Function to write a character to the VGA buffer
void put_char(char c) {
    volatile char* vga = (volatile char*)VGA_ADDRESS;

    if (c == '\n') {
        cursor_pos += VGA_WIDTH - (cursor_pos % VGA_WIDTH);
    } else {
        vga[cursor_pos * 2] = c;         // Character byte
        vga[cursor_pos * 2 + 1] = WHITE_ON_BLACK; // Attribute byte
        cursor_pos++;
    }

    // Scroll if necessary
    if (cursor_pos >= VGA_WIDTH * VGA_HEIGHT) {
        // Simple scrolling: move lines up and clear the last line
        for (int i = 0; i < (VGA_WIDTH * (VGA_HEIGHT - 1)); i++) {
            vga[i * 2] = vga[(i + VGA_WIDTH) * 2];
            vga[i * 2 + 1] = vga[(i + VGA_WIDTH) * 2 + 1];
        }
        // Clear the last line
        for (int i = (VGA_WIDTH * (VGA_HEIGHT - 1)); i < VGA_WIDTH * VGA_HEIGHT; i++) {
            vga[i * 2] = ' ';
            vga[i * 2 + 1] = WHITE_ON_BLACK;
        }
        cursor_pos -= VGA_WIDTH;
    }
}

// Function to print a string
void print(const char* str) {
    for (size_t i = 0; str[i] != '\0'; i++) {
        put_char(str[i]);
    }
}


