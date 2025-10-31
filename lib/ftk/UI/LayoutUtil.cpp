// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

#include <ftk/UI/LayoutUtil.h>

#include <ftk/Core/Math.h>

#include <iomanip>
#include <sstream>

namespace ftk
{
    Box2I align(
        const Box2I& box,
        const Size2I& sizeHint,
        HAlign        hAlign,
        VAlign        vAlign)
    {
        V2I pos;
        V2I size;
        switch (hAlign)
        {
        case HAlign::Fill:
            pos.x = box.x();
            size.x = box.w();
            break;
        case HAlign::Left:
            pos.x = box.x();
            size.x = sizeHint.w;
            break;
        case HAlign::Center:
            pos.x = box.x() + box.w() / 2 - sizeHint.w / 2;
            size.x = sizeHint.w;
            break;
        case HAlign::Right:
            pos.x = box.x() + box.w() - sizeHint.w;
            size.x = sizeHint.w;
            break;
        default: break;
        }
        switch (vAlign)
        {
        case VAlign::Fill:
            pos.y = box.y();
            size.y = box.h();
            break;
        case VAlign::Top:
            pos.y = box.y();
            size.y = sizeHint.h;
            break;
        case VAlign::Center:
            pos.y = box.y() + box.h() / 2 - sizeHint.h / 2;
            size.y = sizeHint.h;
            break;
        case VAlign::Bottom:
            pos.y = box.y() + box.h() - sizeHint.h;
            size.y = sizeHint.h;
            break;
        default: break;
        }
        return Box2I(pos.x, pos.y, size.x, size.y);
    }

    std::string format(int value)
    {
        std::stringstream ss;
        ss << std::setfill('0');
        ss << std::setw(digits(value));
        ss << 0;
        return ss.str();
    }

    std::string format(float value, int precision)
    {
        std::stringstream ss;
        ss << std::setfill('0');
        ss << std::setw(digits(value));
        ss << 0;
        ss << ".";
        ss << std::setw(precision);
        ss << 0;
        return ss.str();
    }
}