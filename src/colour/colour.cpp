#include "colour/colour.hpp"

Colour::Colour(double r, double g, double b) : _r(r), _g(g), _b(b) {}

double Colour::getR() const { return _r; }
double Colour::getG() const { return _g; }
double Colour::getB() const { return _b; }
