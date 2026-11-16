# 1. Use a dev container for the development environment

## Status

Accepted

## Context

Team members work on different operating systems (Windows, macOS, Linux). A C++ toolchain (compiler, CMake, Ninja, formatter, debugger) is installed and configured differently on each one, and versions drift between machines.

Alternatives considered:

- **Native toolchain on each machine:** each person installs CMake, Ninja and a C++20 compiler themselves (Xcode tools, apt packages, or Visual Studio 2022).
- **Dev container:** a Docker image that holds the whole toolchain, opened by the editor or the Dev Container CLI.

## Decision

We will use a dev container (`.devcontainer/`) as the recommended environment, so that everyone gets exactly the same compiler and tools, whatever their OS.

The image is based on Ubuntu 24.04 and contains GCC, Clang, CMake, Ninja, clang-format, clang-tidy, clangd and gdb. The native toolchain stays documented in the README as a fallback.

## Consequences

- Everyone builds with the same compiler and tool versions, so "it works on my machine" problems are less likely.
- Every team member needs Docker running (on Windows, Docker Desktop with the WSL 2 backend).
- The first start builds the image, which takes a few minutes.
- Builds run inside a container, which can be slower than native, especially with Docker Desktop on Windows and macOS.
- People who use the native fallback may end up with different compiler versions, so the guarantee only holds inside the container.
