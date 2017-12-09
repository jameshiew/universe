cmake_minimum_required(VERSION 3.9)
project(universe C)

set(CMAKE_C_STANDARD 11)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(universe
    vendor/glad/src/glad.c
    vendor/sds/sds.c
    src/main.c src/input.h src/input.c src/shaders.c src/shaders.h src/shaders.c src/shaders.h src/render.c src/render.h)

include_directories(
    vendor/glad/include/
    vendor/sds/
)

target_link_libraries(universe ${CONAN_LIBS})