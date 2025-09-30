add_executable(tabs tabs.cpp)
target_link_libraries(tabs ftkUI)
set_target_properties(tabs PROPERTIES FOLDER examples)

add_test(NAME tabs COMMAND tabs -exit -log)
