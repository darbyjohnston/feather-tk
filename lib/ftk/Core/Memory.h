// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/Core/Util.h>

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace ftk
{
    //! \name Memory
    ///@{

    constexpr size_t kilobyte = 1024; //!< The number of bytes in a kilobyte
    constexpr size_t megabyte = kilobyte * 1024; //!< The number of bytes in a megabyte
    constexpr size_t gigabyte = megabyte * 1024; //!< The number of bytes in a gigabyte
    constexpr size_t terabyte = gigabyte * 1024; //!< The number of bytes in a terabyte

    //! Get the aligned byte count.
    size_t getAlignedByteCount(size_t, size_t alignment);
        
    //! Endian type.
    enum class Endian
    {
        MSB, //!< Most siginificant byte first
        LSB, //!< Least significant byte first

        Count,
        First = MSB
    };
    FTK_ENUM(Endian);

    //! Get the current endian.
    Endian getEndian();

    //! Get the opposite of the given endian.
    constexpr Endian opposite(Endian);

    //! Convert the endianness of a block of memory in place.
    void endian(
        void*  in,
        size_t size,
        size_t wordSize);

    //! Convert the endianness of a block of memory.
    void endian(
        const void* in,
        void*       out,
        size_t      size,
        size_t      wordSize);

    //! Get the given bit.
    bool getBit(unsigned int, int bit);

    //! Set the given bit.
    unsigned int setBit(unsigned int, int bit);

    //! Clear the given bit.
    unsigned int clearBit(unsigned int, int bit);

    //! Toggle the given bit.
    unsigned int toggleBit(unsigned int, int bit);

    //! Convert bits to a string for debugging.
    std::string getBitString(uint8_t);

    //! Convert bits to a string for debugging.
    std::string getBitString(uint16_t);

    ///@}
}

#include <ftk/Core/MemoryInline.h>
