#include "geometry/plane.hpp"

#include <utility>

Plane::Plane(const Vector& point, const Vector& normal, std::shared_ptr<const Material> material)
    : _point(point), _normal(normal.normalised()), _material(std::move(material)) {}

std::optional<HitInfo> Plane::hit(const Ray& ray) const {
    double nDotD = _normal.dot(ray.getDirection());
    if (nDotD == 0.0) {
        return std::nullopt;
    }

    double t = _normal.dot(_point - ray.getOrigin()) / nDotD;
    if (t <= 0.0) {
        return std::nullopt;
    }

    return HitInfo{t, ray.at(t), _normal, _material.get()};
}
