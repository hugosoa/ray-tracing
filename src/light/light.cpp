#include "light/light.hpp"

Light::Light(const Vector& position, const Colour& colour)
    : _position(position), _colour(colour) {}

const Vector& Light::getPosition() const { return _position; }
const Colour& Light::getColour() const { return _colour; }
