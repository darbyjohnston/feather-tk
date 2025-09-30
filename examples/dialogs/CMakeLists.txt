add_executable(dialogs dialogs.h dialogs.cpp)
target_link_libraries(dialogs ftkUI)
set_target_properties(dialogs PROPERTIES FOLDER examples)

add_test(NAME dialogs COMMAND dialogs -exit -log)
