#pragma once

#include "types.h"

union header {
    struct {
        size_t size;
        bool isFree;
        header* next;
    } s;
    char stub[16];
};

typedef header header_t;

void* malloc(size_t size);
void* calloc(size_t n, size_t nsize);
void* realloc(void* mem, size_t size);
void free(void* mem);

void* memset(void* mem, int c, size_t n);
void memcpy(void* dest, void* src, size_t n);
void memmove(void* dest, void* src, size_t n);