// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

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
