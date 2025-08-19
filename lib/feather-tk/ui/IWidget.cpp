// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/ui/IWidget.h>

#include <feather-tk/ui/IWindow.h>

#include <feather-tk/core/String.h>

namespace feather_tk
{
    void IWidget::_init(
        const std::shared_ptr<Context>& context,
        const std::string& objectName,
        const std::shared_ptr<IWidget>& parent)
    {
        _context = context;
        _objectName = objectName;
        _parent = parent;
        if (parent)
        {
            parent->_children.push_back(
                std::static_pointer_cast<IWidget>(shared_from_this()));

            ChildAddEvent event(shared_from_this());
            parent->childAddEvent(event);
        }
    }

    IWidget::IWidget()
    {}

    IWidget::~IWidget()
    {}

    void IWidget::setObjectName(const std::string& value)
    {
        _objectName = value;
    }

    std::string IWidget::getObjectPath() const
    {
        std::vector<std::string> names;
        auto widget = shared_from_this();
        while (widget)
        {
            names.push_back(widget->getObjectName());
            widget = widget->getParent().lock();
        }
        std::reverse(names.begin(), names.end());
        return join(names, '/');
    }

    void IWidget::setBackgroundRole(ColorRole value)
    {
        if (value == _backgroundRole)
            return;
        _backgroundRole = value;
        _setDrawUpdate();
    }

    void IWidget::setParent(const std::shared_ptr<IWidget>& value)
    {
        if (!value)
        {
            _releaseMouse();
            releaseKeyFocus();
        }
        auto widget = shared_from_this();
        if (auto parent = _parent.lock())
        {
            auto i = parent->_children.begin();
            int j = 0;
            for (; i != parent->_children.end(); ++i, ++j)
            {
                if (*i == widget)
                {
                    break;
                }
            }
            if (i != parent->_children.end())
            {
                ChildRemoveEvent event(*i, j);
                parent->_children.erase(i);
                parent->childRemoveEvent(event);
                parent->_setSizeUpdate();
                parent->_setDrawUpdate();
            }
        }
        _parent = value;
        if (value)
        {
            value->_children.push_back(
                std::static_pointer_cast<IWidget>(shared_from_this()));
            ChildAddEvent event(shared_from_this());
            value->childAddEvent(event);
            value->_setSizeUpdate();
            value->_setDrawUpdate();
        }
    }

    int IWidget::getChildIndex(const std::shared_ptr<IWidget>& value) const
    {
        int out = -1;
        int i = 0;
        auto j = _children.begin();
        for (; *j != value && j != _children.end(); ++i, ++j)
            ;
        if (j != _children.end())
        {
            out = i;
        }
        return out;
    }

    void IWidget::moveToFront(const std::shared_ptr<IWidget>& value)
    {
        auto i = std::find(_children.begin(), _children.end(), value);
        if (i != _children.end())
        {
            auto child = *i;
            _children.erase(i);
            _children.push_back(child);
            _setSizeUpdate();
            _setDrawUpdate();
        }
    }

    void IWidget::moveToBack(const std::shared_ptr<IWidget>& value)
    {
        auto i = std::find(_children.begin(), _children.end(), value);
        if (i != _children.end())
        {
            auto child = *i;
            _children.erase(i);
            _children.push_front(child);
            _setSizeUpdate();
            _setDrawUpdate();
        }
    }

    void IWidget::moveToIndex(const std::shared_ptr<IWidget>& value, size_t index)
    {
        auto i = _children.begin();
        for (; i != _children.end() && *i != value; ++i)
            ;
        if (i != _children.end())
        {
            _children.erase(i);
            i = _children.begin();
            int j = 0;
            for (; i != _children.end() && j < index; ++i, ++j)
                ;
            if (i != _children.end())
            {
                _children.insert(i, value);
            }
            else
            {
                _children.push_back(value);
            }
            _setSizeUpdate();
            _setDrawUpdate();
        }
    }

    std::shared_ptr<IWindow> IWidget::getWindow()
    {
        std::shared_ptr<IWidget> out = shared_from_this();
        auto parent = out->_parent.lock();
        while (parent)
        {
            out = parent;
            parent = parent->_parent.lock();
        }
        return std::dynamic_pointer_cast<IWindow>(out);
    }

    void IWidget::setHStretch(Stretch value)
    {
        if (value == _hStretch)
            return;
        _hStretch = value;
        _setSizeUpdate();
        _setDrawUpdate();
    }

    void IWidget::setVStretch(Stretch value)
    {
        if (value == _vStretch)
            return;
        _vStretch = value;
        _setSizeUpdate();
        _setDrawUpdate();
    }

    void IWidget::setStretch(Stretch horizontal, Stretch vertical)
    {
        if (horizontal == _hStretch && vertical == _vStretch)
            return;
        _hStretch = horizontal;
        _vStretch = vertical;
        _setSizeUpdate();
        _setDrawUpdate();
    }

    void IWidget::setStretch(Stretch value)
    {
        setStretch(value, value);
    }

    void IWidget::setHAlign(HAlign value)
    {
        if (value == _hAlign)
            return;
        _hAlign = value;
        _setSizeUpdate();
        _setDrawUpdate();
    }

    void IWidget::setVAlign(VAlign value)
    {
        if (value == _vAlign)
            return;
        _vAlign = value;
        _setSizeUpdate();
        _setDrawUpdate();
    }

    void IWidget::setAlign(HAlign hAlign, VAlign vAlign)
    {
        if (hAlign == _hAlign && vAlign == _vAlign)
            return;
        _hAlign = hAlign;
        _vAlign = vAlign;
        _setSizeUpdate();
        _setDrawUpdate();
    }

    void IWidget::setGeometry(const Box2I& value)
    {
        if (value == _geometry)
            return;
        _geometry = value;
        _setSizeUpdate();
        _setDrawUpdate();
    }

    void IWidget::setPos(const V2I& value)
    {
        setGeometry(Box2I(value, _geometry.size()));
    }

    void IWidget::setSize(const Size2I& value)
    {
        setGeometry(Box2I(_geometry.min, value));
    }

    void IWidget::setVisible(bool value)
    {
        if (value == _visible)
            return;
        _visible = value;
        if (!_visible)
        {
            _releaseMouse();
            releaseKeyFocus();
        }
        _setSizeUpdate();
        _setDrawUpdate();
        if (auto parent = _parent.lock())
        {
            parent->_setSizeUpdate();
            parent->_setDrawUpdate();
        }
    }

    void IWidget::show()
    {
        setVisible(true);
    }

    void IWidget::hide()
    {
        setVisible(false);
    }

    Box2I IWidget::getChildrenClipRect() const
    {
        return _geometry;
    }

    void IWidget::setEnabled(bool value)
    {
        if (value == _enabled)
            return;
        _enabled = value;
        if (!_enabled)
        {
            _releaseMouse();
            releaseKeyFocus();
        }
        _setSizeUpdate();
        _setDrawUpdate();
    }

    void IWidget::setAcceptsKeyFocus(bool value)
    {
        _acceptsKeyFocus = value;
    }

    void IWidget::takeKeyFocus()
    {
        if (auto window = getWindow())
        {
            window->setKeyFocus(shared_from_this());
        }
    }

    void IWidget::releaseKeyFocus()
    {
        if (_keyFocus)
        {
            if (auto window = getWindow())
            {
                window->setKeyFocus(nullptr);
            }
        }
        for (const auto& child : _children)
        {
            child->releaseKeyFocus();
        }
    }

    void IWidget::setTooltip(const std::string& value)
    {
        _tooltip = value;
    }

    void IWidget::childAddEvent(const ChildAddEvent&)
    {}

    void IWidget::childRemoveEvent(const ChildRemoveEvent&)
    {}

    void IWidget::tickEvent(
        bool parentsVisible,
        bool parentsEnabled,
        const TickEvent& event)
    {
        _parentsVisible = parentsVisible;
        _parentsEnabled = parentsEnabled;
    }

    void IWidget::sizeHintEvent(const SizeHintEvent& event)
    {
        _updates &= ~static_cast<int>(Update::Size);
    }

    void IWidget::clipEvent(const Box2I&, bool clipped)
    {
        if (clipped && clipped != _clipped)
        {
            _releaseMouse();
            releaseKeyFocus();
        }
        _clipped = clipped;
    }

    void IWidget::drawEvent(
        const Box2I&,
        const DrawEvent& event)
    {
        _updates &= ~static_cast<int>(Update::Draw);
        if (_backgroundRole != ColorRole::None)
        {
            event.render->drawRect(
                _geometry,
                event.style->getColorRole(_backgroundRole));
        }
    }

    void IWidget::drawOverlayEvent(
        const Box2I&,
        const DrawEvent&)
    {
        _updates &= ~static_cast<int>(Update::Draw);
    }

    void IWidget::mouseEnterEvent(MouseEnterEvent& event)
    {
        if (_mouseHoverEnabled)
        {
            event.accept = true;
        }
        _mouseInside = true;
        _mousePos = event.pos;
    }

    void IWidget::mouseLeaveEvent()
    {
        _mouseInside = false;
    }

    void IWidget::mouseMoveEvent(MouseMoveEvent& event)
    {
        if (_mouseHoverEnabled)
        {
            event.accept = true;
        }
        _mousePos = event.pos;
    }

    void IWidget::mousePressEvent(MouseClickEvent& event)
    {
        const bool button =
            _mousePressButton != 0 ?
            event.button == _mousePressButton :
            true;
        const bool modifiers =
            _mousePressModifiers != -1 ?
            event.modifiers == _mousePressModifiers :
            true;
        if (_mousePressEnabled && button && modifiers)
        {
            event.accept = true;
            _mousePos = event.pos;
            _mousePress = true;
            _mousePressPos = event.pos;
        }
    }

    void IWidget::mouseReleaseEvent(MouseClickEvent& event)
    {
        if (_mousePress)
        {
            event.accept = true;
            _mousePress = false;
        }
    }

    void IWidget::scrollEvent(ScrollEvent&)
    {}

    void IWidget::keyFocusEvent(bool value)
    {
        _keyFocus = value;
    }

    void IWidget::keyPressEvent(KeyEvent&)
    {}

    void IWidget::keyReleaseEvent(KeyEvent&)
    {}

    void IWidget::textEvent(TextEvent&)
    {}

    void IWidget::dragEnterEvent(DragAndDropEvent&)
    {}

    void IWidget::dragLeaveEvent(DragAndDropEvent&)
    {}

    void IWidget::dragMoveEvent(DragAndDropEvent&)
    {}

    void IWidget::dropEvent(DragAndDropEvent&)
    {}

    void IWidget::_setMouseHoverEnabled(bool value)
    {
        _mouseHoverEnabled = value;
    }

    void IWidget::_setMousePressEnabled(bool value, int button, int modifiers)
    {
        _mousePressEnabled = value;
        _mousePressButton = button;
        _mousePressModifiers = modifiers;
    }

    void IWidget::_releaseMouse()
    {
        if (_mouseInside || _mousePress)
        {
            _mouseInside = false;
            _mousePress = false;
            _setDrawUpdate();
        }
        for (const auto& child : _children)
        {
            child->_releaseMouse();
        }
    }
}