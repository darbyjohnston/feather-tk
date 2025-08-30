add_subdirectory(core)
add_subdirectory(resource)
if(ftk_UI_LIB)
    if ("${ftk_API}" STREQUAL "GL_4_1" OR
        "${ftk_API}" STREQUAL "GL_4_1_Debug" OR
        "${ftk_API}" STREQUAL "GLES_2")
        add_subdirectory(gl)
    endif()
    add_subdirectory(ui)
endif()
