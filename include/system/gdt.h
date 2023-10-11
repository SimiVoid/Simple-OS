#pragma once

#include "../stdlib/types.h"

class GlobalDescriptorTable {
public:
    class SegmentDescriptor {
    private:
        uint16_t _limitLo;
        uint16_t _baseLo;
        uint8_t _baseHi;
        uint8_t _type;
        uint8_t _limitHi;
        uint8_t _baseVhi;
    public:
        SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t type);
        ~SegmentDescriptor() = default;

        uint32_t base();
        uint32_t limit();
    } __attribute__((packed));
private:
    SegmentDescriptor _nullSegmentSelector;
    SegmentDescriptor _unusedSegmentSelector;
    SegmentDescriptor _codeSegmentSelector;
    SegmentDescriptor _dataSegmentSelector;
public:
    GlobalDescriptorTable();
    ~GlobalDescriptorTable() = default;

    uint16_t codeSegmentSelector();
    uint16_t dataSegmentSelector();
};