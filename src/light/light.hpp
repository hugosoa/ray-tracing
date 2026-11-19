#pragma once

#include "math/vector.hpp"
#include "colour/colour.hpp"

// A point light: it shines in every direction from `position`, with the given `colour`.
class Light {
private:
    Vector _position;
    Colour _colour;

public:
    // Creates a point light at `position` with the given `colour`.
    Light(const Vector& position, const Colour& colour);

    const Vector& position() const;
    const Colour& colour() const;
};
