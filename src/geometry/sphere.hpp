#pragma once
#include "math/vector.hpp"
#include "ray/ray.hpp"
#include "colour/colour.hpp"

// A sphere in 3D space, defined by its center and its radius.
class Sphere {
private:
    Vector _center;
    double _radius;

    Colour _colour;

public:
    Sphere(const Vector& center, double radius, const Colour& colour);

    const Vector& center() const;
    const Colour& colour() const;
    double radius() const;

    // Est-ce que ce rayon me touche? 
    bool hit(Ray& ray);
};

