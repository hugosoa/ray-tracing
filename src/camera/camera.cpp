#include "camera/camera.hpp"

Camera::Camera(const Vector& position, double screenWidth)
    : _position(position), _screenWidth(screenWidth) {}

const Vector& Camera::position() const { return _position; }

Ray Camera::rayThroughCenter() const {
    return Ray(_position, Vector(0.0, 0.0, 1.0));
}

Ray Camera::rayThroughPixel(int column, int row, int imageWidth, int imageHeight) {

    double pixelSize = _screenWidth / imageWidth;

    double x = ((column + 0.5) - (imageWidth / 2.0)) * pixelSize;
    double y = -((row + 0.5) - (imageHeight / 2.0)) * pixelSize;

    Vector pixelPosition(x, y, 0);
    Vector direction = pixelPosition - _position;

    return Ray(_position, direction);
}

Colour Camera::trace(Ray& ray, Sphere& sphere) const {
    if (sphere.hit(ray)) {
        return sphere.colour();
    }
    return Colour(0, 0, 0);
}

Image Camera::render(Sphere& sphere, int imageWidth, int imageHeight) {
    Image image(imageWidth, imageHeight);

    for (int row = 0; row < imageHeight; ++row) {
        for (int column = 0; column < imageWidth; ++column) {
            Ray ray = rayThroughPixel(column, row, imageWidth, imageHeight);
            image.setPixel(column, row, trace(ray, sphere));
        }
    }

    return image;
}
