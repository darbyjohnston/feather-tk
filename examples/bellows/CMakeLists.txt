add_executable(bellows bellows.cpp)
target_link_libraries(bellows ftkUi)
set_target_properties(bellows PROPERTIES FOLDER examples)

add_test(NAME bellows COMMAND bellows -exit -log)
