add_executable(windows windows.cpp)
target_link_libraries(windows ftkUi)
set_target_properties(windows PROPERTIES FOLDER examples)

add_test(NAME windows COMMAND windows -exit -log)
