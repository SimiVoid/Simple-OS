#pragma once

#include "vga.h"
#include "keyboard.h"

void puts(const char* str);
void putc(char c);

uint8_t readKey();
uint8_t getc();

void initKeyboard();
void updateKeyStates();
