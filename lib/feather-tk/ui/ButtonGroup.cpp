// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/ui/ButtonGroup.h>

namespace feather_tk
{
    struct ButtonGroup::Private
    {
        ButtonGroupType type = ButtonGroupType::Click;
        std::vector<std::shared_ptr<IButton> > buttons;
        int radio = -1;
        std::function<void(int)> clickedCallback;
        std::function<void(int, bool)> checkedCallback;
    };

    void ButtonGroup::_init(
        const std::shared_ptr<Context>& context,
        ButtonGroupType type)
    {
        FEATHER_TK_P();
        p.type = type;
    }

    ButtonGroup::ButtonGroup() :
        _p(new Private)
    {}

    ButtonGroup::~ButtonGroup()
    {}

    std::shared_ptr<ButtonGroup> ButtonGroup::create(
        const std::shared_ptr<Context>& context,
        ButtonGroupType type)
    {
        auto out = std::shared_ptr<ButtonGroup>(new ButtonGroup);
        out->_init(context, type);
        return out;
    }

    const std::vector<std::shared_ptr<IButton> >& ButtonGroup::getButtons() const
    {
        return _p->buttons;
    }

    void ButtonGroup::addButton(const std::shared_ptr<IButton>& button)
    {
        FEATHER_TK_P();
        switch (p.type)
        {
        case ButtonGroupType::Click:
            button->setCheckable(false);
            break;
        case ButtonGroupType::Check:
            button->setCheckable(true);
            break;
        case ButtonGroupType::Radio:
            button->setCheckable(true);
            break;
        case ButtonGroupType::Toggle:
            button->setCheckable(true);
            break;
        default: break;
        }
        const size_t index = p.buttons.size();
        p.buttons.push_back(button);
        button->setClickedCallback(
            [this, index]
            {
                if (_p->clickedCallback)
                {
                    _p->clickedCallback(index);
                }
            });
        button->setCheckedCallback(
            [this, index](bool value)
            {
                switch (_p->type)
                {
                case ButtonGroupType::Check:
                    if (_p->checkedCallback)
                    {
                        _p->checkedCallback(index, value);
                    }
                    break;
                case ButtonGroupType::Radio:
                    for (size_t i = 0; i < _p->buttons.size(); ++i)
                    {
                        _p->buttons[i]->setChecked(i == index);
                    }
                    if (_p->checkedCallback && index != _p->radio)
                    {
                        _p->checkedCallback(index, true);
                    }
                    _p->radio = index;
                    break;
                case ButtonGroupType::Toggle:
                    for (size_t i = 0; i < _p->buttons.size(); ++i)
                    {
                        if (i != index)
                        {
                            _p->buttons[i]->setChecked(false);
                        }
                    }
                    if (_p->checkedCallback)
                    {
                        _p->checkedCallback(index, value);
                    }
                    break;
                default: break;
                }
            });
    }

    void ButtonGroup::clearButtons()
    {
        FEATHER_TK_P();
        p.buttons.clear();
    }

    void ButtonGroup::setChecked(int index, bool value)
    {
        FEATHER_TK_P();
        switch (p.type)
        {
        case ButtonGroupType::Check:
            if (index >= 0 && index < p.buttons.size())
            {
                p.buttons[index]->setChecked(value);
            }
            break;
        case ButtonGroupType::Radio:
            for (size_t i = 0; i < p.buttons.size(); ++i)
            {
                p.buttons[i]->setChecked(i == index);
            }
            p.radio = index;
            break;
        case ButtonGroupType::Toggle:
            for (size_t i = 0; i < p.buttons.size(); ++i)
            {
                p.buttons[i]->setChecked(i == index ? value : false);
            }
            break;
        default: break;
        }
    }

    void ButtonGroup::setClickedCallback(const std::function<void(int)>& value)
    {
        _p->clickedCallback = value;
    }

    void ButtonGroup::setCheckedCallback(const std::function<void(int, bool)>& value)
    {
        _p->checkedCallback = value;
    }
}