include(FetchContent)

# GoogleTest is downloaded at configure time, pinned to a release and checksum.
FetchContent_Declare(googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.tar.gz
    URL_HASH SHA256=7b42b4d6ed48810c5362c265a17faebe90dc2373c885e5216439d37927f02926
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    SYSTEM  # Our warning flags must not apply to GoogleTest's headers.
)
# Use the same C runtime as our code on Windows/MSVC.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(raytracer_tests
    greeting_test.cpp
)
target_link_libraries(raytracer_tests PRIVATE
    raytracer_core
    raytracer_warnings
    GTest::gtest_main
)

# Registers each TEST() with CTest, so `ctest` and IDE test explorers see them individually.
include(GoogleTest)
gtest_discover_tests(raytracer_tests)
