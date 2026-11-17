#pragma once

// A vector in 3D space, with components x, y and z.
class Vector {
private:
    double _x;
    double _y;
    double _z;

public:
    // Creates the zero vector (0, 0, 0).
    Vector();

    // Creates a vector with the given components.
    Vector(double x, double y, double z);

    // Read the components (they are private, so other code uses these).
    double getX() const;
    double getY() const;
    double getZ() const;

    // Returns a new vector that is the sum of this vector and `other`.
    // Lets you write: Vector v3 = v1 + v2;
    Vector operator+(const Vector& other) const;

    // Returns a new vector that is this vector minus `other`.
    // Lets you write: Vector v3 = v1 - v2;
    Vector operator-(const Vector& other) const;
};
