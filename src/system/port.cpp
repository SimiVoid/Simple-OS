#include "system/port.h"

extern "C" uint8_t inb(uint16_t port) {
    uint8_t val;

    asm volatile ("inb %1, %0" : "=a" (val) : "Nd" (port));

    return val;
}

extern "C" uint16_t inw(uint16_t port) {
    uint16_t val;

    asm volatile ("inw %1, %0" : "=a" (val) : "Nd" (port));

    return val;
}

extern "C" uint32_t inl(uint16_t port) {
    uint32_t val;

    asm volatile ("inl %1, %0" : "=a" (val) : "Nd" (port));

    return val;
}

extern "C" void outb(uint16_t port, uint8_t value) {
    asm volatile("outb %0, %1" : : "a" (value), "Nd" (port));
}

extern "C" void outw(uint16_t port, uint16_t value) {
    asm volatile("outw %0, %1" : : "a" (value), "Nd" (port));
}

extern "C" void outl(uint16_t port, uint32_t value) {
    asm volatile("outl %0, %1" : : "a"(value), "Nd"(port) );
}