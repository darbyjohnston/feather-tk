pybind11_add_module(featherTkPy Bindings.cpp)
target_link_libraries(featherTkPy PRIVATE feather-tk-uiPy feather-tk-corePy)
set_target_properties(featherTkPy PROPERTIES FOLDER python/lib)
set_target_properties(featherTkPy PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(TARGETS featherTkPy
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)
