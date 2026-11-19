#include "ray.hpp"

Ray::Ray(const Vector& origin, const Vector& direction)
    : _origin(origin), _direction(direction) {}

Vector Ray::getOrigin() const {
    return _origin;
}

Vector Ray::getDirection() const {
    return _direction;
}

Vector Ray::at(double t) const {
    return _origin + _direction * t;
}
