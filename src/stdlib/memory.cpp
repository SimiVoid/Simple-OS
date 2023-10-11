#include "stdlib/memory.h"

header_t* head;
header_t* tail;

void* sbrk(int increment) {
    extern char end;
    static char* headEnd;
    char* prevHeapEnd;

    if(headEnd == 0)
        headEnd = &end;

    prevHeapEnd = headEnd;
    headEnd += increment;

    return (void*)prevHeapEnd;
}

header_t* getFreeBlock(size_t size) {
    header* current = head;

    while (current)
    {
        if(current->s.isFree && current->s.size >= size)
            return current;
        current = current->s.next;
    }

    return NULL;
}

void* malloc(size_t size) {
    if(!size) return NULL;

    size_t totalSize;
    void* block;
    header_t* header = getFreeBlock(size);

    if(header) {
        header->s.isFree = false;
        return (void*)(header + 1);
    }

    totalSize = sizeof(header_t) + size;
    block = sbrk(totalSize);

    if(block == (void*) - 1) {
        return NULL;
    }

    header = (header_t*)block;
    header->s.size = size;
    header->s.isFree = false;
    header->s.next = NULL;

    if(!head) head = header;
    if(tail) tail->s.next = header;
    tail = header;

    return (void*)(header + 1);
}

void* calloc(size_t n, size_t nsize) {
    size_t size;
    void* mem;

    if(!n || !nsize) return NULL;

    size = n * nsize;

    if(nsize != size / n) return NULL;

    mem = malloc(size);

    if(!mem) return NULL;

    memset(mem, 0, size);

    return mem;
}

void* realloc(void* mem, size_t size) {
    header_t *header;
	void *ret;

    if (!mem || !size) return malloc(size);

    header = (header_t*)mem - 1;

    if (header->s.size >= size) return mem;

	ret = malloc(size);

	if (ret) {
		memcpy(ret, mem, header->s.size);
		free(mem);
	}

	return ret;
}

void free(void* mem) {
    header_t* tmp;

    if(!mem) return;

    header_t* header = (header_t*)mem - 1;
    void* programBreak = sbrk(0);

    if((char*)mem + header->s.size == programBreak) {
        if(head == tail)
            head = tail = NULL;
        else {
            tmp = head;

            while(tmp) {
                if(tmp->s.next == tail) {
                    tmp->s.next = NULL;
                    tail = tmp;
                }
                tmp = tmp->s.next;
            }
        }
        sbrk(0 - sizeof(header_t) - header-> s.size);

        return;
    }

    header->s.isFree = true;
}

void* memset(void* mem, int c, size_t n) {
    uint8_t* ptr = (uint8_t*)mem;

    while(n--) *ptr++ = (uint8_t)c;

    return mem;
}

void memcpy(void* dest, void* src, size_t n) {
    uint8_t* srccpy = (uint8_t*)src;
    uint8_t* destcpy = (uint8_t*)dest;

    for(size_t i = 0; i < n; ++i) destcpy[i] = srccpy[i];
}

void memmove(void* dest, void* src, size_t n) {
    uint8_t* srccpy = (uint8_t*)src;
    uint8_t* destcpy = (uint8_t*)dest;
    uint8_t* temp = (uint8_t*)malloc(sizeof(uint8_t) * n);

    size_t i;

    for(i = 0; i < n; ++i) temp[i] = srccpy[i];
    for(i = 0; i < n; ++i) destcpy[i] = temp[i];

    free(temp);
}
