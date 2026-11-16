cmake_minimum_required(VERSION 3.25)

project(raytracer
    VERSION 0.1.0
    DESCRIPTION "HETIC ray tracer"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# Lets clangd (Zed, VS Code clangd extension) understand the project.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(RAYTRACER_BUILD_TESTS "Build the unit tests" ON)
option(RAYTRACER_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF)

# Shared warning flags, linked into every target we own (not third-party code).
add_library(raytracer_warnings INTERFACE)
if(MSVC)
    target_compile_options(raytracer_warnings INTERFACE
        /W4 /permissive-
        $<$<BOOL:${RAYTRACER_WARNINGS_AS_ERRORS}>:/WX>
    )
else()
    target_compile_options(raytracer_warnings INTERFACE
        -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion
        $<$<BOOL:${RAYTRACER_WARNINGS_AS_ERRORS}>:-Werror>
    )
endif()

add_subdirectory(src)

if(RAYTRACER_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
