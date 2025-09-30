add_executable(buttons buttons.cpp)
target_link_libraries(buttons ftkUI)
set_target_properties(buttons PROPERTIES FOLDER examples)

add_test(NAME buttons COMMAND buttons -exit -log)
