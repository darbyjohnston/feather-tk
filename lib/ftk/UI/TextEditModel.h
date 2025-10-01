// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <ftk/UI/Event.h>

#include <ftk/Core/ObservableList.h>
#include <ftk/Core/ObservableValue.h>

namespace ftk
{
    //! \name Text Widgets
    ///@{

    //! Text edit position.
    struct TextEditPos
    {
        TextEditPos() = default;
        TextEditPos(int line, int chr);

        int line = -1;
        int chr = -1;

        bool operator == (const TextEditPos&) const;
        bool operator != (const TextEditPos&) const;
        bool operator < (const TextEditPos&) const;
        bool operator <= (const TextEditPos&) const;
        bool operator > (const TextEditPos&) const;
        bool operator >= (const TextEditPos&) const;
    };

    //! Invalid text edit position.
    const TextEditPos textEditPosInvalid(-1, -1);

    //! Text edit selection pair.
    typedef std::pair<TextEditPos, TextEditPos> TextEditSelectionPair;

    //! Text edit selection pair.
    class TextEditSelection
    {
    public:
        TextEditSelection() = default;

        //! Get the selection.
        const TextEditSelectionPair& get() const;

        //! Get the sorted selection.
        TextEditSelectionPair getSorted() const;

        //! Get whether the selection is valid.
        bool isValid() const;

        //! Set the selection.
        void set(const TextEditSelectionPair&);

        //! Set the start of the selection.
        void setFirst(const TextEditPos&);

        //! Set the end of the selection.
        void setSecond(const TextEditPos&);

        void select(const TextEditSelectionPair&);
        void select(const TextEditPos& first, const TextEditPos& second);
        void clear();

        bool operator == (const TextEditSelection&) const;
        bool operator != (const TextEditSelection&) const;

    private:
        TextEditSelectionPair _pair = std::make_pair(textEditPosInvalid, textEditPosInvalid);
    };

    //! Text edit model.
    class TextEditModel : public std::enable_shared_from_this<TextEditModel>
    {
    protected:
        void _init();

        TextEditModel();

    public:
        virtual ~TextEditModel();

        //! Create a new text edit model.
        static std::shared_ptr<TextEditModel> create();

        //! Get the text.
        const std::vector<std::string>& getText() const;

        //! Observer the text.
        std::shared_ptr<IObservableList<std::string> > observeText() const;

        //! Set the text.
        void setText(const std::vector<std::string>&);

        //! Clear the text.
        void clearText();

        //! Get the cursor.
        const TextEditPos& getCursor() const;

        //! Observe the cursor.
        std::shared_ptr<IObservableValue<TextEditPos> > observeCursor() const;

        //! Set the cursor.
        void setCursor(const TextEditPos&);

        //! Get the selection.
        const TextEditSelection& getSelection() const;

        //! Observer the selection.
        std::shared_ptr<IObservableValue<TextEditSelection> > observeSelection() const;

        //! Set the selection.
        void setSelection(const TextEditSelection&);

        //! Select all.
        void selectAll();

        //! Clear the selection.
        void clearSelection();

        //! Add text.
        void text(const std::string&);

        //! Handle keys.
        bool key(Key, int modifiers = 0);

    private:
        
        FTK_PRIVATE();
    };
        
    ///@}
}
