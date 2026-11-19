#pragma once

#include "math/vector.hpp"
#include "ray/ray.hpp"
#include "geometry/sphere.hpp"
#include "colour/colour.hpp"
#include "image/image.hpp"

// A camera placed at `position`.
// For now it always faces the positive Z axis (direction (0, 0, 1)).
class Camera {
private:
    Vector _position;
    double _screenWidth;

public:
    // Creates a camera at `position`, looking at a screen `screenWidth` wide.
    Camera(const Vector& position, double screenWidth = 2.0);

    const Vector& position() const;

    Ray rayThroughCenter() const;

    Ray rayThroughPixel(int column, int row, int imageWidth, int imageHeight);

    // Colour seen along `ray`: the colour of `sphere` if the ray hits it, black otherwise.
    Colour trace(Ray& ray, Sphere& sphere) const;

    // Renders `sphere` into an image of imageWidth x imageHeight pixels.
    Image render(Sphere& sphere, int imageWidth, int imageHeight);
};

