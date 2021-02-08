#include "lowlevel.h"

extern "C" uint8_t inb(uint16_t port) {
    uint8_t val;

    asm volatile ("inb %w1,%0\noutb %%al,$0x80":"=a" (val):"Nd" (port));
    
    return val;
}

extern "C" void outb(uint16_t port, uint8_t value) {
    asm volatile("outb %0, %1" : : "a"(value), "Nd"(port) );
}