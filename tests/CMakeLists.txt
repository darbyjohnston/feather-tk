add_subdirectory(CoreTest)
add_subdirectory(ftk-test)
add_subdirectory(TestLib)
if(ftk_UI_LIB)
    if ("${ftk_API}" STREQUAL "GL_4_1" OR
        "${ftk_API}" STREQUAL "GL_4_1_Debug" OR
        "${ftk_API}" STREQUAL "GLES_2")
        add_subdirectory(GlTest)
    endif()
    add_subdirectory(UiTest)
endif()
