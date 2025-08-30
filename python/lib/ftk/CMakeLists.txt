pybind11_add_module(ftk Bindings.cpp)
target_link_libraries(ftk PRIVATE ftk-uiPy ftk-corePy)
set_target_properties(ftk PROPERTIES FOLDER python/lib)
set_target_properties(ftk PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(TARGETS ftk
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)
