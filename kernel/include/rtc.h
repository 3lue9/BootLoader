#ifndef RTC_H
#define RTC_H

#include <stdint.h>

void rtc_get_time(uint8_t* year, uint8_t* month, uint8_t* day,
                  uint8_t* hour, uint8_t* minute, uint8_t* second);

uint32_t date_to_unix(uint8_t year, uint8_t month, uint8_t day,
                      uint8_t hour, uint8_t minute, uint8_t second);

void print_unix_time();

#endif // RTC_H

