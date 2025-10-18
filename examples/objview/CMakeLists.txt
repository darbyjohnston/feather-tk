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

add_executable(objview ${HEADERS} ${SOURCE})
target_link_libraries(objview ftkUI)
set_target_properties(objview PROPERTIES FOLDER examples)

add_test(NAME objview COMMAND objview -exit -log)