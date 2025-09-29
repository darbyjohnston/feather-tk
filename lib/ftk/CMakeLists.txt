add_subdirectory(Core)
add_subdirectory(Resource)
if(ftk_UI_LIB)
    if ("${ftk_API}" STREQUAL "GL_4_1" OR
        "${ftk_API}" STREQUAL "GL_4_1_Debug" OR
        "${ftk_API}" STREQUAL "GLES_2")
        add_subdirectory(Gl)
    endif()
    add_subdirectory(Ui)
endif()
