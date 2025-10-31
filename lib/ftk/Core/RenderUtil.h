// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the feather-tk project.

#pragma once

#include <ftk/Core/Box.h>
#include <ftk/Core/Util.h>

#include <memory>

namespace ftk
{
    class IRender;

    //! \name Rendering
    ///@{
        
    //! Set and restore the render size.
    class RenderSizeState
    {
    public:
        RenderSizeState(const std::shared_ptr<IRender>&);

        ~RenderSizeState();

    private:
        FTK_PRIVATE();
    };

    //! Set and restore the viewport.
    class ViewportState
    {
    public:
        ViewportState(const std::shared_ptr<IRender>&);

        ~ViewportState();

    private:
        FTK_PRIVATE();
    };

    //! Set and restore whether the clipping rectangle is enabled.
    class ClipRectEnabledState
    {
    public:
        ClipRectEnabledState(const std::shared_ptr<IRender>&);

        ~ClipRectEnabledState();

    private:
        FTK_PRIVATE();
    };

    //! Set and restore the clipping rectangle.
    class ClipRectState
    {
    public:
        ClipRectState(const std::shared_ptr<IRender>&);

        ~ClipRectState();

        const Box2I& getClipRect() const;

    private:
        FTK_PRIVATE();
    };

    //! Set and restore the transform.
    class TransformState
    {
    public:
        TransformState(const std::shared_ptr<IRender>&);

        ~TransformState();

    private:
        FTK_PRIVATE();
    };
        
    ///@}
}
