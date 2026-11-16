# All the ray tracer logic lives in this library, so the tests can link against it.
add_library(raytracer_core
    greeting.cpp
)
target_include_directories(raytracer_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(raytracer_core PRIVATE raytracer_warnings)

# The executable stays a thin entry point on top of the library.
add_executable(raytracer
    main.cpp
)
target_link_libraries(raytracer PRIVATE raytracer_core raytracer_warnings)
