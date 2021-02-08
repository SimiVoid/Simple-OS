#include "io.h"
#include "string.h"

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
    //initKeyboard();

    while (true) {
        updateKeyStates();
    }    
}
