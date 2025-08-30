set(HEADERS
    Buttons.h
    ColorWidgets.h
    DemoWindow.h
    Editors.h
    Icons.h
    ImageWidgets.h
    Layouts.h
    Popups.h
    Sliders.h)

set(SOURCE
    Buttons.cpp
    ColorWidgets.cpp
    DemoWindow.cpp
    Editors.cpp
    Icons.cpp
    ImageWidgets.cpp
    Layouts.cpp
    Popups.cpp
    Sliders.cpp
    main.cpp)

add_executable(demo ${HEADERS} ${SOURCE})
target_link_libraries(demo ftk-ui)
set_target_properties(demo PROPERTIES FOLDER examples)

add_test(NAME demo COMMAND demo -exit -log)
