# AGENTS.md

C++20 ray tracer. Run all commands from the repository root.

## Build, run, test

Shortcuts (they only call the CMake commands below): `make build`, `make start`, `make test`, `make clean`; add `PRESET=release` to change preset.

```sh
cmake --preset debug             # configure (once, or after editing a CMakeLists.txt)
cmake --build --preset debug     # build
./build/debug/src/raytracer      # run
ctest --preset debug             # run the tests
```

Other presets: `release`, `ci` (Release with warnings as errors, to check code before merging).

## Architecture decisions

Our architecture decisions are in `docs/adr/`. Read them before changing the build, the tools or the test setup.

- Never go against an ADR whose status is Accepted.
- To change a decision, write a new ADR in `docs/adr/` with status Proposed, then ask the user.
- Never set an ADR's status to Accepted. Only the team does that.
