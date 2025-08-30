add_executable(popups popups.cpp)
target_link_libraries(popups feather-tk-ui)
set_target_properties(popups PROPERTIES FOLDER examples)

add_test(NAME popups COMMAND popups -exit -log)