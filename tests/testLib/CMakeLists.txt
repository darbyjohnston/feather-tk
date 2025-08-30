set(HEADERS ITest.h)
set(PRIVATE_HEADERS)

set(SOURCE ITest.cpp)

add_library(feather-tk-testLib ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(feather-tk-testLib feather-tk-core)
set_target_properties(feather-tk-testLib PROPERTIES FOLDER tests)
set_target_properties(feather-tk-testLib PROPERTIES PUBLIC_HEADER "${HEADERS}")

