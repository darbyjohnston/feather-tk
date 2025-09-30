add_executable(popups popups.cpp)
target_link_libraries(popups ftkUI)
set_target_properties(popups PROPERTIES FOLDER examples)

add_test(NAME popups COMMAND popups -exit -log)