#pragma once

// An RGB colour, with red, green and blue components.
class Colour {
private:
    double _r;
    double _g;
    double _b;

public:
    // Creates the colour (r, g, b).
    Colour(double r, double g, double b);

    // Components.
    double getR() const;
    double getG() const;
    double getB() const;
};
