#include "geometry/sphere.hpp"
#include <cmath>

Sphere::Sphere(const Vector& center, double radius, const Colour& colour)
    : _center(center), _radius(radius), _colour(colour) {}

const Vector& Sphere::center() const { return _center; }
const Colour& Sphere::colour() const { return _colour; }
double Sphere::radius() const { return _radius; }

bool Sphere::hit(Ray& ray) {
    Vector D = ray.getDirection();
    Vector O = ray.getOrigin();
    Vector C = _center;

    Vector L = O - C;

    double a = D.dot(D);
    double b = 2 * D.dot(L);
    double c = L.dot(L) - _radius * _radius;

    double delta = b * b - 4 * a * c;
    if (delta < 0) { return false; }

    double t1 = (-b + sqrt(delta)) / (2 * a);
    double t2 = (-b - sqrt(delta)) / (2 * a);

    if (t1 >= 0 || t2 >= 0) {
        return true;
    }

   return false;
}