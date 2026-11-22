#include "geometry/sphere.hpp"
#include <cmath>
#include <utility>

Sphere::Sphere(const Vector& center, double radius, std::shared_ptr<const Material> material)
    : _center(center), _radius(radius), _material(std::move(material)) {}

const Vector& Sphere::getCenter() const { return _center; }
const Material& Sphere::getMaterial() const { return *_material; }
double Sphere::getRadius() const { return _radius; }

std::optional<HitInfo> Sphere::hit(const Ray& ray) const {
    Vector D = ray.getDirection();
    Vector O = ray.getOrigin();
    Vector C = _center;

    Vector L = O - C;

    double a = D.dot(D);
    double b = 2 * D.dot(L);
    double c = L.dot(L) - _radius * _radius;

    double delta = b * b - 4 * a * c;
    if (delta < 0) { return std::nullopt; }

    // a = D.D is positive, so tNear <= tFar: the ray enters the sphere at tNear and leaves it at tFar.
    double sqrtDelta = std::sqrt(delta);
    double tNear = (-b - sqrtDelta) / (2 * a);
    double tFar = (-b + sqrtDelta) / (2 * a);

    // Keep the first t > 0 (t <= 0 is behind the ray, or at its origin).
    double t;
    if (tNear > 0) {
        t = tNear;  // the ray starts outside: it enters the sphere
    } else if (tFar > 0) {
        t = tFar;   // the ray starts inside: it leaves the sphere
    } else {
        return std::nullopt;  // the sphere is behind the ray
    }

    Vector point = ray.at(t);
    Vector normal = (point - _center).normalised();

    return HitInfo{t, point, normal, _material.get()};
}
