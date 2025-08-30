set(HEADERS
    App.h
    TextWidget.h
    Window.h)

set(SOURCE
    App.cpp
    TextWidget.cpp
    Window.cpp
    main.cpp)

add_executable(textedit ${HEADERS} ${SOURCE})
target_link_libraries(textedit feather-tk-ui)
set_target_properties(textedit PROPERTIES FOLDER examples)

add_test(NAME textedit COMMAND textedit -exit -log)