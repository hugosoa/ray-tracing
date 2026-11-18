#include "vector.hpp"

Vector::Vector() {
    _x = 0.0;
    _y = 0.0;
    _z = 0.0;
}

Vector::Vector(double x, double y, double z) {
    _x = x;
    _y = y;
    _z = z;
}

double Vector::getX() const {
    return _x;
}

double Vector::getY() const {
    return _y;
}

double Vector::getZ() const {
    return _z;
}

Vector Vector::operator+(const Vector& other) const {
    return Vector(_x + other._x, _y + other._y, _z + other._z);
}

Vector Vector::operator-(const Vector& other) const {
    return Vector(_x - other._x, _y - other._y, _z - other._z);
}

Vector Vector::operator*(double factor) const {
    return Vector(_x * factor, _y * factor, _z * factor);
}
