# ray-tracing

Ray tracer HETIC project, written in C++20.

For now the project only contains a "Hello World" demo, a unit-test setup and a portable build. The goal is that every team member can build and test the code the same way, whatever their OS.

## Project layout

```
.
├── CMakeLists.txt        # Root build file (C++ standard, warnings, options)
├── CMakePresets.json     # Named build configurations: debug, release, ci
├── src/
│   ├── greeting.hpp/.cpp # Library code (raytracer_core): all the real logic goes here
│   └── main.cpp          # Executable entry point (raytracer): kept as thin as possible
├── tests/
│   └── greeting_test.cpp # GoogleTest unit tests for raytracer_core
├── .devcontainer/        # Reproducible Linux toolchain (Docker)
├── .clang-format         # Code style
└── docs/                 # Project documents (discovery report...)
```

The code is split into a **library** (`raytracer_core`) and a thin **executable** (`raytracer`). The tests link against the library, so anything we write in the library can be tested without running the program.

## Toolchain

| Tool | Role |
|---|---|
| [CMake](https://cmake.org/) ≥ 3.25 | Describes the build in a compiler-independent way |
| [Ninja](https://ninja-build.org/) | Runs the build (fast, same on every OS) |
| A C++20 compiler | GCC, Clang or MSVC |
| [GoogleTest](https://github.com/google/googletest) 1.15.2 | Unit-test framework (BSD-3 licence), downloaded automatically by CMake |

## Getting started

There are two ways to build. The **dev container is the recommended one**: everyone gets exactly the same compiler and tools.

### Option A: dev container (recommended, any OS)

Prerequisites: [Docker Desktop](https://www.docker.com/products/docker-desktop/) (on Windows, with the WSL 2 backend) running.

**VS Code**

1. Install the [Dev Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) extension.
2. Open the repository folder, then run **Dev Containers: Reopen in Container** from the command palette.
3. The first time, the image is built (a few minutes) and the project is configured automatically.
4. Use the CMake Tools status bar to build, run and test, or use the terminal commands below.

**Zed**

Open the repository with Zed's dev container support, or use the editor-independent CLI below and keep editing locally. Zed uses `clangd`, which finds the compile commands through the `.clangd` file once `build/debug` has been configured.

**Any editor, from the terminal** ([Dev Container CLI](https://github.com/devcontainers/cli), `npm install -g @devcontainers/cli`):

```sh
devcontainer up --workspace-folder .
devcontainer exec --workspace-folder . bash   # shell inside the container
```

Then run the commands from [Build and run](#build-and-run) inside that shell.

### Option B: native toolchain

Install CMake ≥ 3.25, Ninja and a C++20 compiler:

- **macOS:** `xcode-select --install` then `brew install cmake ninja`
- **Ubuntu/Debian:** `sudo apt install build-essential cmake ninja-build`
- **Windows:** install Visual Studio 2022 with the "Desktop development with C++" workload (it includes CMake and Ninja), then run the commands from a **Developer PowerShell for VS 2022**.

## Build and run

All commands are run from the repository root.

### Shortcuts

Short commands, like `npm run ...` in JavaScript projects. They only call the CMake commands below (see [ADR 4](docs/adr/0004-makefile-shortcuts.md)).

```sh
make build                 # configure (first time only) and compile
make start                 # build, then run the ray tracer
make start ARGS="Alice"    # same, with arguments
make test                  # build, then run the unit tests
make clean                 # delete the build folder
```

They use the `debug` preset by default. Pick another one with `PRESET`, for example `make test PRESET=release`.

`make` is included in the dev container. Without it (native Windows), use the CMake commands below. Alternatively, `cmake --workflow --preset debug` configures, builds and tests in one command.

### CMake commands

```sh
cmake --preset debug          # configure (only needed once, or after editing CMakeLists.txt)
cmake --build --preset debug  # compile
./build/debug/src/raytracer   # run
```

Expected output:

```
$ ./build/debug/src/raytracer
Hello, World!
$ ./build/debug/src/raytracer Alice
Hello, Alice!
```

On Windows the executable is `build\debug\src\raytracer.exe`.

Available presets:

| Preset | Use |
|---|---|
| `debug` | Day-to-day development: no optimisation, debug symbols |
| `release` | Optimised build, for measuring render times |
| `ci` | Release + warnings treated as errors, to check code before merging |

Each preset builds into its own folder (`build/<preset>`), so they never overwrite each other. To start from scratch, delete the `build/` folder.

## Testing and TDD

We use [GoogleTest](https://google.github.io/googletest/primer.html). CMake downloads it during the configure step (pinned version and checksum), so there is nothing to install.

### Running the tests

```sh
cmake --build --preset debug   # tests are rebuilt with the rest of the code
ctest --preset debug           # run all tests
```

Useful variants:

```sh
ctest --preset debug -R Greet                 # only tests whose name matches "Greet"
ctest --preset debug --rerun-failed           # only the tests that failed last time
./build/debug/tests/raytracer_tests --gtest_filter='Greet.*'   # run the test binary directly
```

In VS Code (with CMake Tools), the tests also appear in the **Testing** panel, where each test can be run or debugged on its own.

### The TDD cycle

Every new feature follows the same loop:

1. **Red:** write a small test that describes the behaviour we want. Build and run it: it must fail (or not compile, if the function does not exist yet). This proves the test actually checks something.
2. **Green:** write the simplest code that makes the test pass. Run the tests again: everything must be green.
3. **Refactor:** clean up the code (names, duplication, structure) while keeping all the tests green.

Then commit, and start again with the next small behaviour.

### Example: adding a feature with TDD

Let's say we need a `Vector3` with a `length()` method.

**1. Red.** Create `tests/vector3_test.cpp`:

```cpp
#include <gtest/gtest.h>

#include "vector3.hpp"

TEST(Vector3, LengthOfThreeFourZeroIsFive) {
    const raytracer::Vector3 v{3.0, 4.0, 0.0};
    EXPECT_DOUBLE_EQ(v.length(), 5.0);
}
```

Register it in `tests/CMakeLists.txt`:

```cmake
add_executable(raytracer_tests
    greeting_test.cpp
    vector3_test.cpp
)
```

Build: it fails because `vector3.hpp` does not exist. That is our red step.

**2. Green.** Create `src/vector3.hpp` and `src/vector3.cpp` with the minimum code to pass, and add `vector3.cpp` to `add_library(raytracer_core ...)` in `src/CMakeLists.txt`. Build and run `ctest --preset debug`: the test passes.

**3. Refactor**, run the tests again, commit.

### Writing good tests

- **One behaviour per test**, named after that behaviour: `TEST(Suite, WhatItDoes)`, for example `TEST(Sphere, RayMissesWhenPointingAway)`.
- **One test file per source file:** `src/sphere.cpp` → `tests/sphere_test.cpp`.
- **`EXPECT_*` vs `ASSERT_*`:** `EXPECT_*` reports the failure and continues, `ASSERT_*` stops the test. Use `ASSERT_*` only when the rest of the test makes no sense after a failure (for example, before using a pointer).
- **Floating point:** never compare doubles with `EXPECT_EQ`. Use `EXPECT_DOUBLE_EQ(a, b)` or `EXPECT_NEAR(a, b, tolerance)`.
- Test the library (`raytracer_core`), not `main.cpp`: keep `main.cpp` as small as possible.

Common assertions: [GoogleTest assertions reference](https://google.github.io/googletest/reference/assertions.html).

## Code style

The style is defined in `.clang-format` and applied automatically on save in the dev container (VS Code). To format manually:

```sh
clang-format -i src/*.cpp src/*.hpp tests/*.cpp
```

The compiler runs with strict warnings (`-Wall -Wextra -Wpedantic -Wshadow -Wconversion ...`, or `/W4` on MSVC). Fix warnings as they appear: the `ci` preset turns them into errors.
