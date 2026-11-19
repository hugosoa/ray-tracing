#pragma once

#include <optional>

#include "ray/ray.hpp"
#include "geometry/hit_info.hpp"

// Something in the world that a ray can hit.
// Each kind of shape (sphere, plane, ...) is a subclass that implements hit().
//
// Every shape promises: hit() returns the nearest hit in front of the ray's origin
// (t > 0), with a normal of length 1, or std::nullopt if the ray misses it.
class Shape {
public:
    // Virtual so that deleting a subclass through a Shape pointer is safe.
    virtual ~Shape() = default;

    // Where `ray` first hits the shape. Implemented by each subclass.
    virtual std::optional<HitInfo> hit(const Ray& ray) const = 0;
};
