#include "geometry/sphere.hpp"
#include <algorithm>
#include <cmath>
#include <utility>

Sphere::Sphere(const Vector& center, double radius, std::shared_ptr<const Material> material)
    : _center(center), _radius(radius), _material(std::move(material)) {}

const Vector& Sphere::center() const { return _center; }
const Material& Sphere::material() const { return *_material; }
double Sphere::radius() const { return _radius; }

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

    double t1 = (-b + sqrt(delta)) / (2 * a);
    double t2 = (-b - sqrt(delta)) / (2 * a);

    // Ignore negative t (behind the ray), then keep the lowest of what is left.
    double t;
    if (t1 >= 0 && t2 >= 0) {
        t = std::min(t1, t2);
    } else if (t1 >= 0) {
        t = t1;
    } else if (t2 >= 0) {
        t = t2;
    } else {
        return std::nullopt;
    }

    Vector point = ray.at(t);
    Vector normal = (point - _center).normalised();

    return HitInfo{point, normal, _material.get()};
}
