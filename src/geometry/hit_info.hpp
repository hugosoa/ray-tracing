#pragma once

#include "math/vector.hpp"
#include "material/material.hpp"

// What we know about the point where a ray hits an object.
struct HitInfo {
    // Where the ray hits the surface.
    Vector point;

    // Normal of the surface at `point`, pointing outwards, with length 1.
    Vector normal;

    // Material of the object that was hit, used for shading.
    // Not owned: it stays valid as long as the object that was hit exists.
    const Material* material;
};
