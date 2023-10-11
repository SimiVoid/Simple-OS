#include "system/rtc.h"

#include "system/port.h"
#include "system/cmos.h"

uint8_t getRTCRegister(uint8_t reg) {
    outb(CMOS_ADDRESS, reg);
    return inb(CMOS_DATA);
}

DateTime getTimeFromRTC() {
    DateTime time;

    time.second = getRTCRegister(0x00);
    time.minute = getRTCRegister(0x02);
    time.hour = getRTCRegister(0x04);
    time.day = getRTCRegister(0x07);
    time.month = getRTCRegister(0x08);
    time.year = getRTCRegister(0x09);
    uint8_t century = getRTCRegister(0x32);

    uint8_t registerB = getRTCRegister(0x0B);

    if (!(registerB & 0x04)) {
        time.second = (time.second & 0x0F) + ((time.second / 16) * 10);
        time.minute = (time.minute & 0x0F) + ((time.minute / 16) * 10);
        time.hour = ( (time.hour & 0x0F) + (((time.hour & 0x70) / 16) * 10) ) | (time.hour & 0x80);
        time.day = (time.day & 0x0F) + ((time.day / 16) * 10);
        time.month = (time.month & 0x0F) + ((time.month / 16) * 10);
        time.year = (time.year & 0x0F) + ((time.year / 16) * 10)
            + (century & 0x0F) + (century / 16) * 1000;
    }

    if (!(registerB & 0x02) && (time.hour & 0x80)) {
            time.hour = ((time.hour & 0x7F) + 12) % 24;
    }

    return time;
}

void setTimeToRTC(const DateTime& time) {
    outb(CMOS_ADDRESS, 0x00);
    outb(CMOS_DATA, time.second);

    outb(CMOS_ADDRESS, 0x02);
    outb(CMOS_DATA, time.minute);

    outb(CMOS_ADDRESS, 0x04);
    outb(CMOS_DATA, time.hour);

    outb(CMOS_ADDRESS, 0x07);
    outb(CMOS_DATA, time.day);

    outb(CMOS_ADDRESS, 0x08);
    outb(CMOS_DATA, time.month);

    uint8_t year = time.year % 100;
    uint8_t century = (time.year - time.year % 100) / 100;

    outb(CMOS_ADDRESS, 0x09);
    outb(CMOS_DATA, year);

    outb(CMOS_ADDRESS, 0x32);
    outb(CMOS_DATA, century);
}

bool updateClock() {
    DateTime dateTimeBuffer = getTimeFromRTC();

    if(dateTimeBuffer.second != currentDateTime.second || dateTimeBuffer.day != currentDateTime.day || dateTimeBuffer.hour != currentDateTime.hour || 
        dateTimeBuffer.minute != currentDateTime.minute || dateTimeBuffer.year != currentDateTime.year || dateTimeBuffer.month != currentDateTime.month ) {
        currentDateTime = dateTimeBuffer;

        return true;
    }

    return false;
}
