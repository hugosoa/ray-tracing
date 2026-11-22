# 0005 — Use LodePNG to Save Images as PNG

## Status

Accepted

## Context

The raytracer renders into an in-memory `Image` and needs to write it to disk
in a format that any image viewer can open. PNG is lossless and universally
supported, but encoding it by hand (zlib compression, CRC checksums, chunk
layout) is out of scope for the course.

Alternatives considered:

- **Write PPM by hand** — trivial to implement with no dependency, but many
  image viewers (and the default ones on Windows and macOS) cannot open PPM.
- **libpng** — the reference implementation, but it is a system library with
  a zlib dependency, a verbose C API, and per-platform installation steps.
- **stb_image_write** — single header and easy to vendor, but it is part of
  a larger collection and its PNG output is less compressed.

## Decision

Use [LodePNG](https://github.com/lvandeve/lodepng), fetched with CMake
`FetchContent` (consistent with [ADR 0002](0002-cmake.md)). LodePNG has no
release tags, so it is pinned to a specific commit in `CMakeLists.txt`.
LodePNG ships no `CMakeLists.txt`, so the project builds `lodepng.cpp` as a
static library target, `lodepng`, which both `raytracer` and `tests` link.

`PngSaver` (in `src/io/`) is the only production code that uses LodePNG,
behind the `ImageSaver` interface. Tests also use LodePNG to decode saved
files and check their pixels.

## Consequences

**Positive:**
- Pure C++ with no external dependencies (it includes its own zlib), so it
  builds identically on every platform and in CI.
- A simple API: one call to encode and save, one call to load and decode.
- Hidden behind `ImageSaver`, so it can be replaced without touching the
  rest of the raytracer.

**Negative:**
- Pinned to a commit rather than a release: updating means choosing a new
  commit hash by hand.
- `FetchContent` downloads it on first configure, which adds to the
  internet-access requirement and first-build time noted in ADR 0002.
