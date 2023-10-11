#pragma once

#include "../stdlib/types.h"

struct DateTime {
    uint8_t second;
    uint8_t minute;
    uint8_t hour;
    uint8_t day;
    uint8_t month;
    uint32_t year;
} __attribute__((packed));

DateTime currentDateTime;

DateTime getTimeFromRTC();
void setTimeToRTC(const DateTime& time);
bool updateClock();