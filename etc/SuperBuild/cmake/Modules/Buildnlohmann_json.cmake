include(ExternalProject)

set(nlohmann_json_GIT_REPOSITORY "https://github.com/nlohmann/json.git")
set(nlohmann_json_GIT_TAG "v3.11.3")

set(nlohmann_json_ARGS ${feather_tk_DEPS_ARGS})
list(APPEND nlohmann_json_ARGS -DJSON_BuildTests=OFF)

ExternalProject_Add(
	nlohmann_json
	PREFIX ${CMAKE_CURRENT_BINARY_DIR}/nlohmann_json
	GIT_REPOSITORY ${nlohmann_json_GIT_REPOSITORY}
    GIT_TAG ${nlohmann_json_GIT_TAG}
    LIST_SEPARATOR |
	CMAKE_ARGS ${nlohmann_json_ARGS})
