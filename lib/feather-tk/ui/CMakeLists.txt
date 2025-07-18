set(HEADERS
    Action.h
    App.h
    Bellows.h
    ButtonGroup.h
    CheckBox.h
    ColorPopup.h
    ColorSwatch.h
    ColorWidget.h
    ComboBox.h
    ConfirmDialog.h
    DialogSystem.h
    Divider.h
    DockLayout.h
    DoubleEdit.h
    DoubleEditSlider.h
    DoubleModel.h
    DoubleSlider.h
    DrawUtil.h
    DrivesModel.h
    Event.h
    FileBrowser.h
    FileEdit.h
    FloatEdit.h
    FloatEditSlider.h
    FloatModel.h
    FloatSlider.h
    FormLayout.h
    GridLayout.h
    GroupBox.h
    IButton.h
    IClipboard.h
    IDialog.h
    IMenuPopup.h
    IPopup.h
    IWidget.h
    IWidgetInline.h
    IWidgetPopup.h
    IWindow.h
    ImageWidget.h
    IncButtons.h
    IntEdit.h
    IntEditSlider.h
    IntModel.h
    IntSlider.h
    Icon.h
    IconSystem.h
    Init.h
    Label.h
    LayoutUtil.h
    LineEdit.h
    ListItemsWidget.h
    ListWidget.h
    MainWindow.h
    MDICanvas.h
    MDIWidget.h
    Menu.h
    MenuBar.h
    MessageDialog.h
    PieChart.h
    ProgressDialog.h
    PushButton.h
    RadioButton.h
    RecentFilesModel.h
    RowLayout.h
    ScrollArea.h
    ScrollBar.h
    ScrollWidget.h
    SearchBox.h
    Settings.h
    SettingsInline.h
    Spacer.h
    Splitter.h
    StackLayout.h
    Style.h
    SvgWidget.h
    TabBar.h
    TabWidget.h
    ToolBar.h
    ToolButton.h
    Tooltip.h
    WidgetOptions.h
    Window.h)
set(PRIVATE_HEADERS
    BellowsPrivate.h
    ComboBoxPrivate.h
    FileBrowserPrivate.h
    ListItemsWidgetPrivate.h
    MenuBarPrivate.h
    MenuPrivate.h
    TabBarPrivate.h)

set(SOURCE
    Action.cpp
    Bellows.cpp
    BellowsButton.cpp
    ButtonGroup.cpp
    CheckBox.cpp
    ColorPopup.cpp
    ColorSwatch.cpp
    ColorWidget.cpp
    ComboBox.cpp
    ComboBoxButton.cpp
    ComboBoxMenu.cpp
    ConfirmDialog.cpp
    DialogSystem.cpp
    Divider.cpp
    DockLayout.cpp
    DoubleEdit.cpp
    DoubleEditSlider.cpp
    DoubleModel.cpp
    DoubleSlider.cpp
    DrawUtil.cpp
    DrivesModel.cpp
    Event.cpp
    FileBrowser.cpp
    FileBrowserModel.cpp
    FileBrowserPanel.cpp
    FileBrowserPath.cpp
    FileBrowserSystem.cpp
    FileBrowserView.cpp
    FileBrowserWidget.cpp
    FileEdit.cpp
    FloatEdit.cpp
    FloatEditSlider.cpp
    FloatModel.cpp
    FloatSlider.cpp
    FormLayout.cpp
    GridLayout.cpp
    GroupBox.cpp
    IButton.cpp
    IClipboard.cpp
    IDialog.cpp
    IMenuPopup.cpp
    IPopup.cpp
    IWidget.cpp
    IWidgetPopup.cpp
    IWindow.cpp
    ImageWidget.cpp
    IncButtons.cpp
    IntEdit.cpp
    IntEditSlider.cpp
    IntModel.cpp
    IntSlider.cpp
    Icon.cpp
    IconSystem.cpp
    Init.cpp
    Label.cpp
    LayoutUtil.cpp
    LineEdit.cpp
    ListItemsButton.cpp
    ListItemsWidget.cpp
    ListWidget.cpp
    MDICanvas.cpp
    MDIWidget.cpp
    MainWindow.cpp
    Menu.cpp
    MenuBar.cpp
    MenuBarButton.cpp
    MenuButton.cpp
    MessageDialog.cpp
    PieChart.cpp
    ProgressDialog.cpp
    PushButton.cpp
    RadioButton.cpp
    RecentFilesModel.cpp
    RowLayout.cpp
    ScrollArea.cpp
    ScrollBar.cpp
    ScrollWidget.cpp
    SearchBox.cpp
    Settings.cpp
    Spacer.cpp
    Splitter.cpp
    StackLayout.cpp
    Style.cpp
    SvgWidget.cpp
    TabBar.cpp
    TabBarButton.cpp
    TabWidget.cpp
    ToolBar.cpp
    ToolButton.cpp
    Tooltip.cpp
    WidgetOptions.cpp)
if ("${feather_tk_API}" STREQUAL "GL_4_1" OR
    "${feather_tk_API}" STREQUAL "GL_4_1_Debug" OR
    "${feather_tk_API}" STREQUAL "GLES_2")
    list(APPEND SOURCE
        AppGL.cpp
        WindowGL.cpp)
endif()

set(LIBRARIES)
if ("${feather_tk_API}" STREQUAL "GL_4_1" OR
    "${feather_tk_API}" STREQUAL "GL_4_1_Debug" OR
    "${feather_tk_API}" STREQUAL "GLES_2")
    list(APPEND LIBRARIES feather-tk-gl)
endif()
list(APPEND LIBRARIES feather-tk-core)
set(LIBRARIES_PRIVATE lunasvg::lunasvg)
if(feather_tk_nfd)
    list(APPEND LIBRARIES_PRIVATE nfd::nfd)
endif()

add_library(feather-tk-ui ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(feather-tk-ui PUBLIC ${LIBRARIES} PRIVATE ${LIBRARIES_PRIVATE})
set_target_properties(feather-tk-ui PROPERTIES FOLDER lib)
set_target_properties(feather-tk-ui PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(
    TARGETS feather-tk-ui
    EXPORT feather-tk-uiTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/feather-tk/ui)
install(
    EXPORT feather-tk-uiTargets
    FILE feather-tk-uiTargets.cmake
    DESTINATION "share/feather-tk"
    NAMESPACE feather-tk::)
