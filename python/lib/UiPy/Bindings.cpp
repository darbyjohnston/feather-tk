// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <UiPy/Bindings.h>

#include <UiPy/App.h>
#include <UiPy/Bellows.h>
#include <UiPy/ButtonGroup.h>
#include <UiPy/CheckBox.h>
#include <UiPy/ColorPopup.h>
#include <UiPy/ColorSwatch.h>
#include <UiPy/ColorWidget.h>
#include <UiPy/ConfirmDialog.h>
#include <UiPy/DialogSystem.h>
#include <UiPy/DoubleEdit.h>
#include <UiPy/DoubleEditSlider.h>
#include <UiPy/DoubleModel.h>
#include <UiPy/DoubleSlider.h>
#include <UiPy/Event.h>
#include <UiPy/FileBrowser.h>
#include <UiPy/FileEdit.h>
#include <UiPy/FloatEdit.h>
#include <UiPy/FloatEditSlider.h>
#include <UiPy/FloatModel.h>
#include <UiPy/FloatSlider.h>
#include <UiPy/GridLayout.h>
#include <UiPy/GroupBox.h>
#include <UiPy/IButton.h>
#include <UiPy/IDialog.h>
#include <UiPy/IMenuPopup.h>
#include <UiPy/IPopup.h>
#include <UiPy/IWidget.h>
#include <UiPy/IWidgetPopup.h>
#include <UiPy/IWindow.h>
#include <UiPy/Icon.h>
#include <UiPy/IconSystem.h>
#include <UiPy/IntEdit.h>
#include <UiPy/IntEditSlider.h>
#include <UiPy/IntModel.h>
#include <UiPy/IntSlider.h>
#include <UiPy/Label.h>
#include <UiPy/MDICanvas.h>
#include <UiPy/MDIWidget.h>
#include <UiPy/MainWindow.h>
#include <UiPy/Menu.h>
#include <UiPy/MenuBar.h>
#include <UiPy/MessageDialog.h>
#include <UiPy/ProgressDialog.h>
#include <UiPy/PushButton.h>
#include <UiPy/RadioButton.h>
#include <UiPy/RecentFilesModel.h>
#include <UiPy/RowLayout.h>
#include <UiPy/ScrollArea.h>
#include <UiPy/ScrollWidget.h>
#include <UiPy/Settings.h>
#include <UiPy/Style.h>
#include <UiPy/TabBar.h>
#include <UiPy/TabWidget.h>
#include <UiPy/ToolButton.h>
#include <UiPy/WidgetOptions.h>
#include <UiPy/Window.h>

#include <ftk/Ui/Init.h>

#include <ftk/Core/Context.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace ftk
{
    void uiBind(py::module_& m)
    {
        m.def(
            "uiInit",
            &uiInit,
            py::arg("context"),
            "Initialize the library.");

        style(m);
        event(m);
        widgetOptions(m);
        iWidget(m);
        iWindow(m);
        iPopup(m);
        iDialog(m);
        iMenuPopup(m);
        iWidgetPopup(m);
        iButton(m);
        settings(m);
        window(m);

        app(m);
        bellows(m);
        buttonGroup(m);
        checkBox(m);
        colorPopup(m);
        colorSwatch(m);
        colorWidget(m);
        confirmDialog(m);
        dialogSystem(m);
        doubleEdit(m);
        doubleEditSlider(m);
        doubleModel(m);
        doubleSlider(m);
        fileBrowser(m);
        fileEdit(m);
        floatEdit(m);
        floatEditSlider(m);
        floatModel(m);
        floatSlider(m);
        gridLayout(m);
        groupBox(m);
        icon(m);
        iconSystem(m);
        intEdit(m);
        intEditSlider(m);
        intModel(m);
        intSlider(m);
        label(m);
        mainWindow(m);
        mdiCanvas(m);
        mdiWidget(m);
        menu(m);
        menuBar(m);
        messageDialog(m);
        progressDialog(m);
        pushButton(m);
        radioButton(m);
        recentFilesModel(m);
        rowLayout(m);
        scrollArea(m);
        scrollWidget(m);
        tabBar(m);
        tabWidget(m);
        toolButton(m);
    }
}
