add_executable(splitters splitters.cpp)
target_link_libraries(splitters ftk-ui)
set_target_properties(splitters PROPERTIES FOLDER examples)

add_test(NAME splitters COMMAND splitters -exit -log)
