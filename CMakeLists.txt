cmake_minimum_required(VERSION 3.9)
project(universe C)

set(CMAKE_C_STANDARD 11)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(universe
    vendor/glad/src/glad.c
    src/main.c
)

include_directories(
    vendor/glad/include/
)

target_link_libraries(universe ${CONAN_LIBS})