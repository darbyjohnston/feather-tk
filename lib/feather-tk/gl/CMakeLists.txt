set(HEADERS
    GL.h
    Init.h
    Mesh.h
    OffscreenBuffer.h
    Render.h
    Shader.h
    System.h
    Texture.h
    TextureAtlas.h
    Util.h
    Window.h)
set(PRIVATE_HEADERS
    RenderPrivate.h)

set(SOURCE
    Init.cpp
    Mesh.cpp
    Mesh.cpp
    OffscreenBuffer.cpp
    Render.cpp
    RenderPrims.cpp
    Shader.cpp
    System.cpp
    Texture.cpp
    TextureAtlas.cpp
    Util.cpp
    Window.cpp)
if ("${ftk_API}" STREQUAL "GL_4_1" OR
    "${ftk_API}" STREQUAL "GL_4_1_Debug")
    list(APPEND SOURCE RenderShaders_GL_4_1.cpp)
elseif ("${ftk_API}" STREQUAL "GLES_2")
    list(APPEND SOURCE RenderShaders_GLES_2.cpp)
endif()

add_library(ftk-gl ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(ftk-gl ftk-core ftk-glad SDL2::SDL2-static)
set_target_properties(ftk-gl PROPERTIES FOLDER lib)
set_target_properties(ftk-gl PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(
    TARGETS ftk-gl
    EXPORT ftk-glTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/feather-tk/gl)
install(
    EXPORT ftk-glTargets
    FILE ftk-glTargets.cmake
    DESTINATION "share/feather-tk"
    NAMESPACE ftk::)
