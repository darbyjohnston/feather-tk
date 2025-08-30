add_subdirectory(coreTest)
add_subdirectory(feather-tk-test)
add_subdirectory(testLib)
if(ftk_UI_LIB)
    if ("${ftk_API}" STREQUAL "GL_4_1" OR
        "${ftk_API}" STREQUAL "GL_4_1_Debug" OR
        "${ftk_API}" STREQUAL "GLES_2")
        add_subdirectory(glTest)
    endif()
    add_subdirectory(uiTest)
endif()
