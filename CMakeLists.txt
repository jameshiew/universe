# --- Project info ---
cmake_minimum_required(VERSION 3.9)
project(universe)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
add_definitions(-g -Wall -DGLFW_INCLUDE_NONE=True)
# --------------------

# --- Vendored dependencies ---
# GLAD
file(GLOB GLAD_SOURCE_FILES vendor/glad/src/glad.c)
include_directories(vendor/glad/include/)

# stb_image
include_directories(vendor/stb/)

# quadtree
include_directories(vendor/quadtree/src/)

# spdlog
include_directories(vendor/spdlog/include/spdlog/)

# backward-cpp
add_subdirectory(vendor/backward-cpp/)
# -----------------------------

# --- Final executable ---
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
file(GLOB SOURCE_FILES src/*.cpp)
add_executable(universe
    ${SOURCE_FILES}
    ${GLAD_SOURCE_FILES}
    ${GRAPHENE_SOURCE_FILES}
    ${BACKWARD_ENABLE}
)
add_backward(universe)
target_link_libraries(universe ${CONAN_LIBS})
# ------------------------------