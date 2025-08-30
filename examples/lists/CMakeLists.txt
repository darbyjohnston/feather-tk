add_executable(lists lists.cpp)
target_link_libraries(lists feather-tk-ui)
set_target_properties(lists PROPERTIES FOLDER examples)

add_test(NAME lists COMMAND lists -exit -log)
