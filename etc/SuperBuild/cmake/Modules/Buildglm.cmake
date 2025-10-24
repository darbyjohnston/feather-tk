include(ExternalProject)

set(glm_GIT_REPOSITORY "https://github.com/g-truc/glm.git")
set(glm_GIT_TAG "1.0.2")

set(glm_ARGS
    ${ftk_DEPS_ARGS}
    -DGLM_ENABLE_CXX_17=ON
    -DCMAKE_POSITION_INDEPENDENT_CODE=ON)

ExternalProject_Add(
    glm
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/glm
    GIT_REPOSITORY ${glm_GIT_REPOSITORY}
    GIT_TAG ${glm_GIT_TAG}
    LIST_SEPARATOR |
    CMAKE_ARGS ${glm_ARGS})
