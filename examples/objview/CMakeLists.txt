set(HEADERS
    Actions.h
    App.h
    Document.h
    DocumentModel.h
    DocumentTabs.h
    HUDWidget.h
    MainWindow.h
    MenuBar.h
    ObjIO.h
    ObjView.h
    Settings.h
    SettingsModel.h
    SettingsWidget.h
    ToolBar.h)

set(SOURCE
    Actions.cpp
    App.cpp
    Document.cpp
    DocumentModel.cpp
    DocumentTabs.cpp
    HUDWidget.cpp
    MainWindow.cpp
    MenuBar.cpp
    ObjIO.cpp
    ObjView.cpp
    Settings.cpp
    SettingsModel.cpp
    SettingsWidget.cpp
    ToolBar.cpp
    main.cpp)

add_executable(objview ${HEADERS} ${SOURCE})
target_link_libraries(objview ftkUI)
set_target_properties(objview PROPERTIES FOLDER examples)

add_test(NAME objview COMMAND objview -exit -log)