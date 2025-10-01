// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/UI/TextEdit.h>

namespace ftk
{
    class TextEditWidget : public IWidget
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<TextEditModel>&,
            const std::shared_ptr<IWidget>& parent);

        TextEditWidget();

    public:
        virtual ~TextEditWidget();

        static std::shared_ptr<TextEditWidget> create(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<TextEditModel>&,
            const std::shared_ptr<IWidget>& parent = nullptr);

        const std::vector<std::string>& getText() const;
        void setText(const std::vector<std::string>&);
        void clearText();

        void setTextCallback(const std::function<void(const std::vector<std::string>&)>&);
        void setFocusCallback(const std::function<void(bool)>&);

        void selectAll();
        void clearSelection();

        void setOptions(const TextEditOptions&);

        Box2I getCursorBox(bool margin = false) const;

        void setGeometry(const Box2I&) override;
        void setVisible(bool) override;
        void setEnabled(bool) override;
        void tickEvent(
            bool,
            bool,
            const TickEvent&) override;
        void sizeHintEvent(const SizeHintEvent&) override;
        void drawEvent(const Box2I&, const DrawEvent&) override;
        void mouseMoveEvent(MouseMoveEvent&) override;
        void mousePressEvent(MouseClickEvent&) override;
        void keyFocusEvent(bool) override;
        void keyPressEvent(KeyEvent&) override;
        void keyReleaseEvent(KeyEvent&) override;
        void textEvent(TextEvent&) override;

    private:
        TextEditPos _getCursorPos(const V2I&) const;
        void _cursorReset();

        FTK_PRIVATE();
    };
}
