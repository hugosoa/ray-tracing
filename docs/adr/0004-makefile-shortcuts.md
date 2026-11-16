# 4. Use a Makefile as a command shortcut layer over CMake

## Status

Proposed

## Context

The CMake commands to configure, build, run and test (ADR 2) are long and hard to remember, especially for people new to C++. We want short commands, like `npm run build` or `npm run start` in JavaScript projects.

Alternatives considered:

- **CMake only:** a workflow preset (`cmake --workflow --preset debug`) and custom targets (`cmake --build --preset debug --target run`). Built in, but the commands stay long.
- **A task runner** such as `just`: short commands, but one more tool to install on every machine.
- **Editor buttons** (VS Code CMake Tools status bar): only help people using that editor.
- **A Makefile** that only calls the CMake commands.

## Decision

We will add a root `Makefile` with the targets `build`, `start`, `test` and `clean`. Each target only calls CMake or CTest with a preset (`debug` by default, `PRESET=<name>` to change it). CMake stays the build system: the Makefile holds no compiler flags, sources or build logic.

We also add workflow presets to `CMakePresets.json`, so `cmake --workflow --preset <name>` configures, builds and tests in one command without `make`.

## Consequences

- Day-to-day commands become `make build`, `make start`, `make test` and `make clean`.
- `make` is already in the dev container (`build-essential`, ADR 1), so nothing new is installed there.
- `make` is not available by default on native Windows. People using the native fallback there use the CMake commands or the workflow preset instead.
- There are now two ways to run the same steps, which the README must keep in sync.
- Makefiles require tabs for indentation, which is an easy mistake to make when editing.
