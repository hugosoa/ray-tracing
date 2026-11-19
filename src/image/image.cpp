#include "image/image.hpp"

#include <stdexcept>

Image::Image(unsigned int width, unsigned int height)
    : _width(width),
      _height(height),
      _pixels(static_cast<std::size_t>(width) * height, Colour(0.0, 0.0, 0.0)) {}

unsigned int Image::width() const { return _width; }
unsigned int Image::height() const { return _height; }

std::size_t Image::index(unsigned int x, unsigned int y) const {
    if (x >= _width || y >= _height) {
        throw std::out_of_range("pixel coordinate outside the image");
    }
    return static_cast<std::size_t>(y) * _width + x;
}

const Colour& Image::pixel(unsigned int x, unsigned int y) const {
    return _pixels[index(x, y)];
}

void Image::setPixel(unsigned int x, unsigned int y, const Colour& colour) {
    _pixels[index(x, y)] = colour;
}
