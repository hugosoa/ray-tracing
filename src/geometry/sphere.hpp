#pragma once
#include "math/vector.hpp"
#include "ray/ray.hpp"

class Sphere {
private:
    Vector _center;
    double _radius;

public:
    Sphere(const Vector& center, double radius);

    const Vector& center() const;
    double radius() const;

    // Est-ce que ce rayon me touche? 
    bool hit(Ray& ray);
};
