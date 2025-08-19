// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/MDIWidgetTest.h>

#include <feather-tk/ui/App.h>
#include <feather-tk/ui/Label.h>
#include <feather-tk/ui/MDICanvas.h>
#include <feather-tk/ui/MDIWidget.h>
#include <feather-tk/ui/Window.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>

namespace feather_tk
{
    namespace ui_test
    {
        MDIWidgetTest::MDIWidgetTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::ui_test::MDIWidgetTest")
        {}

        MDIWidgetTest::~MDIWidgetTest()
        {}

        std::shared_ptr<MDIWidgetTest> MDIWidgetTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<MDIWidgetTest>(new MDIWidgetTest(context));
        }
                
        void MDIWidgetTest::run()
        {
            _enums();
            _widget();
        }

        void MDIWidgetTest::_enums()
        {
            FEATHER_TK_TEST_ENUM(MDIResize);
        }

        void MDIWidgetTest::_widget()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("MDIWidgetTest");
                auto app = App::create(
                    context,
                    argv,
                    "MDIWidgetTest",
                    "MDI widget test.");
                auto window = Window::create(context, "MDIWidgetTest");
                app->addWindow(window);
                window->show();
                app->tick();

                auto canvas = MDICanvas::create(context, window);
                canvas->setCanvasSize(Size2I(100, 100));
                canvas->setCanvasSize(Size2I(100, 100));
                FEATHER_TK_ASSERT(Size2I(100, 100) == canvas->getCanvasSize());
                canvas->setCanvasSize(Size2I(1000, 1000));
                canvas->setGridSize(Size2I(2, 2));
                canvas->setGridSize(Size2I(2, 2));
                FEATHER_TK_ASSERT(Size2I(2, 2) == canvas->getGridSize());
                canvas->setGridSize(Size2I(20, 20));

                auto label = Label::create(context, "Label");
                auto widget = canvas->addWidget("Widget 0", V2I(100, 100), label);
                FEATHER_TK_ASSERT("Widget 0" == widget->getTitle());
                widget->setTitle("Widget");
                FEATHER_TK_ASSERT("Widget" == widget->getTitle());
                app->tick();
                label.reset();
                widget->setParent(nullptr);
                widget.reset();
                label = Label::create(context, "Label 1");
                widget = canvas->addWidget("Widget 1", V2I(100, 100), label);
                label = Label::create(context, "Label 2");
                widget->setWidget(label);
                widget->setWidget(label);
                FEATHER_TK_ASSERT(label == widget->getWidget());
                widget->setPos(V2I(200, 200));
                widget->setSize(Size2I(1000, 1000));
            }
        }
    }
}

