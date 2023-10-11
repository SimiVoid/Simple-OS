#include "stdlib/io.h"
#include "stdlib/string.h"
#include "stdlib/memory.h"
#include "system/gdt.h"
#include "modules/clock.h"

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}

extern "C" void kernelMain(const void* multibootStructure, uint32_t magicNumber) {
    initVga();
    clearTerminal();

    GlobalDescriptorTable gdt;

    while (true) {
        printClock(VGA_WIDTH - 19);
    }
}
