#include "system/irq.h"

extern "C" void irq::cli() {
    asm volatile ("cli");
}

extern "C" void irq::sti() {
    asm volatile ("sti");
}

extern "C" void irq::hlt() {
    asm volatile ("hlt");
}