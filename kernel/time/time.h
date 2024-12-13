#ifndef TIME_H
#define TIME_H

#include <stdint.h>

// Time structure
typedef struct {
    uint8_t second;
    uint8_t minute;
    uint8_t hour;
    uint8_t day;
    uint8_t month;
    uint16_t year;
} Time;

// Function prototypes
void get_time(Time* time);
void display_time();

#endif // TIME_H

