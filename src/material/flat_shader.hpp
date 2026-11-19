#pragma once

#include "colour/colour.hpp"
#include "material/material.hpp"

// A material that always shades with the same colour, without any lighting.
class FlatShader : public Material {
private:
    Colour _colour;

public:
    // Creates a flat shader that always returns `colour`.
    explicit FlatShader(const Colour& colour);

    // Returns the colour given to the constructor.
    Colour shade() const override;
};
