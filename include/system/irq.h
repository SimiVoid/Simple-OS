#pragma once

namespace irq {
    extern "C" void cli();
    extern "C" void sti();
    extern "C" void hlt();
}