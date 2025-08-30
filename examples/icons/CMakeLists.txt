add_executable(icons icons.cpp)
target_link_libraries(icons feather-tk-ui)
set_target_properties(icons PROPERTIES FOLDER examples)

add_test(NAME icons COMMAND icons -exit -log)
