set(HEADERS
    ftk/glad/gl.h
    ftk/KHR/khrplatform.h)

set(SOURCE
    src/gl.c)

add_library(ftkGlad ${HEADERS} ${SOURCE})
target_link_libraries(ftkGlad OpenGL::GL ${CMAKE_DL_LIBS})
set_target_properties(ftkGlad PROPERTIES FOLDER deps)

install(
    TARGETS ftkGlad
    EXPORT ftkGladTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)
install(
    EXPORT ftkGladTargets
    FILE ftkGladTargets.cmake
    DESTINATION "share/ftk"
    NAMESPACE ftk::)
install(
    DIRECTORY
    "${CMAKE_CURRENT_SOURCE_DIR}/ftk/glad"
    DESTINATION "include/ftk")
install(
    DIRECTORY
    "${CMAKE_CURRENT_SOURCE_DIR}/ftk/KHR"
    DESTINATION "include/ftk")
