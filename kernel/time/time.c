#include <stdint.h>
#include "vga_print.h" // Assuming vga_print.h is available for output

// I/O port read and write functions
static inline uint8_t inb(uint16_t port) {
    uint8_t data;
    __asm__ volatile ("inb %1, %0" : "=a" (data) : "Nd" (port));
    return data;
}

static inline void outb(uint16_t port, uint8_t data) {
    __asm__ volatile ("outb %0, %1" : : "a" (data), "Nd" (port));
}

// CMOS ports
#define CMOS_COMMAND 0x70
#define CMOS_DATA 0x71

// Function to read from the CMOS
uint8_t read_cmos(uint8_t reg) {
    outb(CMOS_COMMAND, reg);
    return inb(CMOS_DATA);
}

// Helper function to convert BCD to binary
static uint8_t bcd_to_bin(uint8_t bcd) {
    return (bcd & 0x0F) + ((bcd >> 4) * 10);
}

// Time structure
typedef struct {
    uint8_t second;
    uint8_t minute;
    uint8_t hour;
    uint8_t day;
    uint8_t month;
    uint16_t year;
} Time;

// Function to get the current time
void get_time(Time* time) {
    time->second = bcd_to_bin(read_cmos(0x00));
    time->minute = bcd_to_bin(read_cmos(0x02));
    time->hour = (bcd_to_bin(read_cmos(0x04)) + 1) % 24; // Adjust for timezone (add 1 hour)
    time->day = bcd_to_bin(read_cmos(0x07));
    time->month = bcd_to_bin(read_cmos(0x08));
    time->year = bcd_to_bin(read_cmos(0x09)) + 2000; // Assuming 21st century
}

// Function to display time using VGA print
void display_time() {
    Time current_time;
    get_time(&current_time);

    print("\n");
    print_formatted("Formatted Time Example:\nHour: %d\nMinute: %d\nSecond: %d\n", current_time.hour, current_time.minute, current_time.second);
}
