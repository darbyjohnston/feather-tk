set(HEADERS ITest.h)
set(PRIVATE_HEADERS)

set(SOURCE ITest.cpp)

add_library(ftk-testLib ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(ftk-testLib ftk-core)
set_target_properties(ftk-testLib PROPERTIES FOLDER tests)
set_target_properties(ftk-testLib PROPERTIES PUBLIC_HEADER "${HEADERS}")

