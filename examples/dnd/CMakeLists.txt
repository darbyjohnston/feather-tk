add_executable(dnd dnd.h dnd.cpp)
target_link_libraries(dnd ftkUi)
set_target_properties(dnd PROPERTIES FOLDER examples)

add_test(NAME dnd COMMAND dnd -exit -log)