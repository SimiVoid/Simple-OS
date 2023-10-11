#include "system/vga.h"

void initVga() {
    VideoMemory = (uint16_t*)0xb8000;
    vgaX = 0;
    vgaY = 0;
    backgraoundColor = VGA_BLUE;
    foregroundColor = VGA_WHITE;
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
    if(x >= VGA_WIDTH) x = VGA_WIDTH - 1;
    if(y >= VGA_HEIGHT) y = VGA_HEIGHT - 1;

	setCursorPos(y * VGA_WIDTH + x);
}

void setCursorPos(uint16_t pos) {
    if(pos >= VGA_WIDTH * VGA_HEIGHT) pos = VGA_WIDTH * VGA_HEIGHT - 1;

	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));

    vgaX = pos % VGA_WIDTH;
    vgaY = (pos - vgaX) / VGA_WIDTH;
}

uint64_t getCursorPos() {
    uint16_t pos = 0;

    outb(0x3D4, 0x0F);
    pos |= inb(0x3D5);
    outb(0x3D4, 0x0E);
    pos |= ((uint16_t)inb(0x3D5)) << 8;

    return pos;
}
