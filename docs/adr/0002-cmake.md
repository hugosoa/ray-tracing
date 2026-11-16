# 2. Use CMake and CTest to build and test

## Status

Accepted

## Context

The project needs a way to describe how the code is compiled (targets, C++20 standard, warning flags, dependencies) and a way to run the unit tests.

Alternatives considered:

- **Hand-written Makefiles:** simple at first, but tied to one toolchain and not usable as-is with MSVC.
- **Other build systems** such as Meson or Bazel: capable, but less common in C++ projects and tools.
- **CMake**, with CTest (shipped with CMake) as the test runner.

## Decision

We will use CMake (≥ 3.25) with the Ninja generator because it is the de facto standard build system for C++.

The build is split into a library (`raytracer_core`), a thin executable (`raytracer`) and a test executable (`raytracer_tests`). Named configurations (`debug`, `release`, `ci`) live in `CMakePresets.json`. Tests are run with CTest (`ctest --preset <name>`).

## Consequences

- Most documentation, examples and libraries assume CMake, and editors understand it (VS Code CMake Tools, clangd through `compile_commands.json`).
- CTest comes with CMake, so the test runner needs no extra install.
- CMake's language is verbose and has many old and new ways of doing the same thing, which makes it hard to learn for people new to C++.
- Adding a source file means also adding it to the right `CMakeLists.txt`. Forgetting this is a common mistake.
- CMake 3.25 or later is required, which older systems may not provide by default.
