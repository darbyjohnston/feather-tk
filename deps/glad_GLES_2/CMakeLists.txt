set(HEADERS
    feather-tk/glad/glad.h
    feather-tk/KHR/khrplatform.h)

set(SOURCE
    src/glad.c)

add_library(ftk-glad ${HEADERS} ${SOURCE})
target_link_libraries(ftk-glad OpenGL::GL ${CMAKE_DL_LIBS})
set_target_properties(ftk-glad PROPERTIES FOLDER deps)

install(
    TARGETS ftk-glad
    EXPORT ftk-gladTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)
install(
    EXPORT ftk-gladTargets
    FILE ftk-gladTargets.cmake
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
