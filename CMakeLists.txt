# --- Project info ---
cmake_minimum_required(VERSION 3.9)
project(universe C)
set(CMAKE_C_STANDARD 11)
# --------------------

# --- Vendored dependencies ---
# GLAD
file(GLOB GLAD_SOURCE_FILES vendor/glad/src/glad.c)
include_directories(vendor/glad/include/)
# stb_image
include_directories(vendor/stb/)
# -----------------------------

# --- Final executable ---
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
file(GLOB SOURCE_FILES src/*.c)
add_executable(universe
    ${SOURCE_FILES}
    ${GLAD_SOURCE_FILES}
)
target_link_libraries(universe ${CONAN_LIBS})
# ------------------------------