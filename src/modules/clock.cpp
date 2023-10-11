#include "modules/clock.h"

#include "stdlib/io.h"
#include "stdlib/string.h"
#include "system/vga.h"
#include "system/rtc.h"

void printClock(uint16_t pos, uint8_t mode) {
    if(!updateClock()) return;

    showCursor(false);
    setCursorPos(pos);

    char* castingBuffer;

    if(mode == CLOCK_ALL || mode == CLOCK_TIME) {
        if(currentDateTime.hour < 10) putc('0');
        puts(itoa(currentDateTime.hour, castingBuffer));
        putc(':');
        if(currentDateTime.minute < 10) putc('0');
        puts(itoa(currentDateTime.minute, castingBuffer));
        putc(':');
        if(currentDateTime.second < 10) putc('0');
        puts(itoa(currentDateTime.second, castingBuffer));
    }

    if(mode == CLOCK_ALL) putc(' ');

    if(mode == CLOCK_ALL || mode == CLOCK_DATE) {
        if(currentDateTime.day < 10) putc('0');
        puts(itoa(currentDateTime.day, castingBuffer));
        putc('/');
        if(currentDateTime.month < 10) putc('0');
        puts(itoa(currentDateTime.month, castingBuffer));
        putc('/');
        puts(itoa(currentDateTime.year, castingBuffer));
    }
}