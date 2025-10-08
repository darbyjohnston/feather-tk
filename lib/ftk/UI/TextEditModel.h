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

    //! Text edit model options.
    struct TextEditModelOptions
    {
        int tabSpaceCount = 4;

        bool operator == (const TextEditModelOptions&) const;
        bool operator != (const TextEditModelOptions&) const;
    };

    //! Text edit model.
    class TextEditModel : public std::enable_shared_from_this<TextEditModel>
    {
    protected:
        void _init(const std::shared_ptr<Context>&);

        TextEditModel();

    public:
        virtual ~TextEditModel();

        //! Create a new text edit model.
        static std::shared_ptr<TextEditModel> create(const std::shared_ptr<Context>&);

        //! Get the text.
        const std::vector<std::string>& getText() const;

        //! Observer the text.
        std::shared_ptr<IObservableList<std::string> > observeText() const;

        //! Set the text. Setting the text will also set the cursor to the
        //! beginning of the text and clear the selection.
        void setText(const std::vector<std::string>&);

        //! Clear the text.
        void clearText();

        //! Get the cursor.
        const TextEditPos& getCursor() const;

        //! Observe the cursor.
        std::shared_ptr<IObservableValue<TextEditPos> > observeCursor() const;

        //! Set the cursor. Setting the cursor clears the selection.
        void setCursor(const TextEditPos&);

        //! Get the selection.
        const TextEditSelection& getSelection() const;

        //! Observer the selection.
        std::shared_ptr<IObservableValue<TextEditSelection> > observeSelection() const;

        //! Set the selection. Setting the selection also sets the cursor to
        //! the end of the selection.
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

        //! Get the options.
        const TextEditModelOptions& getOptions() const;

        //! Observe the options.
        std::shared_ptr<IObservableValue<TextEditModelOptions> > observeOptions() const;

        //! Set the options.
        void setOptions(const TextEditModelOptions&);

    private:
        TextEditPos _getNext(const TextEditPos&) const;
        TextEditPos _getPrev(const TextEditPos&) const;

        TextEditSelection _getSelectAll() const;
        std::vector<std::string> _getSelection(const TextEditSelection&) const;

        void _insert(
            const TextEditPos&,
            const std::vector<std::string>&);
        void _replace(
            const TextEditSelection&,
            const std::vector<std::string>&);

        FTK_PRIVATE();
    };

    std::ostream& operator << (std::ostream&, const TextEditPos&);
    std::ostream& operator << (std::ostream&, const TextEditSelection&);

    ///@}
}
