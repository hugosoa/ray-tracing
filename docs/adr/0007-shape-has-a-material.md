# 0007 — A Shape Has a Material

## Status

Proposed

## Context

The renderer must work with any kind of object (sphere, plane, later
cylinders or triangles) and colour it in different ways (a flat colour, Lambert
shading, later mirrors). Two questions follow:

1. How does the renderer talk to objects without knowing what they are?
2. How does an object know its colour?

"Is a" or "has a": a sphere **is a** shape, but a sphere is not a kind of
colour; it **has** a material. Mixing the two leads to one class per
combination (`YellowLambertSphere`, `GreyFlatPlane`, ...).

Alternatives considered for the colour:

- **A `Colour` field in each shape** — simplest, but there is no room for
  lighting, and every new way of shading would change every shape.
- **Inheritance** (`LambertSphere : Sphere`) — one class per shape and per
  shading: the number of classes multiplies.
- **A material copied by value** in each shape — impossible here: `Material`
  is abstract (it has `FlatShader` and `LambertShader`), and copying it as a
  `Material` would keep only the base part (slicing).
- **`std::unique_ptr<Material>`** in each shape — works, but two shapes could
  not share one material.

## Decision

- Every object a ray can hit implements the abstract class `Shape`
  (`geometry/shape.hpp`), with one method, `hit(ray)`. It promises the nearest
  hit with t > 0 and a normal of length 1, or nothing.
- A shape **has a** material: it keeps a `std::shared_ptr<const Material>`, so
  several shapes can share the same material.
- `Material` is a Strategy with one method, `shade(hit, light)`. `FlatShader`
  and `LambertShader` are two interchangeable strategies.
- `hit()` returns a `HitInfo` (t, point, normal, material). Its material is a
  plain `const Material*`: it only borrows the material for the time of one
  shading, the shape keeps owning it.
- `Scene` owns its shapes (`std::unique_ptr<Shape>`) and returns the hit with
  the smallest t. `Camera` only knows `Scene`, `Shape` and `Material`: only
  `main.cpp` names `Sphere`, `Plane` or `LambertShader`.

## Consequences

**Positive:**
- A new shape is new files plus two lines in `CMakeLists.txt` (and `main.cpp`
  if it is in the picture). No existing class changes (open/closed principle).
- A new way of shading is a new `Material` subclass, with no change to shapes.
- Shapes and materials combine freely: a Lambert sphere, a flat plane, ...

**Negative:**
- Each shape repeats a `_material` field and passes it into its `HitInfo`.
- `shared_ptr` and a virtual call per hit cost a little memory and time.
- The raw pointer in `HitInfo` must not outlive the scene.

**Decisions from the tech lead review (2026-11-22):**

| Finding | Decision |
|---|---|
| `Sphere::hit` had a branch that could never run (`t2 > 0` after `t1 > 0`) | Fixed: `tNear`, else `tFar`, each branch has a test |
| `trace` took a modifiable `Ray&`; camera methods were not `const` | Fixed |
| `rayThroughCenter` was no longer used | Removed |
| `shade` needs a unit normal, nothing said so | Fixed: comment on `Material::shade` |
| Comments in French; `<...>` includes in `main.cpp` | Fixed |
| `Camera` has two reasons to change: making rays, and the pixel loop | Parked: split into `Camera` and a `Renderer` when `trace` needs more rays (shadows, reflections) |
| One point light, held by the `Scene` | Parked: an interface when a second kind of light arrives (sun, several lamps) |
| Each shape has its own `_material` field | Parked |
| `LambertShader` multiplies colours component by component | Parked: add `operator*` to `Colour` when a second place needs it |
| `nDotD == 0.0` compares doubles exactly | Kept: a nearly parallel ray gives a huge t, which is still correct |
| `Sphere::getCenter`, `getRadius`, `getMaterial` are only read by tests | Kept |
