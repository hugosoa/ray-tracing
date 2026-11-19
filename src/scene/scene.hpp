#pragma once

#include <memory>
#include <optional>
#include <vector>

#include "ray/ray.hpp"
#include "light/light.hpp"
#include "geometry/hit_info.hpp"
#include "geometry/shape.hpp"

// Everything in the world: the shapes, and the light that shines on them.
// The scene owns its shapes.
class Scene {
private:
    Light _light;
    std::vector<std::unique_ptr<Shape>> _shapes;

public:
    // Creates an empty scene, lit by `light`.
    explicit Scene(const Light& light);

    const Light& light() const;

    // Adds `shape` to the scene, which then owns it.
    void add(std::unique_ptr<Shape> shape);

    // The hit with the smallest t among all the shapes, or std::nullopt if the ray hits none.
    std::optional<HitInfo> nearestHit(const Ray& ray) const;
};
