add_executable(stack stack.cpp)
target_link_libraries(stack ftk-ui)
set_target_properties(stack PROPERTIES FOLDER examples)

add_test(NAME stack COMMAND stack -exit -log)
