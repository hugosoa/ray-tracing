#pragma once

#include <memory>
#include <optional>

#include "math/vector.hpp"
#include "ray/ray.hpp"
#include "material/material.hpp"
#include "geometry/hit_info.hpp"
#include "geometry/shape.hpp"

// An infinite plane, defined by a point on it and its normal.
// It faces the same way everywhere, so every hit has the same normal.
class Plane : public Shape {
private:
    Vector _point;
    Vector _normal;

    std::shared_ptr<const Material> _material;

public:
    // Creates the plane through `point` facing `normal`, shaded by `material`.
    // The normal is stored with length 1.
    Plane(const Vector& point, const Vector& normal, std::shared_ptr<const Material> material);

    // Where the ray hits the plane: t = n.(Q - O) / (n.D).
    // Returns std::nullopt if the ray is parallel to the plane (n.D = 0)
    // or if the plane is behind the ray (t <= 0).
    std::optional<HitInfo> hit(const Ray& ray) const override;
};
