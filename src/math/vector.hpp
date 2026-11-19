#pragma once

// A vector in 3D space, with components x, y and z.
class Vector {
private:
    double _x;
    double _y;
    double _z;

public:
    // Creates the vector (x, y, z).
    Vector(double x, double y, double z);

    // Components.
    double x() const;
    double y() const;
    double z() const;

    // Component-wise sum and difference: v1 + v2, v1 - v2.
    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;

    // Multiply each component by t: v * t or t * v.
    Vector operator*(double t) const;
    friend Vector operator*(double t, const Vector& v);

    // Dot product: x1*x2 + y1*y2 + z1*z2.
    double dot(const Vector& other) const;

    // Length (norm) of the vector.
    double length() const;

    // Same direction, length 1.
    Vector normalised() const;
};
