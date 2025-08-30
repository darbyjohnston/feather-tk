set(HEADERS feather-tk-test.h)

set(SOURCE feather-tk-test.cpp)

set(LIBRARIES feather-tk-coreTest)
if(ftk_UI_LIB)
    if ("${ftk_API}" STREQUAL "GL_4_1" OR
        "${ftk_API}" STREQUAL "GL_4_1_Debug" OR
        "${ftk_API}" STREQUAL "GLES_2")
        list(APPEND LIBRARIES feather-tk-glTest)
    endif()
    list(APPEND LIBRARIES feather-tk-uiTest)
endif()

add_executable(feather-tk-test ${SOURCE} ${HEADERS})
target_link_libraries(feather-tk-test ${LIBRARIES})
set_target_properties(feather-tk-test PROPERTIES FOLDER tests)

add_test(
    NAME feather-tk-test
    COMMAND feather-tk-test -log)
