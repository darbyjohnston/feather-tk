set(HEADERS
    App.h)
set(PRIVATE_HEADERS)

set(SOURCE
    App.cpp
    main.cpp)

add_executable(feather-tk-resource ${HEADERS} ${PRIVATE_HEADERS} ${SOURCE})
target_link_libraries(feather-tk-resource)
set_target_properties(feather-tk-resource PROPERTIES FOLDER bin)

set(RUNTIME_DESTINATION "bin")
if(ftk_BUILD STREQUAL "vcpkg")
    set(RUNTIME_DESTINATION "tools/dtk")
endif()
install(TARGETS feather-tk-resource
    EXPORT feather-tk-resourceTargets
    RUNTIME DESTINATION ${RUNTIME_DESTINATION})
install(
    EXPORT feather-tk-resourceTargets
    FILE feather-tk-resourceTargets.cmake
    DESTINATION "share/feather-tk"
    NAMESPACE ftk::)
