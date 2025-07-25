set(HEADERS
    Assert.h
    Box.h
    BoxInline.h
    BoxPack.h
    CmdLineInline.h
    CmdLine.h
    Color.h
    ColorInline.h
    Command.h
    Context.h
    ContextInline.h
    Error.h
    FileIO.h
    FileIOInline.h
    File.h
    FontSystem.h
    FontSystemInline.h
    Format.h
    FormatInline.h
    IApp.h
    IRender.h
    ISystem.h
    ISystemInline.h
    ImageIO.h
    Image.h
    ImageInline.h
    LogSystem.h
    LRUCache.h
    LRUCacheInline.h
    Math.h
    MathInline.h
    Matrix.h
    MatrixInline.h
    Memory.h
    MemoryInline.h
    Mesh.h
    MeshInline.h
    Noise.h
    OS.h
    Observable.h
    ObservableList.h
    ObservableListInline.h
    ObservableMap.h
    ObservableMapInline.h
    ObservableValue.h
    ObservableValueInline.h
    PNG.h
    Random.h
    RandomInline.h
    Range.h
    RangeInline.h
    RenderOptions.h
    RenderOptionsInline.h
    RenderUtil.h
    Size.h
    SizeInline.h
    String.h
    Time.h
    Timer.h
    Util.h
    Vector.h
    VectorInline.h)
set(HEADERS_PRIVATE
    PNGPrivate.h)
set(SOURCE
    Assert.cpp
    Box.cpp
    BoxPack.cpp
    CmdLine.cpp
    Command.cpp
    Color.cpp
    Context.cpp
    Error.cpp
    File.cpp
    FileIO.cpp
    FontSystem.cpp
    Format.cpp
    IApp.cpp
    IRender.cpp
    ISystem.cpp
    ImageIO.cpp
    Image.cpp
    LogSystem.cpp
    Math.cpp
    Matrix.cpp
    Memory.cpp
    Mesh.cpp
    Noise.cpp
    PNG.cpp
    PNGRead.cpp
    PNGWrite.cpp
    OS.cpp
    Random.cpp
    Range.cpp
    RenderOptions.cpp
    RenderUtil.cpp
    Size.cpp
    String.cpp
    Time.cpp
    Timer.cpp
    Vector.cpp)
if(WIN32)
    list(APPEND SOURCE
        ErrorWin32.cpp
        FileIOWin32.cpp
        FileWin32.cpp
        OSWin32.cpp
        TimeWin32.cpp)
else()
    list(APPEND SOURCE
        FileIOUnix.cpp
        FileUnix.cpp
        OSUnix.cpp
        TimeUnix.cpp)
endif()

set(LIBS_PUBLIC feather-tk-resource nlohmann_json::nlohmann_json)
if(CMAKE_COMPILER_IS_GNUCXX AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9)
    list(APPEND LIBS_PUBLIC stdc++fs)
endif()
set(LIBS_PRIVATE Freetype::Freetype PNG::PNG ZLIB::ZLIB)

add_library(feather-tk-core ${HEADERS} ${HEADERS_PRIVATE} ${SOURCE})
target_link_libraries(feather-tk-core PUBLIC ${LIBS_PUBLIC} PRIVATE ${LIBS_PRIVATE})
set_target_properties(feather-tk-core PROPERTIES FOLDER lib)
set_target_properties(feather-tk-core PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(
    TARGETS feather-tk-core
    EXPORT feather-tk-coreTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/feather-tk/core)
install(
    EXPORT feather-tk-coreTargets
    FILE feather-tk-coreTargets.cmake
    DESTINATION "share/feather-tk"
    NAMESPACE feather-tk::)
