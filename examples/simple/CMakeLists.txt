add_executable(simple simple.cpp)
target_link_libraries(simple feather-tk-ui)
set_target_properties(simple PROPERTIES FOLDER examples)

add_test(NAME simple COMMAND simple -exit -log)