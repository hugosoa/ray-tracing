cmake_minimum_required(VERSION 3.20)
project(raytracer VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Main executable
add_executable(raytracer
  src/main.cpp
  src/math/vector.cpp
  src/ray/ray.cpp
  src/geometry/sphere.cpp
)
# Lets the code write #include "math/vector.hpp"
target_include_directories(raytracer PRIVATE src)

# Testing
include(FetchContent)
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
  src/math/vector.cpp
  src/ray/ray.cpp
  src/geometry/sphere.cpp
)
# Lets the tests write #include "math/vector.hpp"
target_include_directories(tests PRIVATE src)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(tests)
