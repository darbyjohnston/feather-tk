// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <UITest/TextEditModelTest.h>

#include <ftk/UI/ClipboardSystem.h>
#include <ftk/UI/TextEditModel.h>

#include <ftk/Core/Assert.h>
#include <ftk/Core/Format.h>

namespace ftk
{
    namespace ui_test
    {
        TextEditModelTest::TextEditModelTest(const std::shared_ptr<Context>& context) :
            ITest(context, "ftk::ui_test::TextEditModelTest")
        {}

        TextEditModelTest::~TextEditModelTest()
        {}

        std::shared_ptr<TextEditModelTest> TextEditModelTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<TextEditModelTest>(new TextEditModelTest(context));
        }
                
        void TextEditModelTest::run()
        {
            if (auto context = _context.lock())
            {
                auto model = TextEditModel::create(context);
                std::vector<std::string> text =
                {
                    "abc",
                    "",
                    "123"
                };
                model->setText(text);
                model->setText(text);
                FTK_ASSERT(text == model->getText());

                std::vector<std::string> text2;
                auto observer = ListObserver<std::string>::create(
                    model->observeText(),
                    [&text2](const std::vector<std::string>& value)
                    {
                        text2 = value;
                    });
                FTK_ASSERT(text2 == text);
                model->clearText();
                FTK_ASSERT(text2.empty());
            }
            if (auto context = _context.lock())
            {
                auto model = TextEditModel::create(context);
                std::vector<std::string> text =
                {
                    "abc",
                    "",
                    "123"
                };
                model->setText(text);

                TextEditPos cursor(0, 0);
                model->setCursor(cursor);
                model->setCursor(cursor);
                FTK_ASSERT(cursor == model->getCursor());

                TextEditPos cursor2;
                auto observer = ValueObserver<TextEditPos>::create(
                    model->observeCursor(),
                    [&cursor2](const TextEditPos& value)
                    {
                        cursor2 = value;
                    });
                cursor.chr = 1000;
                model->setCursor(cursor);
                FTK_ASSERT(cursor2.chr == static_cast<int>(text[0].size()));
                cursor.line = 1000;
                model->setCursor(cursor);
                FTK_ASSERT(cursor2.line == static_cast<int>(text.size()) - 1);
                FTK_ASSERT(cursor2.chr == static_cast<int>(text.back().size()));
            }
            if (auto context = _context.lock())
            {
                auto model = TextEditModel::create(context);
                std::vector<std::string> text =
                {
                    "abc",
                    "",
                    "123"
                };
                model->setText(text);

                TextEditSelection selection(
                    TextEditPos(0, 0),
                    TextEditPos(0, 2));
                model->setSelection(selection);
                model->setSelection(selection);
                FTK_ASSERT(selection == model->getSelection());

                TextEditSelection selection2;
                auto observer = ValueObserver<TextEditSelection>::create(
                    model->observeSelection(),
                    [&selection2](const TextEditSelection& value)
                    {
                        selection2 = value;
                    });
                selection.first.chr = 1000;
                model->setSelection(selection);
                FTK_ASSERT(selection2.first.chr == static_cast<int>(text.front().size()));
                selection.second.line = 1000;
                model->setSelection(selection);
                FTK_ASSERT(selection2.second.line == static_cast<int>(text.size()) - 1);
                FTK_ASSERT(selection2.second.chr == 2);

                model->clearSelection();
                FTK_ASSERT(!selection2.isValid());
                model->selectAll();
                FTK_ASSERT(selection2.isValid());
                FTK_ASSERT(selection2.second.line == static_cast<int>(text.size()) - 1);
                FTK_ASSERT(selection2.second.chr == static_cast<int>(text.back().size()));
            }
            if (auto context = _context.lock())
            {
                auto model = TextEditModel::create(context);
                std::vector<std::string> text;
                model->setText(text);

                std::vector<std::string> text2;
                auto observer = ListObserver<std::string>::create(
                    model->observeText(),
                    [&text2](const std::vector<std::string>& value)
                    {
                        text2 = value;
                    });

                model->text("34");
                FTK_ASSERT(text2[0] == "34");
                model->setCursor(TextEditPos(0, 0));
                model->text("12");
                FTK_ASSERT(text2[0] == "1234");
                model->setCursor(TextEditPos(0, 4));
                model->text("56");
                FTK_ASSERT(text2[0] == "123456");

                model->selectAll();
                model->text("abc");
                FTK_ASSERT(text2[0] == "abc");
                FTK_ASSERT(!model->getSelection().isValid());

                model->setSelection(TextEditSelection(
                    TextEditPos(0, 0),
                    TextEditPos(0, 1)));
                model->text("1");
                FTK_ASSERT(text2[0] == "1bc");
                FTK_ASSERT(!model->getSelection().isValid());

                model->setSelection(TextEditSelection(
                    TextEditPos(0, 1),
                    TextEditPos(0, 2)));
                model->text("2");
                FTK_ASSERT(text2[0] == "12c");
                FTK_ASSERT(!model->getSelection().isValid());

                model->setSelection(TextEditSelection(
                    TextEditPos(0, 2),
                    TextEditPos(0, 3)));
                model->text("3");
                FTK_ASSERT(text2[0] == "123");
                FTK_ASSERT(!model->getSelection().isValid());
            }
            if (auto context = _context.lock())
            {
                auto model = TextEditModel::create(context);
                std::vector<std::string> text =
                {};
                model->setText(text);

                std::vector<std::string> text2;
                auto observer = ListObserver<std::string>::create(
                    model->observeText(),
                    [&text2](const std::vector<std::string>& value)
                    {
                        text2 = value;
                    });

                auto clipboard = context->getSystem<ClipboardSystem>();
                clipboard->setText("\n123\nabc\n");

                model->key(Key::V, static_cast<int>(KeyModifier::Control));
                FTK_ASSERT(text2[0] == "");
                FTK_ASSERT(text2[1] == "123");
                FTK_ASSERT(text2[2] == "abc");
                FTK_ASSERT(text2[3] == "");
                
                model->selectAll();
                model->key(Key::V, static_cast<int>(KeyModifier::Control));
                FTK_ASSERT(text2[0] == "");
                FTK_ASSERT(text2[1] == "123");
                FTK_ASSERT(text2[2] == "abc");
                FTK_ASSERT(text2[3] == "");

                model->selectAll();
                model->setText({ "!!" });
                model->setCursor(TextEditPos(0, 1));
                model->key(Key::V, static_cast<int>(KeyModifier::Control));
                FTK_ASSERT(text2[0] == "!");
                FTK_ASSERT(text2[1] == "123");
                FTK_ASSERT(text2[2] == "abc");
                FTK_ASSERT(text2[3] == "!");

                model->selectAll();
                model->setText({ "!!!" });
                model->setSelection(TextEditSelection(
                    TextEditPos(0, 1),
                    TextEditPos(0, 2)));
                model->key(Key::V, static_cast<int>(KeyModifier::Control));
                FTK_ASSERT(text2[0] == "!");
                FTK_ASSERT(text2[1] == "123");
                FTK_ASSERT(text2[2] == "abc");
                FTK_ASSERT(text2[3] == "!");

                model->setSelection(TextEditSelection());
                model->key(Key::C, static_cast<int>(KeyModifier::Control));
                FTK_ASSERT(clipboard->getText().empty());

                model->setSelection(TextEditSelection(
                    TextEditPos(0, 0),
                    TextEditPos(0, 1)));
                model->key(Key::C, static_cast<int>(KeyModifier::Control));
                FTK_ASSERT("!" == clipboard->getText());

                model->setSelection(TextEditSelection(
                    TextEditPos(1, 1),
                    TextEditPos(2, 2)));
                model->key(Key::C, static_cast<int>(KeyModifier::Control));
                FTK_ASSERT("23\nab" == clipboard->getText());

                model->setSelection(TextEditSelection());
                model->key(Key::X, static_cast<int>(KeyModifier::Control));
                FTK_ASSERT(clipboard->getText().empty());

                model->setSelection(TextEditSelection(
                    TextEditPos(0, 0),
                    TextEditPos(0, 1)));
                model->key(Key::X, static_cast<int>(KeyModifier::Control));
                FTK_ASSERT("!" == clipboard->getText());
                FTK_ASSERT(text2[0] == "");
                FTK_ASSERT(text2[1] == "123");
                FTK_ASSERT(text2[2] == "abc");
                FTK_ASSERT(text2[3] == "!");

                model->setSelection(TextEditSelection(
                    TextEditPos(1, 1),
                    TextEditPos(2, 2)));
                model->key(Key::X, static_cast<int>(KeyModifier::Control));
                FTK_ASSERT("23\nab" == clipboard->getText());
                FTK_ASSERT(text2[0] == "");
                FTK_ASSERT(text2[1] == "1c");
                FTK_ASSERT(text2[2] == "!");

                model->selectAll();
                model->key(Key::X, static_cast<int>(KeyModifier::Control));
                FTK_ASSERT("\n1c\n!" == clipboard->getText());
                FTK_ASSERT(text2.empty());
            }
            if (auto context = _context.lock())
            {
                auto model = TextEditModel::create(context);
                std::vector<std::string> text =
                {
                    "abc",
                    "",
                    "123"
                };
                model->setText(text);

                std::vector<std::string> text2;
                auto observer = ListObserver<std::string>::create(
                    model->observeText(),
                    [&text2](const std::vector<std::string>& value)
                    {
                        text2 = value;
                    });

                model->setCursor(TextEditPos(0, 0));
                model->key(Key::Left);
                FTK_ASSERT(TextEditPos(0, 0) == model->getCursor());
                model->key(Key::Right);
                FTK_ASSERT(TextEditPos(0, 1) == model->getCursor());
                for (int i = 0; i < text.size(); ++i)
                {
                    for (int j = 0; j <= text[i].size(); ++j)
                    {
                        model->key(Key::Right);
                    }
                }
                FTK_ASSERT(TextEditPos(2, 3) == model->getCursor());
                model->key(Key::Right);
                FTK_ASSERT(TextEditPos(2, 3) == model->getCursor());

                model->setCursor(TextEditPos(0, 0));
                model->key(Key::End);
                FTK_ASSERT(TextEditPos(0, 3) == model->getCursor());
                model->key(Key::Home);
                FTK_ASSERT(TextEditPos(0, 0) == model->getCursor());
                model->key(Key::Up);
                FTK_ASSERT(TextEditPos(0, 0) == model->getCursor());
                model->key(Key::Down);
                FTK_ASSERT(TextEditPos(1, 0) == model->getCursor());
                for (int i = 0; i <= text.size(); ++i)
                {
                    model->key(Key::Down);
                }
                FTK_ASSERT(TextEditPos(2, 0) == model->getCursor());
                model->key(Key::Down);
                FTK_ASSERT(TextEditPos(2, 0) == model->getCursor());
            }
            if (auto context = _context.lock())
            {
                auto model = TextEditModel::create(context);
                std::vector<std::string> text =
                {
                    "abc",
                    "",
                    "123"
                };
                model->setText(text);

                std::vector<std::string> text2;
                auto textObserver = ListObserver<std::string>::create(
                    model->observeText(),
                    [&text2](const std::vector<std::string>& value)
                    {
                        text2 = value;
                    });
                TextEditPos cursor2;
                auto cursorObserver = ValueObserver<TextEditPos>::create(
                    model->observeCursor(),
                    [&cursor2](const TextEditPos& value)
                    {
                        cursor2 = value;
                    });
                TextEditSelection selection2;
                auto selectionObserver = ValueObserver<TextEditSelection>::create(
                    model->observeSelection(),
                    [&selection2](const TextEditSelection& value)
                    {
                        selection2 = value;
                    });

                model->setCursor(TextEditPos(0, 0));
                model->key(Key::Right, static_cast<int>(KeyModifier::Shift));
                FTK_ASSERT(TextEditSelection(
                    TextEditPos(0, 0),
                    TextEditPos(0, 1)) == selection2);
                for (int i = 0; i < static_cast<int>(text.size()); ++i)
                {
                    for (int j = 0; j <= text[i].size(); ++j)
                    {
                        model->key(Key::Right, static_cast<int>(KeyModifier::Shift));
                    }
                }
                model->key(Key::Right, static_cast<int>(KeyModifier::Shift));
                FTK_ASSERT(TextEditSelection(
                    TextEditPos(0, 0),
                    TextEditPos(2, 3)) == selection2);

                model->clearSelection();
                model->key(Key::Left, static_cast<int>(KeyModifier::Shift));
                model->key(Key::Left, static_cast<int>(KeyModifier::Shift));
                FTK_ASSERT(TextEditSelection(
                    TextEditPos(2, 3),
                    TextEditPos(2, 1)) == selection2);
                for (int i = static_cast<int>(text.size()) - 1; i >= 0; --i)
                {
                    for (int j = static_cast<int>(text[i].size()); j >= 0; --j)
                    {
                        model->key(Key::Left, static_cast<int>(KeyModifier::Shift));
                    }
                }
                FTK_ASSERT(TextEditSelection(
                    TextEditPos(2, 3),
                    TextEditPos(0, 0)) == selection2);

                model->clearSelection();
                model->setPageRows(2);
                model->key(Key::PageDown, static_cast<int>(KeyModifier::Shift));
                model->key(Key::PageDown, static_cast<int>(KeyModifier::Shift));
                FTK_ASSERT(TextEditSelection(
                    TextEditPos(0, 0),
                    TextEditPos(2, 3)) == selection2);

                model->clearSelection();
                model->setPageRows(2);
                model->key(Key::PageUp, static_cast<int>(KeyModifier::Shift));
                model->key(Key::PageUp, static_cast<int>(KeyModifier::Shift));
                FTK_ASSERT(TextEditSelection(
                    TextEditPos(2, 3),
                    TextEditPos(0, 3)) == selection2);
            }
            if (auto context = _context.lock())
            {
                auto model = TextEditModel::create(context);
                std::vector<std::string> text =
                {
                    "abc",
                    "   ",
                    "   123"
                };
                model->setText(text);

                std::vector<std::string> text2;
                auto textObserver = ListObserver<std::string>::create(
                    model->observeText(),
                    [&text2](const std::vector<std::string>& value)
                    {
                        text2 = value;
                    });

                model->selectAll();
                model->key(Key::Tab);
                FTK_ASSERT(text2[0] == "    abc");
                FTK_ASSERT(text2[1] == "       ");
                FTK_ASSERT(text2[2] == "       123");
                model->key(Key::Tab, static_cast<int>(KeyModifier::Shift));
                FTK_ASSERT(text2[0] == "abc");
                FTK_ASSERT(text2[1] == "   ");
                FTK_ASSERT(text2[2] == "   123");
                model->key(Key::Tab, static_cast<int>(KeyModifier::Shift));
                FTK_ASSERT(text2[0] == "abc");
                FTK_ASSERT(text2[1] == "");
                FTK_ASSERT(text2[2] == "123");

                model->setSelection(TextEditSelection(
                    TextEditPos(2, 1),
                    TextEditPos(2, 2)));
                model->key(Key::Tab);
                FTK_ASSERT(text2[0] == "abc");
                FTK_ASSERT(text2[1] == "");
                FTK_ASSERT(text2[2] == "    123");

                model->setCursor(TextEditPos(0, 0));
                model->key(Key::Tab);
                FTK_ASSERT(text2[0] == "    abc");
                FTK_ASSERT(text2[1] == "");
                FTK_ASSERT(text2[2] == "    123");
            }
            if (auto context = _context.lock())
            {
                auto model = TextEditModel::create(context);
                std::vector<std::string> text =
                {
                    "abc",
                    "   ",
                    "123"
                };
                model->setText(text);

                std::vector<std::string> text2;
                auto textObserver = ListObserver<std::string>::create(
                    model->observeText(),
                    [&text2](const std::vector<std::string>& value)
                    {
                        text2 = value;
                    });

                model->key(Key::Backspace);
                model->key(Key::Backspace);
                FTK_ASSERT(TextEditPos(0, 0) == model->getCursor());
                model->setCursor(TextEditPos(text.size() - 1, text.back().size()));
                model->key(Key::Backspace);
                FTK_ASSERT(text2[2] == "12");
                model->key(Key::Backspace);
                model->key(Key::Backspace);
                model->key(Key::Backspace);
                FTK_ASSERT(text2.size() == 2);
                model->setCursor(TextEditPos(1, 0));
                model->key(Key::Backspace);
                FTK_ASSERT(text2.size() == 1);
                FTK_ASSERT(text2[0] == "abc   ");

                model->setSelection(TextEditSelection(
                    TextEditPos(0, 2),
                    TextEditPos(0, 6)));
                model->key(Key::Backspace);
                FTK_ASSERT(text2[0] == "ab");
            }
            if (auto context = _context.lock())
            {
                auto model = TextEditModel::create(context);
                std::vector<std::string> text =
                {
                    "abc",
                    "   ",
                    "123"
                };
                model->setText(text);

                std::vector<std::string> text2;
                auto textObserver = ListObserver<std::string>::create(
                    model->observeText(),
                    [&text2](const std::vector<std::string>& value)
                    {
                        text2 = value;
                    });

                TextEditPos cursor(text.size() - 1, text.back().size());
                model->setCursor(cursor);
                model->key(Key::Delete);
                model->key(Key::Delete);
                FTK_ASSERT(cursor == model->getCursor());
                model->setCursor(TextEditPos(0, 0));
                model->key(Key::Delete);
                FTK_ASSERT(text2[0] == "bc");
                model->key(Key::Delete);
                model->key(Key::Delete);
                model->key(Key::Delete);
                FTK_ASSERT(text2.size() == 2);
                model->setCursor(TextEditPos(0, text2[0].size()));
                model->key(Key::Delete);
                FTK_ASSERT(text2.size() == 1);
                FTK_ASSERT(text2[0] == "   123");

                model->setSelection(TextEditSelection(
                    TextEditPos(0, 0),
                    TextEditPos(0, 4)));
                model->key(Key::Delete);
                FTK_ASSERT(text2[0] == "23");
            }
            if (auto context = _context.lock())
            {
                auto model = TextEditModel::create(context);
                std::vector<std::string> text =
                {
                    "abc",
                    "   ",
                    "123"
                };
                model->setText(text);

                std::vector<std::string> text2;
                auto textObserver = ListObserver<std::string>::create(
                    model->observeText(),
                    [&text2](const std::vector<std::string>& value)
                    {
                        text2 = value;
                    });
                TextEditPos cursor2;
                auto observer = ValueObserver<TextEditPos>::create(
                    model->observeCursor(),
                    [&cursor2](const TextEditPos& value)
                    {
                        cursor2 = value;
                    });

                model->key(Key::Return);
                FTK_ASSERT(text2.size() == 4);
                FTK_ASSERT(text2[0] == "");
                FTK_ASSERT(cursor2 == TextEditPos(1, 0));

                model->key(Key::Right);
                model->key(Key::Return);
                FTK_ASSERT(text2.size() == 5);
                FTK_ASSERT(text2[0] == "");
                FTK_ASSERT(text2[1] == "a");
                FTK_ASSERT(text2[2] == "bc");
                FTK_ASSERT(cursor2 == TextEditPos(2, 0));

                model->key(Key::End);
                model->key(Key::Return);
                FTK_ASSERT(text2.size() == 6);
                FTK_ASSERT(text2[0] == "");
                FTK_ASSERT(text2[1] == "a");
                FTK_ASSERT(text2[2] == "bc");
                FTK_ASSERT(text2[3] == "");
                FTK_ASSERT(cursor2 == TextEditPos(3, 0));
            }
        }
    }
}

