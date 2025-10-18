set(HEADERS
    Actions.h
    App.h
    Document.h
    DocumentModel.h
    DocumentTabs.h
    MainWindow.h
    MenuBar.h
    SettingsModel.h
    SettingsWidget.h
    StatusBar.h
    ToolBar.h)

set(SOURCE
    Actions.cpp
    App.cpp
    Document.cpp
    DocumentModel.cpp
    DocumentTabs.cpp
    MainWindow.cpp
    MenuBar.cpp
    SettingsModel.cpp
    SettingsWidget.cpp
    StatusBar.cpp
    ToolBar.cpp
    main.cpp)

add_executable(imageview ${HEADERS} ${SOURCE})
target_link_libraries(imageview ftkUI)
set_target_properties(imageview PROPERTIES FOLDER examples)

add_test(NAME imageview COMMAND imageview -exit -log)