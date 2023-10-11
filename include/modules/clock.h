#pragma once

#include "../stdlib/types.h"

#define CLOCK_TIME 0x01
#define CLOCK_DATE 0x02
#define CLOCK_ALL CLOCK_TIME | CLOCK_DATE

void printClock(uint16_t pos, uint8_t mode = CLOCK_ALL);