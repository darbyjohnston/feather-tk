// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

namespace ftk
{
    inline InMemoryFile::InMemoryFile(const uint8_t* p, size_t size) :
        p(p),
        size(size)
    {}

    inline bool InMemoryFile::operator == (const InMemoryFile& other) const
    {
        return
            p == other.p &&
            size == other.size;
    }

    inline bool InMemoryFile::operator != (const InMemoryFile& other) const
    {
        return !(*this == other);
    }
}
