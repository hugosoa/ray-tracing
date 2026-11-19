#pragma once

#include "colour/colour.hpp"
#include "material/material.hpp"

// A diffuse (matte) material using Lambert's cosine law:
// the more directly the surface faces the light, the brighter it is.
class LambertShader : public Material {
private:
    Colour _colour;

public:
    // Creates a Lambert shader for a surface of the given `colour`.
    explicit LambertShader(const Colour& colour);

    // Surface colour times light colour, scaled by max(0, N . L), where N is the
    // surface normal and L the direction from the hit point to the light (both length 1).
    // Points facing away from the light are black.
    Colour shade(const HitInfo& hit, const Light& light) const override;
};
