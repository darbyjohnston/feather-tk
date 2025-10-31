// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

#include <cstdint>

namespace ftk
{
    inline size_t getAlignedByteCount(size_t value, size_t alignment)
    {
        return (value / alignment * alignment) + (value % alignment != 0 ? alignment : 0);
    }

    inline Endian getEndian()
    {
        const uint32_t tmp = 1;
        return *(reinterpret_cast<const uint8_t*>(&tmp)) ? Endian::LSB : Endian::MSB;
    }

    constexpr Endian opposite(Endian in)
    {
        return Endian::MSB == in ? Endian::LSB : Endian::MSB;
    }

    inline bool getBit(unsigned int value, int bit)
    {
        return (value >> bit) & 0x01;
    }

    inline unsigned int setBit(unsigned int value, int bit)
    {
        return value | (1 << bit);
    }

    inline unsigned int clearBit(unsigned int value, int bit)
    {
        return value & ~(1 << bit);
    }

    inline unsigned int toggleBit(unsigned int value, int bit)
    {
        return value ^ (1 << bit);
    }
}
