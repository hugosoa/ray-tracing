#pragma once

#include <memory>
#include <optional>

#include "math/vector.hpp"
#include "ray/ray.hpp"
#include "material/material.hpp"
#include "geometry/hit_info.hpp"

// A sphere in 3D space, defined by its center and its radius.
class Sphere {
private:
    Vector _center;
    double _radius;

    std::shared_ptr<const Material> _material;

public:
    // Creates a sphere centered at `center` with the given `radius`, shaded by `material`.
    // The material is shared, so several spheres can use the same one.
    Sphere(const Vector& center, double radius, std::shared_ptr<const Material> material);

    const Vector& center() const;
    const Material& material() const;
    double radius() const;

    // Est-ce que ce rayon me touche?
    // Returns where the ray hits the sphere first (closest non negative t),
    // or std::nullopt if it does not hit it.
    std::optional<HitInfo> hit(const Ray& ray) const;
};

