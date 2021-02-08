#include "vga.h"

void initVga() {
    VideoMemory = (uint16_t*)0xb8000;
    vgaX = 0;
    vgaY = 0;
    backgraoundColor = VGA_BLUE;
    foregroundColor = VGA_WHITE;

    clearScreen();
}

void clearScreen() {
    for(uint16_t x = 0; x < VGA_WIDTH; ++x)
        for(uint16_t y = 0; y < VGA_HEIGHT; ++y)
            VideoMemory[VGA_WIDTH * y + x] = vgaColorEntry() | ' ';

    vgaX = 0;
    vgaY = 0;
}

void setColor(uint8_t foreground, uint8_t background) {
    backgraoundColor = background;
    foregroundColor = foreground;
}

uint16_t vgaColorEntry() {
    return ((backgraoundColor << 4) | (foregroundColor & 0x0F)) << 8;
}

void showCursor(bool enable) {
    if(enable) {
        outb(0x3D4, 0x0A);
	    outb(0x3D5, (inb(0x3D5) & 0xC0) | 0x00);
 
	    outb(0x3D4, 0x0B);
	    outb(0x3D5, (inb(0x3D5) & 0xE0) | 0x0F);
    }
    else {
        outb(0x3D4, 0x0A);
	    outb(0x3D5, 0x20);
    }
}

void setCursorPos(uint16_t x, uint16_t y) {
    uint16_t pos = y * VGA_WIDTH + x;
 
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

uint64_t getCursorPos() {
    uint16_t pos = 0;

    return pos;
}


