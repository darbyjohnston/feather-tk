// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/UI/TextEdit.h>

namespace ftk
{
    class TextPos
    {
    public:
        TextPos() = default;
        TextPos(int line, int chr);

        int line = -1;
        int chr = -1;

        bool operator == (const TextPos&) const;
        bool operator != (const TextPos&) const;
        bool operator < (const TextPos&) const;
        bool operator <= (const TextPos&) const;
        bool operator > (const TextPos&) const;
        bool operator >= (const TextPos&) const;
    };

    const TextPos posInvalid(-1, -1);

    enum class MoveCursor
    {
        Left,
        Right,
        Up,
        Down,
        Home,
        End
    };

    typedef std::pair<TextPos, TextPos> SelectionPair;

    class Selection
    {
    public:
        Selection() = default;

        const SelectionPair& get() const;
        SelectionPair getSorted() const;
        bool isValid() const;

        void set(const SelectionPair&);
        void setFirst(const TextPos&);
        void setSecond(const TextPos&);

        void select(const SelectionPair&);
        void select(const TextPos& first, const TextPos& second);
        void clear();

        bool operator == (const Selection&) const;
        bool operator != (const Selection&) const;

    private:
        SelectionPair _pair = std::make_pair(posInvalid, posInvalid);
    };

    class TextEditModel : public std::enable_shared_from_this<TextEditModel>
    {
    protected:
        void _init();

        TextEditModel();

    public:
        virtual ~TextEditModel();

        static std::shared_ptr<TextEditModel> create();

        const std::vector<std::string>& getText() const;

        std::shared_ptr<IObservableList<std::string> > observeText() const;

        void setText(const std::vector<std::string>&);

        void clearText();

        const TextPos& getCursor() const;

        std::shared_ptr<IObservableValue<TextPos> > observeCursor() const;

        void setCursor(const TextPos&);

        void moveCursor(MoveCursor, bool select = false);

        const Selection& getSelection() const;

        std::shared_ptr<IObservableValue<Selection> > observeSelection() const;

        void setSelection(const Selection&);

        void selectAll();

        void selectNone();

    private:
        FTK_PRIVATE();
    };

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

        void selectNone();

        FontRole getFontRole() const;

        void setFontRole(FontRole);

        Box2I getCursorBox() const;

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
        TextPos _getCursorPos(const V2I&) const;
        void _cursorReset();

        void _textUpdate();

        FTK_PRIVATE();
    };
}
