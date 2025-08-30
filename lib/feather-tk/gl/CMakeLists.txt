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

add_library(feather-tk-gl ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(feather-tk-gl feather-tk-core feather-tk-glad SDL2::SDL2-static)
set_target_properties(feather-tk-gl PROPERTIES FOLDER lib)
set_target_properties(feather-tk-gl PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(
    TARGETS feather-tk-gl
    EXPORT feather-tk-glTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/feather-tk/gl)
install(
    EXPORT feather-tk-glTargets
    FILE feather-tk-glTargets.cmake
    DESTINATION "share/feather-tk"
    NAMESPACE ftk::)
