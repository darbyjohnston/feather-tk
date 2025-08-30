add_executable(offscreen offscreen.h offscreen.cpp)
target_link_libraries(offscreen feather-tk-ui)
set_target_properties(offscreen PROPERTIES FOLDER examples)

add_test(NAME offscreen COMMAND offscreen -exit -log)
