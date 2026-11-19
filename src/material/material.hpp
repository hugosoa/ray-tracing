#pragma once

#include "colour/colour.hpp"

// Decides the colour of a surface when a ray hits it.
// Each way of shading (flat, diffuse, ...) is a subclass that implements shade().
class Material {
public:
    // Virtual so that deleting a subclass through a Material pointer is safe.
    virtual ~Material() = default;

    // Colour of the surface. Implemented by each subclass.
    virtual Colour shade() const = 0;
};
