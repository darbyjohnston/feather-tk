add_executable(mdi mdi.cpp)
target_link_libraries(mdi feather-tk-ui)
set_target_properties(mdi PROPERTIES FOLDER examples)

add_test(NAME mdi COMMAND mdi -exit -log)