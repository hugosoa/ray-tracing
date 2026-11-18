#pragma once

#include "math/vector.hpp"

// A ray: a half-line that starts at `origin` and goes in `direction`.
class Ray {
private:
    Vector _origin;
    Vector _direction;

public:
    // Creates a ray starting at `origin` and going in `direction`.
    Ray(const Vector& origin, const Vector& direction);

    // Read the origin and direction (they are private, so other code uses these).
    Vector getOrigin() const;
    Vector getDirection() const;
};
