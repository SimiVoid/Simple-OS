#pragma once

#include "../stdlib/types.h"
#include "port.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

#define VGA_BLACK           0x00
#define VGA_BLUE            0x01
#define VGA_GREEN           0x02
#define VGA_CYAN            0x03
#define VGA_RED             0x04
#define VGA_MAGENTA         0x05
#define VGA_BROWN           0x06
#define VGA_LIGHT_GRAY      0x07
#define VGA_DARK_GRAY       0x08
#define VGA_LIGHT_BLUE      0x09
#define VGA_LIGHT_GREEN     0x0A
#define VGA_LIGHT_CYAN      0x0B
#define VGA_LIGHT_RED       0x0C
#define VGA_LIGHT_MAGENTA   0x0D
#define VGA_YELLOW          0x0E
#define VGA_WHITE           0x0F

uint16_t* VideoMemory;
uint16_t vgaX, vgaY;
uint8_t foregroundColor;
uint8_t backgraoundColor;

void initVga();

void setColor(uint8_t foreground, uint8_t background);
uint16_t vgaColorEntry();

void showCursor(bool enable);
void setCursorPos(uint16_t x, uint16_t y);
void setCursorPos(uint16_t pos);
uint64_t getCursorPos();
