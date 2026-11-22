# 0006 — Naming Style: `_` for Private Members, `get` for Getters

## Status

Proposed

## Context

The code is read by people who are new to C++, so it must be easy to tell at a
glance what a name refers to. Two questions keep coming up when writing a
class: how to name its private data, and how to name the methods that read it.

During the course, the instruction was to write getters without a prefix
(`x()`, `origin()`). It was not written in `AGENTS.md`, so the codebase ended up
mixed: `Ray` had `getOrigin()` and `getDirection()`, while `Vector`, `Colour`,
`Light`, `Image`, `Sphere`, `Camera` and `Scene` had no prefix.

Alternatives considered for getters:

- **No prefix** (`v.x()`, `light.position()`) — shorter, common in modern C++
  and the course's original instruction. But a getter looks the same as any
  other method (`v.length()`, `v.normalised()` compute something).
- **`get` prefix** (`v.getX()`, `light.getPosition()`) — longer, but reading a
  stored value is always visible, and it matches the existing `setPixel`.

Private members: names starting with `_` followed by an uppercase letter
(`_X`) are reserved by the C++ standard, so only `_` followed by a lowercase
letter is safe.

## Decision

- Private member variables start with `_` followed by a lowercase letter:
  `_x`, `_origin`, `_shapes`.
- Getters start with `get` followed by the field name: `getX()`,
  `getOrigin()`, `getColour()`, `getPixel(x, y)`. Setters, when needed, start
  with `set`: `setPixel(x, y, colour)`.
- Methods that compute something keep a verb or a plain name: `dot()`,
  `length()`, `normalised()`, `hit()`, `nearestHit()`, `shade()`.

Both rules are written in `AGENTS.md`.

## Consequences

**Positive:**
- A call like `light.getPosition()` reads as "look up a stored value", while
  `v.normalised()` reads as "compute something".
- One rule for every class; `get` / `set` pairs match (`getPixel` / `setPixel`).
- `_name` tells private data from parameters and local variables, so a
  constructor can write `_radius(radius)` without confusion.

**Negative:**
- Longer expressions in maths-heavy code: `v.getX() * w.getX()` instead of
  `v.x() * w.x()`.
- Goes against the course's original instruction and against part of the
  modern C++ community; readers coming from that style must adapt.
- Renaming every getter touched most files and tests at once.
