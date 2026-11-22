#pragma once

#include "math/vector.hpp"
#include "ray/ray.hpp"
#include "scene/scene.hpp"
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

    const Vector& getPosition() const;

    // Ray from the camera through the centre of pixel (column, row), on a screen at z = 0.
    Ray rayThroughPixel(int column, int row, int imageWidth, int imageHeight) const;

    // Colour seen along `ray`: the nearest hit in `scene`, shaded by its material with the scene's light,
    // or black if the ray hits nothing.
    Colour trace(const Ray& ray, const Scene& scene) const;

    // Renders `scene` into an image of imageWidth x imageHeight pixels.
    Image render(const Scene& scene, int imageWidth, int imageHeight) const;
};

