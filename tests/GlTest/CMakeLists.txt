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

add_library(ftkGlTest ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(ftkGlTest ftkGl ftkTestLib)
set_target_properties(ftkGlTest PROPERTIES FOLDER tests)
set_target_properties(ftkGlTest PROPERTIES PUBLIC_HEADER "${HEADERS}")

