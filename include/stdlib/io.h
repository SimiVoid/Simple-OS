#pragma once

#include "../system/vga.h"
#include "../system/keyboard.h"

#define STREAM_SIZE 255

void puts(const char* str);
void putc(char c);
char printCharFormKeyboard();

uint8_t readKey();
char getCharFromKeyboard();
char getc();

void updateKeyStates();
void clearTerminal();
