set(HEADERS
    feather-tk/glad/gl.h
    feather-tk/KHR/khrplatform.h)

set(SOURCE
    src/gl.c)

add_library(feather-tk-glad ${HEADERS} ${SOURCE})
target_link_libraries(feather-tk-glad OpenGL::GL ${CMAKE_DL_LIBS})
set_target_properties(feather-tk-glad PROPERTIES FOLDER deps)

install(
    TARGETS feather-tk-glad
    EXPORT feather-tk-gladTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)
install(
    EXPORT feather-tk-gladTargets
    FILE feather-tk-gladTargets.cmake
    DESTINATION "share/feather-tk"
    NAMESPACE ftk::)
install(
    DIRECTORY
    "${CMAKE_CURRENT_SOURCE_DIR}/feather-tk/glad"
    DESTINATION "include/feather-tk")
install(
    DIRECTORY
    "${CMAKE_CURRENT_SOURCE_DIR}/feather-tk/KHR"
    DESTINATION "include/feather-tk")
