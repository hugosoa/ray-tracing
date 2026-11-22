#include "material/lambert_shader.hpp"

#include <algorithm>

#include "geometry/hit_info.hpp"
#include "light/light.hpp"
#include "math/vector.hpp"

LambertShader::LambertShader(const Colour& colour) : _colour(colour) {}

Colour LambertShader::shade(const HitInfo& hit, const Light& light) const {
    Vector toLight = (light.getPosition() - hit.point).normalised();

    // Cosine of the angle between the normal and the light direction.
    // Negative means the light is behind the surface: no light reaches it.
    double intensity = std::max(0.0, hit.normal.dot(toLight));

    const Colour& lightColour = light.getColour();
    return Colour(_colour.getR() * lightColour.getR() * intensity,
                  _colour.getG() * lightColour.getG() * intensity,
                  _colour.getB() * lightColour.getB() * intensity);
}
