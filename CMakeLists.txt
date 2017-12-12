cmake_minimum_required(VERSION 3.9)
project(universe C)

set(CMAKE_C_STANDARD 11)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

file(GLOB SOURCE_FILES src/*.c)
add_executable(universe
    ${SOURCE_FILES}
    vendor/glad/src/glad.c
    vendor/sds/sds.c)

include_directories(
    vendor/glad/include/
    vendor/sds/
)

target_link_libraries(universe ${CONAN_LIBS})