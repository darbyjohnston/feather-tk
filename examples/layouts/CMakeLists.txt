add_executable(layouts layouts.cpp)
target_link_libraries(layouts ftkUI)
set_target_properties(layouts PROPERTIES FOLDER examples)

add_test(NAME layouts COMMAND layouts -exit -log)
