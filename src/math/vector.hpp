#pragma once

class Vector {
private:
    double _x;
    double _y;
    double _z;

public:
    Vector(double x, double y, double z);

    double x() const;
    double y() const;
    double z() const;

    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector operator*(double t) const;
    friend Vector operator*(double t, const Vector& v);

    double dot(const Vector& other) const;
    double length() const;
    Vector normalised() const;
};
