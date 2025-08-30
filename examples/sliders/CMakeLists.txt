add_executable(sliders sliders.cpp)
target_link_libraries(sliders feather-tk-ui)
set_target_properties(sliders PROPERTIES FOLDER examples)

add_test(NAME sliders COMMAND sliders -exit -log)