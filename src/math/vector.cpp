#include "vector.hpp"
#include <cmath>

Vector::Vector(double x, double y, double z) : _x(x), _y(y), _z(z) {}

double Vector::getX() const { return _x; }
double Vector::getY() const { return _y; }
double Vector::getZ() const { return _z; }

Vector Vector::operator+(const Vector& other) const {
    return Vector(_x + other._x, _y + other._y, _z + other._z);
}

Vector Vector::operator-(const Vector& other) const {
    return Vector(_x - other._x, _y - other._y, _z - other._z);
}

Vector Vector::operator*(double t) const {
    return Vector(_x * t, _y * t, _z * t);
}

Vector operator*(double t, const Vector& v) {
    return v * t;
}

double Vector::dot(const Vector& other) const {
    return _x * other._x + _y * other._y + _z * other._z;
}

double Vector::length() const {
    return std::sqrt(dot(*this));
}

Vector Vector::normalised() const {
    return *this * (1.0 / length());
}
