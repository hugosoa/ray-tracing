#include "scene/scene.hpp"

#include <utility>

Scene::Scene(const Light& light) : _light(light) {}

const Light& Scene::light() const { return _light; }

void Scene::add(std::unique_ptr<Shape> shape) { _shapes.push_back(std::move(shape)); }

std::optional<HitInfo> Scene::nearestHit(const Ray& ray) const {
    std::optional<HitInfo> nearest;
    for (const std::unique_ptr<Shape>& shape : _shapes) {
        std::optional<HitInfo> hit = shape->hit(ray);
        // Keep this hit if it is the first one, or nearer than the nearest so far.
        if (hit && (!nearest || hit->t < nearest->t)) {
            nearest = hit;
        }
    }
    return nearest;
}
