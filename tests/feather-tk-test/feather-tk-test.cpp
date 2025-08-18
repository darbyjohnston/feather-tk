// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "feather-tk-test.h"

#if defined(FEATHER_TK_UI_LIB)
#include <uiTest/ActionTest.h>
//#include <uiTest/AppTest.h>
//#include <uiTest/BellowsTest.h>
//#include <uiTest/ButtonGroupTest.h>
//#include <uiTest/ButtonTest.h>
//#include <uiTest/ColorWidgetTest.h>
//#include <uiTest/ComboBoxTest.h>
//#include <uiTest/ConfirmDialogTest.h>
//#include <uiTest/DoubleEditTest.h>
//#include <uiTest/DoubleEditSliderTest.h>
//#include <uiTest/DoubleSliderTest.h>
#include <uiTest/DoubleModelTest.h>
//#include <uiTest/DragAndDropTest.h>
//#include <uiTest/DrawUtilTest.h>
#include <uiTest/EventTest.h>
//#include <uiTest/FileBrowserTest.h>
//#include <uiTest/FileEditTest.h>
//#include <uiTest/FloatEditTest.h>
//#include <uiTest/FloatEditSliderTest.h>
//#include <uiTest/FloatSliderTest.h>
#include <uiTest/FloatModelTest.h>
//#include <uiTest/GridLayoutTest.h>
//#include <uiTest/GroupBoxTest.h>
//#include <uiTest/IWidgetTest.h>
//#include <uiTest/IconTest.h>
//#include <uiTest/IntEditTest.h>
//#include <uiTest/IntEditSliderTest.h>
//#include <uiTest/IntSliderTest.h>
#include <uiTest/IntModelTest.h>
//#include <uiTest/LabelTest.h>
#include <uiTest/LayoutUtilTest.h>
//#include <uiTest/LineEditTest.h>
//#include <uiTest/ListWidgetTest.h>
//#include <uiTest/MDIWidgetTest.h>
//#include <uiTest/MenuBarTest.h>
//#include <uiTest/MessageDialogTest.h>
//#include <uiTest/PieChartTest.h>
//#include <uiTest/ProgressDialogTest.h>
#include <uiTest/RecentFilesModelTest.h>
//#include <uiTest/RowLayoutTest.h>
//#include <uiTest/ScrollAreaTest.h>
//#include <uiTest/ScrollBarTest.h>
//#include <uiTest/ScrollWidgetTest.h>
//#include <uiTest/SearchBoxTest.h>
//#include <uiTest/SplitterTest.h>
//#include <uiTest/StackLayoutTest.h>
//#include <uiTest/StyleTest.h>
//#include <uiTest/TabWidgetTest.h>
#include <uiTest/WidgetOptionsTest.h>

#if defined(FEATHER_TK_API_GL_4_1) || defined(FEATHER_TK_API_GLES_2)
#include <glTest/MeshTest.h>
#include <glTest/OffscreenBufferTest.h>
#include <glTest/TextureAtlasTest.h>
#include <glTest/TextureTest.h>
#include <glTest/RenderTest.h>
#include <glTest/ShaderTest.h>
#include <glTest/UtilTest.h>
#include <glTest/WindowTest.h>
#endif // FEATHER_TK_API_GL_4_1
#endif // FEATHER_TK_UI_LIB

#include <coreTest/AppTest.h>
#include <coreTest/BoxPackTest.h>
#include <coreTest/BoxTest.h>
#include <coreTest/CmdLineTest.h>
#include <coreTest/ColorTest.h>
#include <coreTest/CommandTest.h>
#include <coreTest/ErrorTest.h>
#include <coreTest/FileIOTest.h>
#include <coreTest/FileTest.h>
#include <coreTest/FontSystemTest.h>
#include <coreTest/FormatTest.h>
#include <coreTest/ImageIOTest.h>
#include <coreTest/ImageTest.h>
#include <coreTest/LRUCacheTest.h>
#include <coreTest/MathTest.h>
#include <coreTest/MatrixTest.h>
#include <coreTest/MemoryTest.h>
#include <coreTest/MeshTest.h>
#include <coreTest/NoiseTest.h>
#include <coreTest/OSTest.h>
#include <coreTest/ObservableTest.h>
#include <coreTest/PNGTest.h>
#include <coreTest/RandomTest.h>
#include <coreTest/RangeTest.h>
#include <coreTest/RenderOptionsTest.h>
#include <coreTest/RenderUtilTest.h>
#include <coreTest/SizeTest.h>
#include <coreTest/StringTest.h>
#include <coreTest/SystemTest.h>
#include <coreTest/TimeTest.h>
#include <coreTest/TimerTest.h>
#include <coreTest/VectorTest.h>

#include <testLib/ITest.h>

#if defined(FEATHER_TK_UI_LIB)
#include <feather-tk/ui/Init.h>

#if defined(FEATHER_TK_API_GL_4_1) || defined(FEATHER_TK_API_GLES_2)
#include <feather-tk/gl/Init.h>
#endif // FEATHER_TK_API_GL_4_1
#endif // FEATHER_TK_UI_LIB

#include <feather-tk/core/CmdLine.h>
#include <feather-tk/core/Context.h>
#include <feather-tk/core/Format.h>
#include <feather-tk/core/Time.h>

#include <iostream>

namespace feather_tk
{
    namespace tests
    {
        struct App::Private
        {
            std::shared_ptr<CmdLineValueArg<std::string> > testName;
            std::vector<std::shared_ptr<test::ITest> > tests;
            std::chrono::steady_clock::time_point startTime;
        };
        
        void App::_init(
            const std::shared_ptr<Context>& context,
            std::vector<std::string>& argv)
        {
            FEATHER_TK_P();
            p.testName = CmdLineValueArg<std::string>::create(
                "Test",
                "Name of the test to run.",
                true);
            IApp::_init(
                context,
                argv,
                "feather-tk-test",
                "Test application",
                { p.testName });
            p.startTime = std::chrono::steady_clock::now();                
#if defined(FEATHER_TK_UI_LIB)
#if defined(FEATHER_TK_API_GL_4_1) || defined(FEATHER_TK_API_GLES_2)
            gl::init(context);
#endif // FEATHER_TK_API_GL_4_1
            uiInit(context);
#endif // FEATHER_TK_UI_LIB

            p.tests.push_back(core_test::AppTest::create(context));
            p.tests.push_back(core_test::BoxPackTest::create(context));
            p.tests.push_back(core_test::BoxTest::create(context));
            p.tests.push_back(core_test::CmdLineTest::create(context));
            p.tests.push_back(core_test::ColorTest::create(context));
            p.tests.push_back(core_test::CommandTest::create(context));
            p.tests.push_back(core_test::ErrorTest::create(context));
            p.tests.push_back(core_test::FileIOTest::create(context));
            p.tests.push_back(core_test::FileTest::create(context));
            p.tests.push_back(core_test::FontSystemTest::create(context));
            p.tests.push_back(core_test::FormatTest::create(context));
            p.tests.push_back(core_test::ImageIOTest::create(context));
            p.tests.push_back(core_test::ImageTest::create(context));
            p.tests.push_back(core_test::LRUCacheTest::create(context));
            p.tests.push_back(core_test::MathTest::create(context));
            p.tests.push_back(core_test::MatrixTest::create(context));
            p.tests.push_back(core_test::MemoryTest::create(context));
            p.tests.push_back(core_test::MeshTest::create(context));
            p.tests.push_back(core_test::NoiseTest::create(context));
            p.tests.push_back(core_test::OSTest::create(context));
            p.tests.push_back(core_test::ObservableTest::create(context));
            p.tests.push_back(core_test::PNGTest::create(context));
            p.tests.push_back(core_test::RandomTest::create(context));
            p.tests.push_back(core_test::RangeTest::create(context));
            p.tests.push_back(core_test::RenderOptionsTest::create(context));
            p.tests.push_back(core_test::RenderUtilTest::create(context));
            p.tests.push_back(core_test::SizeTest::create(context));
            p.tests.push_back(core_test::StringTest::create(context));
            p.tests.push_back(core_test::SystemTest::create(context));
            p.tests.push_back(core_test::TimeTest::create(context));
            p.tests.push_back(core_test::TimerTest::create(context));
            p.tests.push_back(core_test::VectorTest::create(context));

#if defined(FEATHER_TK_UI_LIB)
#if defined(FEATHER_TK_API_GL_4_1) || defined(FEATHER_TK_API_GLES_2)
            p.tests.push_back(gl_test::MeshTest::create(context));
            p.tests.push_back(gl_test::OffscreenBufferTest::create(context));
            p.tests.push_back(gl_test::TextureAtlasTest::create(context));
            p.tests.push_back(gl_test::TextureTest::create(context));
            p.tests.push_back(gl_test::RenderTest::create(context));
            p.tests.push_back(gl_test::ShaderTest::create(context));
            p.tests.push_back(gl_test::UtilTest::create(context));
            p.tests.push_back(gl_test::WindowTest::create(context));
#endif // FEATHER_TK_API_GL_4_1

            p.tests.push_back(ui_test::ActionTest::create(context));
            /*p.tests.push_back(ui_test::BellowsTest::create(context));
            p.tests.push_back(ui_test::ButtonTest::create(context));
            p.tests.push_back(ui_test::ButtonGroupTest::create(context));
            p.tests.push_back(ui_test::ColorWidgetTest::create(context));
            p.tests.push_back(ui_test::ComboBoxTest::create(context));
            p.tests.push_back(ui_test::ConfirmDialogTest::create(context));
            p.tests.push_back(ui_test::DoubleEditTest::create(context));
            p.tests.push_back(ui_test::DoubleEditSliderTest::create(context));
            p.tests.push_back(ui_test::DoubleSliderTest::create(context));*/
            p.tests.push_back(ui_test::DoubleModelTest::create(context));
            //p.tests.push_back(ui_test::DragAndDropTest::create(context));
            //p.tests.push_back(ui_test::DrawUtilTest::create(context));
            p.tests.push_back(ui_test::EventTest::create(context));
            /*p.tests.push_back(ui_test::FileBrowserTest::create(context));
            p.tests.push_back(ui_test::FileEditTest::create(context));
            p.tests.push_back(ui_test::FloatEditTest::create(context));
            p.tests.push_back(ui_test::FloatEditSliderTest::create(context));
            p.tests.push_back(ui_test::FloatSliderTest::create(context));*/
            p.tests.push_back(ui_test::FloatModelTest::create(context));
            /*p.tests.push_back(ui_test::GridLayoutTest::create(context));
            p.tests.push_back(ui_test::GroupBoxTest::create(context));
            p.tests.push_back(ui_test::IWidgetTest::create(context));
            p.tests.push_back(ui_test::IconTest::create(context));
            p.tests.push_back(ui_test::IntEditTest::create(context));
            p.tests.push_back(ui_test::IntEditSliderTest::create(context));
            p.tests.push_back(ui_test::IntSliderTest::create(context));*/
            p.tests.push_back(ui_test::IntModelTest::create(context));
            //p.tests.push_back(ui_test::LabelTest::create(context));
            p.tests.push_back(ui_test::LayoutUtilTest::create(context));
            /*p.tests.push_back(ui_test::LineEditTest::create(context));
            p.tests.push_back(ui_test::ListWidgetTest::create(context));
            p.tests.push_back(ui_test::MDIWidgetTest::create(context));
            p.tests.push_back(ui_test::MenuBarTest::create(context));
            p.tests.push_back(ui_test::MessageDialogTest::create(context));
            p.tests.push_back(ui_test::PieChartTest::create(context));
            p.tests.push_back(ui_test::ProgressDialogTest::create(context));*/
            p.tests.push_back(ui_test::RecentFilesModelTest::create(context));
            /*p.tests.push_back(ui_test::RowLayoutTest::create(context));
            p.tests.push_back(ui_test::ScrollAreaTest::create(context));
            p.tests.push_back(ui_test::ScrollBarTest::create(context));
            p.tests.push_back(ui_test::ScrollWidgetTest::create(context));
            p.tests.push_back(ui_test::SearchBoxTest::create(context));
            p.tests.push_back(ui_test::SplitterTest::create(context));
            p.tests.push_back(ui_test::StackLayoutTest::create(context));
            p.tests.push_back(ui_test::StyleTest::create(context));
            p.tests.push_back(ui_test::TabWidgetTest::create(context));*/
            p.tests.push_back(ui_test::WidgetOptionsTest::create(context));

            //p.tests.push_back(ui_test::AppTest::create(context));
#endif // FEATHER_TK_UI_LIB
        }

        App::App() :
            _p(new Private)
        {}

        App::~App()
        {}

        std::shared_ptr<App> App::create(
            const std::shared_ptr<Context>& context,
            std::vector<std::string>& argv)
        {
            auto out = std::shared_ptr<App>(new App);
            out->_init(context, argv);
            return out;
        }
        
        void App::run()
        {
            FEATHER_TK_P();

            // Get the tests to run.
            std::vector<std::shared_ptr<test::ITest> > runTests;
            for (const auto& test : p.tests)
            {
                if (!p.testName->hasValue() ||
                    (p.testName->hasValue() &&
                        contains(test->getName(), p.testName->getValue())))
                {
                    runTests.push_back(test);
                }
            }     

            // Run the tests.
            for (const auto& test : runTests)
            {
                _context->tick();
                _print(Format("Running test: {0}").arg(test->getName()));
                test->run();
            }
                
            const auto now = std::chrono::steady_clock::now();
            const std::chrono::duration<float> diff = now - p.startTime;
            _print(Format("Seconds elapsed: {0}").arg(diff.count(), 2));
        }
    }
}

FEATHER_TK_MAIN()
{
    int r = 0;
    try
    {
        auto context = feather_tk::Context::create();
        auto args = feather_tk::convert(argc, argv);
        auto app = feather_tk::tests::App::create(context, args);
        r = app->getExit();
        if (0 == r)
        {
            app->run();
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
    }
    return r;
}

