cmake_minimum_required(VERSION 3.20)
project(raytracer VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# LodePNG: PNG encoding/decoding. It has no release tags, so it is pinned to a commit.
# It ships no CMakeLists.txt, so we build its single source file ourselves.
FetchContent_Declare(
  lodepng
  GIT_REPOSITORY https://github.com/lvandeve/lodepng.git
  GIT_TAG        7b2893e35891c0c85bee5595caafaf3c2044b409
)
FetchContent_MakeAvailable(lodepng)

add_library(lodepng STATIC ${lodepng_SOURCE_DIR}/lodepng.cpp)
target_include_directories(lodepng PUBLIC ${lodepng_SOURCE_DIR})

# Main executable
add_executable(raytracer
  src/main.cpp
  src/math/vector.cpp
  src/ray/ray.cpp
  src/geometry/sphere.cpp
  src/camera/camera.cpp
  src/colour/colour.cpp
  src/image/image.cpp
  src/io/png_saver.cpp
  src/material/flat_shader.cpp
  src/material/lambert_shader.cpp
  src/light/light.cpp
)
# Lets the code write #include "math/vector.hpp"
target_include_directories(raytracer PRIVATE src)
target_link_libraries(raytracer PRIVATE lodepng)

# Testing
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.7.1
)
FetchContent_MakeAvailable(Catch2)

enable_testing()

add_executable(tests
  tests/test_main.cpp
  tests/math/vector_test.cpp
  tests/ray/ray_test.cpp
  tests/geometry/sphere_test.cpp
  tests/colour/colour_test.cpp
  tests/camera/camera_test.cpp
  tests/image/image_test.cpp
  tests/io/png_saver_test.cpp
  tests/material/flat_shader_test.cpp
  tests/material/lambert_shader_test.cpp
  tests/light/light_test.cpp
  src/math/vector.cpp
  src/ray/ray.cpp
  src/geometry/sphere.cpp
  src/camera/camera.cpp
  src/colour/colour.cpp
  src/image/image.cpp
  src/io/png_saver.cpp
  src/material/flat_shader.cpp
  src/material/lambert_shader.cpp
  src/light/light.cpp
)
# Lets the tests write #include "math/vector.hpp"
target_include_directories(tests PRIVATE src)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain lodepng)

include(CTest)
include(Catch)
catch_discover_tests(tests)
