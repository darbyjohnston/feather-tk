set(HEADERS
    ftk/glad/gl.h
    ftk/KHR/khrplatform.h)

set(SOURCE
    src/gl.c)

add_library(glad ${HEADERS} ${SOURCE})
target_link_libraries(glad OpenGL::GL ${CMAKE_DL_LIBS})
set_target_properties(glad PROPERTIES FOLDER deps)

install(
    TARGETS glad
    EXPORT gladTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)
install(
    EXPORT gladTargets
    FILE gladTargets.cmake
    DESTINATION "share/ftk"
    NAMESPACE feather_tk::)
install(
    DIRECTORY
    "${CMAKE_CURRENT_SOURCE_DIR}/ftk/glad"
    DESTINATION "include/ftk")
install(
    DIRECTORY
    "${CMAKE_CURRENT_SOURCE_DIR}/ftk/KHR"
    DESTINATION "include/ftk")
