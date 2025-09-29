set(HEADERS
    feather-tk/glad/gl.h
    feather-tk/KHR/khrplatform.h)

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
