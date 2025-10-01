set(HEADERS
    App.h
    Document.h
    DocumentModel.h
    MainWindow.h
    MenuBar.h
    StatusBar.h)

set(SOURCE
    App.cpp
    Document.cpp
    DocumentModel.cpp
    MainWindow.cpp
    MenuBar.cpp
    StatusBar.cpp
    main.cpp)

add_executable(textedit ${HEADERS} ${SOURCE})
target_link_libraries(textedit ftkUI)
set_target_properties(textedit PROPERTIES FOLDER examples)

add_test(NAME textedit COMMAND textedit -exit -log)