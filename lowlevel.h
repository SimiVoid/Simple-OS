#pragma once

#include "types.h"

extern "C" uint8_t inb(uint16_t port);

extern "C" void outb(uint16_t port, uint8_t value);