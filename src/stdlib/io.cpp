#include "stdlib/io.h"

struct {
    bool keyLeftShiftPressed = false;
    bool keyRightShiftPressed = false;
    bool keyLeftCtrlPressed = false;
    bool keyRightCtrlPressed = false;
    bool keyLeftAltPressed = false;
    bool keyRightAltPressed = false;
    bool keyCapsLockEnable = false;
    bool keyNumLockEnable = false;
} keyData;

void puts(const char* str) {
    for(uint16_t i = 0; str[i] != '\0'; ++i) {
        putc(str[i]);
    }
}

void putc(char c) {
    switch (c)
        {
        case '\n':
            if(++vgaY >= VGA_HEIGHT)
                clearTerminal();
        case '\r':
            vgaX = 0;
            break;
        case '\b':
            if(vgaX - 1 < 0) {
                vgaX == VGA_WIDTH - 1;
                if(vgaY - 1 < 0) {
                    vgaX = 0;
                    vgaY = 0;
                }
            } else vgaX--;
            VideoMemory[VGA_WIDTH * vgaY + vgaX] = vgaColorEntry() | ' ';
            break;
        case '\t':
            puts("    ");
            break;
        default:
            VideoMemory[VGA_WIDTH * vgaY + vgaX] = vgaColorEntry() | c;

            if(++vgaX >= VGA_WIDTH) {
                vgaX = 0;
                if(++vgaY >= VGA_HEIGHT)
                    clearTerminal();
            }
            break;
        }

    setCursorPos(VGA_WIDTH * vgaY + vgaX);
}

char printCharFormKeyboard() {
    char c = getCharFromKeyboard();

    putc(c);

    return c;
}

uint8_t readKey() {
    return inb(0x60);
}

char getCharFromKeyboard() {
    static uint8_t memKeyCode = 0;

    while(true) {
        updateKeyStates();

        char keyCode = readKey();

        if(keyCode == memKeyCode) continue;

        memKeyCode = keyCode;

        if(keyCode == KEY_BACK_TICK && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return '~';
        else if(keyCode == KEY_BACK_TICK && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return '`';
        else if(keyCode == KEY_1 && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return '!';
        else if(keyCode == KEY_1 && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return '1';
        else if(keyCode == KEY_2 && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return '@';
        else if(keyCode == KEY_2 && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return '2';
        else if(keyCode == KEY_3 && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return '#';
        else if(keyCode == KEY_3 && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return '3';
        else if(keyCode == KEY_4 && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return '$';
        else if(keyCode == KEY_4 && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return '4';
        else if(keyCode == KEY_5 && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return '%';
        else if(keyCode == KEY_5 && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return '5';
        else if(keyCode == KEY_6 && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return '^';
        else if(keyCode == KEY_6 && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return '6';
        else if(keyCode == KEY_7 && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return '&';
        else if(keyCode == KEY_7 && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return '7';
        else if(keyCode == KEY_8 && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return '*';
        else if(keyCode == KEY_8 && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return '8';
        else if(keyCode == KEY_9 && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return '(';
        else if(keyCode == KEY_9 && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return '9';
        else if(keyCode == KEY_0 && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return ')';
        else if(keyCode == KEY_0 && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return '0';
        else if(keyCode == KEY_DASH && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return '_';
        else if(keyCode == KEY_DASH && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return '-';
        else if(keyCode == KEY_EQUAL && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return '+';
        else if(keyCode == KEY_EQUAL && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return '=';
        else if(keyCode == KEY_Q && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'Q';
        else if(keyCode == KEY_Q && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'q';
        else if(keyCode == KEY_W && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'W';
        else if(keyCode == KEY_W && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'w';
        else if(keyCode == KEY_E && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'E';
        else if(keyCode == KEY_E && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'e';
        else if(keyCode == KEY_R && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'R';
        else if(keyCode == KEY_R && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'r';
        else if(keyCode == KEY_T && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'T';
        else if(keyCode == KEY_T && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 't';
        else if(keyCode == KEY_Y && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'Y';
        else if(keyCode == KEY_Y && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'y';
        else if(keyCode == KEY_U && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'U';
        else if(keyCode == KEY_U && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'u';
        else if(keyCode == KEY_I && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'I';
        else if(keyCode == KEY_I && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'i';
        else if(keyCode == KEY_O && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'O';
        else if(keyCode == KEY_O && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'o';
        else if(keyCode == KEY_P && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'P';
        else if(keyCode == KEY_P && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'p';
        else if(keyCode == KEY_LEFT_SQUARE_BRAKET && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return '{';
        else if(keyCode == KEY_LEFT_SQUARE_BRAKET && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return '[';
        else if(keyCode == KEY_RIGHT_SQUARE_BRAKET && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return '}';
        else if(keyCode == KEY_RIGHT_SQUARE_BRAKET && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return ']';
        else if(keyCode == KEY_BACKSLASH && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return '|';
        else if(keyCode == KEY_BACKSLASH && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return '\\';
        else if(keyCode == KEY_A && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'A';
        else if(keyCode == KEY_A && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'a';
        else if(keyCode == KEY_S && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'S';
        else if(keyCode == KEY_S && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 's';
        else if(keyCode == KEY_D && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'D';
        else if(keyCode == KEY_D && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'd';
        else if(keyCode == KEY_F && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'F';
        else if(keyCode == KEY_F && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'f';
        else if(keyCode == KEY_G && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'G';
        else if(keyCode == KEY_G && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'g';
        else if(keyCode == KEY_H && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'H';
        else if(keyCode == KEY_H && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'h';
        else if(keyCode == KEY_J && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'J';
        else if(keyCode == KEY_J && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'j';
        else if(keyCode == KEY_K && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'K';
        else if(keyCode == KEY_K && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'k';
        else if(keyCode == KEY_L && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'L';
        else if(keyCode == KEY_L && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'l';
        else if(keyCode == KEY_SEMICOLON && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return ':';
        else if(keyCode == KEY_SEMICOLON && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return ';';
        else if(keyCode == KEY_SINGLE_QUOTE && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return '"';
        else if(keyCode == KEY_SINGLE_QUOTE && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return '\'';
        else if(keyCode == KEY_Z && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'Z';
        else if(keyCode == KEY_Z && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'z';
        else if(keyCode == KEY_X && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'X';
        else if(keyCode == KEY_X && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'x';
        else if(keyCode == KEY_C && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'C';
        else if(keyCode == KEY_C && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'c';
        else if(keyCode == KEY_V && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'V';
        else if(keyCode == KEY_V && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'v';
        else if(keyCode == KEY_B && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'B';
        else if(keyCode == KEY_B && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'b';
        else if(keyCode == KEY_N && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'N';
        else if(keyCode == KEY_N && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'n';
        else if(keyCode == KEY_M && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'M';
        else if(keyCode == KEY_M && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return 'm';
        else if(keyCode == KEY_COMMA && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return '<';
        else if(keyCode == KEY_COMMA && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return ',';
        else if(keyCode == KEY_DOT && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return '>';
        else if(keyCode == KEY_DOT && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return '.';
        else if(keyCode == KEY_SLASH && (keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return '?';
        else if(keyCode == KEY_SLASH && !(keyData.keyLeftShiftPressed || keyData.keyRightShiftPressed))
            return '/';
        else if(keyCode == KEY_SPACEBAR)
            return ' ';
        else if(keyCode == KEY_ENTER)
            return '\n';
        else if(keyCode == KEY_BACKSPACE)
            return '\b';
    }

    return 0;
}

void updateKeyStates() {
    uint8_t keyCode = readKey();

    if(keyCode == KEY_LEFT_SHIFT + KEY_PRESSED && !keyData.keyLeftShiftPressed)
        keyData.keyLeftShiftPressed = true;
    else if(keyCode == KEY_LEFT_SHIFT + KEY_RELEASED && keyData.keyLeftShiftPressed)
        keyData.keyLeftShiftPressed = false;
    else if(keyCode == KEY_RIGHT_SHIFT + KEY_PRESSED && !keyData.keyRightShiftPressed)
        keyData.keyRightShiftPressed = true;
    else if(keyCode == KEY_RIGHT_SHIFT + KEY_RELEASED && keyData.keyRightShiftPressed)
        keyData.keyRightShiftPressed = false;
    else if(keyCode == KEY_LEFT_CTRL + KEY_PRESSED && !keyData.keyLeftCtrlPressed)
        keyData.keyLeftCtrlPressed = true;
    else if(keyCode == KEY_LEFT_CTRL + KEY_RELEASED && keyData.keyLeftCtrlPressed)
        keyData.keyLeftCtrlPressed = false;
    else if(keyCode == KEY_LEFT_ALT + KEY_PRESSED && !keyData.keyLeftAltPressed)
        keyData.keyLeftAltPressed = true;
    else if(keyCode == KEY_LEFT_ALT + KEY_RELEASED && keyData.keyLeftAltPressed)
        keyData.keyLeftAltPressed = false;
}

void clearTerminal() {
    for(uint16_t x = 0; x < VGA_WIDTH; ++x)
        for(uint16_t y = 0; y < VGA_HEIGHT; ++y)
            VideoMemory[VGA_WIDTH * y + x] = vgaColorEntry() | ' ';

    vgaX = 0;
    vgaY = 0;
}
