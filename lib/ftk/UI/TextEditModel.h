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
        bool operator > (const TextEditPos&) const;
    };

    //! Invalid text edit position.
    const TextEditPos textEditPosInvalid(-1, -1);

    //! Text edit selection.
    struct TextEditSelection
    {
        TextEditSelection() = default;
        TextEditSelection(const TextEditPos&);
        TextEditSelection(const TextEditPos&, const TextEditPos&);

        TextEditPos first = textEditPosInvalid;
        TextEditPos second = textEditPosInvalid;

        //! Get whether the selection is valid.
        bool isValid() const;

        //! Get the minimum.
        TextEditPos min() const;

        //! Get the maximum.
        TextEditPos max() const;

        bool operator == (const TextEditSelection&) const;
        bool operator != (const TextEditSelection&) const;
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

        //! Set the numner of rows in a page.
        void setPageRows(int);

    private:
        
        FTK_PRIVATE();
    };
        
    ///@}
}
