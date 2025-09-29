add_executable(mdi mdi.cpp)
target_link_libraries(mdi ftkUi)
set_target_properties(mdi PROPERTIES FOLDER examples)

add_test(NAME mdi COMMAND mdi -exit -log)