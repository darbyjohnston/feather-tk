set(HEADERS
    Bindings.h
    Box.h
    Bindings.h
    CmdLine.h
    Color.h
    Context.h
    FontSystem.h
    IApp.h
    IRender.h
    ISystem.h
    Image.h
    Memory.h
    OS.h
    Observable.h
    ObservableList.h
    ObservableListInline.h
    ObservableMap.h
    ObservableMapInline.h
    ObservableValue.h
    ObservableValueInline.h
    Random.h
    Range.h
    Size.h
    String.h
    Timer.h
    Vector.h)
set(HEADERS_PRIVATE)
set(SOURCE
    Box.cpp
    Bindings.cpp
    CmdLine.cpp
    Color.cpp
    Context.cpp
    FontSystem.cpp
    IApp.cpp
    IRender.cpp
    ISystem.cpp
    Image.cpp
    Memory.cpp
    OS.cpp
    Observable.cpp
    ObservableList.cpp
    ObservableMap.cpp
    ObservableValue.cpp
    Random.cpp
    Range.cpp
    Size.cpp
    String.cpp
    Timer.cpp
    Vector.cpp)

add_library(ftk-corePy ${HEADERS} ${HEADERS_PRIVATE} ${SOURCE})
target_link_libraries(ftk-corePy ftk-core Python3::Python)
set_target_properties(ftk-corePy PROPERTIES FOLDER python/lib)
set_target_properties(ftk-corePy PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(TARGETS ftk-corePy
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/ftk/corePy)
