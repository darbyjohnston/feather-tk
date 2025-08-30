set(HEADERS
    MeshTest.h
    OffscreenBufferTest.h
    RenderTest.h
    ShaderTest.h
    TextureAtlasTest.h
    TextureTest.h
    UtilTest.h
    WindowTest.h)
set(PRIVATE_HEADERS)

set(SOURCE
    MeshTest.cpp
    OffscreenBufferTest.cpp
    RenderTest.cpp
    ShaderTest.cpp
    TextureAtlasTest.cpp
    TextureTest.cpp
    UtilTest.cpp
    WindowTest.cpp)

add_library(feather-tk-glTest ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(feather-tk-glTest feather-tk-gl feather-tk-testLib)
set_target_properties(feather-tk-glTest PROPERTIES FOLDER tests)
set_target_properties(feather-tk-glTest PROPERTIES PUBLIC_HEADER "${HEADERS}")

