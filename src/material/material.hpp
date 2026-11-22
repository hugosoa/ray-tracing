#pragma once

#include "colour/colour.hpp"

// Declared here rather than included: hit_info.hpp itself includes this file.
struct HitInfo;
class Light;

// Decides the colour of a surface when a ray hits it.
// Each way of shading (flat, Lambert, ...) is a subclass that implements shade().
class Material {
public:
    // Virtual so that deleting a subclass through a Material pointer is safe.
    virtual ~Material() = default;

    // Colour of the surface at the point described by `hit`, lit by `light`.
    // `hit.normal` has length 1: every Shape promises it (see geometry/shape.hpp).
    // Implemented by each subclass.
    virtual Colour shade(const HitInfo& hit, const Light& light) const = 0;
};
