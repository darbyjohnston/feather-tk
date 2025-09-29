set(HEADERS ITest.h)
set(PRIVATE_HEADERS)

set(SOURCE ITest.cpp)

add_library(ftkTestLib ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(ftkTestLib ftkCore)
set_target_properties(ftkTestLib PROPERTIES FOLDER tests)
set_target_properties(ftkTestLib PROPERTIES PUBLIC_HEADER "${HEADERS}")

