#include <stdint.h>
#include <stddef.h>

// Minimal implementation of va_list
typedef __builtin_va_list va_list;
#define va_start(v, l) __builtin_va_start(v, l)
#define va_arg(v, t) __builtin_va_arg(v, t)
#define va_end(v) __builtin_va_end(v)

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
        for (int i = 0; i < (VGA_WIDTH * (VGA_HEIGHT - 1)); i++) {
            vga[i * 2] = vga[(i + VGA_WIDTH) * 2];
            vga[i * 2 + 1] = vga[(i + VGA_WIDTH) * 2 + 1];
        }
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

    if (num == 0) {
        buffer[i++] = '0';
        buffer[i] = '\0';
        return;
    }

    if (num < 0) {
        is_negative = 1;
        num = -num;
    }

    while (num > 0) {
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    }

    if (is_negative) {
        buffer[i++] = '-';
    }

    buffer[i] = '\0';

    for (int j = 0; j < i / 2; j++) {
        char temp = buffer[j];
        buffer[j] = buffer[i - j - 1];
        buffer[i - j - 1] = temp;
    }
}

// Function to print an integer
void print_int(int num) {
    char buffer[12];
    int_to_str(num, buffer);
    print(buffer);
}

// Universal print function to handle multiple types
void print_formatted(const char* format, ...) {
    va_list args;
    va_start(args, format);

    for (size_t i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%' && format[i + 1] != '\0') {
            i++;
            switch (format[i]) {
                case 'd': {
                    int num = va_arg(args, int);
                    print_int(num);
                    break;
                }
                case 'c': {
                    char c = (char)va_arg(args, int);
                    put_char(c);
                    break;
                }
                case 's': {
                    char* str = va_arg(args, char*);
                    print(str);
                    break;
                }
                default: {
                    put_char('%');
                    put_char(format[i]);
                    break;
                }
            }
        } else {
            put_char(format[i]);
        }
    }

    va_end(args);
}

