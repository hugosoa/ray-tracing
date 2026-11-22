#include "camera/camera.hpp"

#include <optional>

Camera::Camera(const Vector& position, double screenWidth)
    : _position(position), _screenWidth(screenWidth) {}

const Vector& Camera::getPosition() const { return _position; }

Ray Camera::rayThroughPixel(int column, int row, int imageWidth, int imageHeight) const {
    double pixelSize = _screenWidth / imageWidth;

    double x = ((column + 0.5) - (imageWidth / 2.0)) * pixelSize;
    double y = -((row + 0.5) - (imageHeight / 2.0)) * pixelSize;

    Vector pixelPosition(x, y, 0);
    Vector direction = pixelPosition - _position;

    return Ray(_position, direction);
}

Colour Camera::trace(const Ray& ray, const Scene& scene) const {
    std::optional<HitInfo> hit = scene.nearestHit(ray);
    if (!hit) {
        return Colour(0, 0, 0);
    }
    return hit->material->shade(*hit, scene.getLight());
}

Image Camera::render(const Scene& scene, int imageWidth, int imageHeight) const {
    Image image(imageWidth, imageHeight);

    for (int row = 0; row < imageHeight; ++row) {
        for (int column = 0; column < imageWidth; ++column) {
            Ray ray = rayThroughPixel(column, row, imageWidth, imageHeight);
            image.setPixel(column, row, trace(ray, scene));
        }
    }

    return image;
}
