// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/core/Box.h>
#include <feather-tk/core/Util.h>

#include <array>
#include <map>
#include <memory>
#include <vector>

namespace feather_tk
{
    //! \name Box Packing
    ///@{

    //! Box packing ID.
    typedef int64_t BoxPackID;

    //! Invalid box packing ID.
    constexpr BoxPackID boxPackInvalidID = -1;

    //! Box packing timestamp.
    typedef uint64_t BoxPackTimestamp;

    //! Box packing node.
    //!
    //! References:
    //! - http://blackpawn.com/texts/lightmaps/
    struct BoxPackNode
    {
        Box2I box;
        BoxPackID id = boxPackInvalidID;
        BoxPackTimestamp timestamp = 0;
        std::array<std::shared_ptr<BoxPackNode>, 2> children;

        bool isBranch() const;
        bool isOccupied() const;
    };

    //! Pack boxes together.
    class BoxPack : public std::enable_shared_from_this<BoxPack>
    {
        FEATHER_TK_NON_COPYABLE(BoxPack);

    private:
        BoxPack() = default;

    public:
        static std::shared_ptr<BoxPack> create(const Size2I&, int border = 0);

        const std::shared_ptr<BoxPackNode>& getRoot() const;

        std::vector<std::shared_ptr<BoxPackNode> > getNodes() const;

        std::shared_ptr<BoxPackNode> getNode(BoxPackID);

        std::shared_ptr<BoxPackNode> insert(const Size2I&);

    private:
        void _getNodes(
            const std::shared_ptr<BoxPackNode>&,
            std::vector<std::shared_ptr<BoxPackNode> >&) const;

        std::shared_ptr<BoxPackNode> _insert(
            std::shared_ptr<BoxPackNode>,
            const Size2I&);

        void _removeFromMap(const std::shared_ptr<BoxPackNode>&);

        int _border = 0;
        std::shared_ptr<BoxPackNode> _root;
        BoxPackID _id = 0;
        BoxPackTimestamp _timestamp = 0;
        std::map<BoxPackID, std::shared_ptr<BoxPackNode>> _idToNode;
    };

    ///@}
}
