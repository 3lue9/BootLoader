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

// Helper function to convert an integer to a string (base 10)
void int_to_str(int num, char* buffer) {
    int i = 0;
    int is_negative = 0;

    // Handle 0 explicitly
    if (num == 0) {
        buffer[i++] = '0';
        buffer[i] = '\0';
        return;
    }

    // Handle negative numbers
    if (num < 0) {
        is_negative = 1;
        num = -num;
    }

    // Convert digits to characters in reverse order
    while (num > 0) {
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    }

    // Add negative sign if applicable
    if (is_negative) {
        buffer[i++] = '-';
    }

    // Null-terminate the string
    buffer[i] = '\0';

    // Reverse the string
    for (int j = 0; j < i / 2; j++) {
        char temp = buffer[j];
        buffer[j] = buffer[i - j - 1];
        buffer[i - j - 1] = temp;
    }
}

// Function to print an integer
void print_int(int num) {
    char buffer[12]; // Enough to hold a 32-bit integer and a null terminator
    int_to_str(num, buffer);
    print(buffer);
}


