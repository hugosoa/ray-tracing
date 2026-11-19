#pragma once

#include <vector>

#include "colour/colour.hpp"

// An image of width x height pixels, each one a colour.
// Pixels are stored row by row, starting at the top-left corner (0, 0).
class Image {
private:
    unsigned int _width;
    unsigned int _height;
    std::vector<Colour> _pixels;

    // Index of pixel (x, y) in _pixels. Throws std::out_of_range if (x, y) is outside the image.
    std::size_t index(unsigned int x, unsigned int y) const;

public:
    // Creates a black image of the given width and height, in pixels.
    Image(unsigned int width, unsigned int height);

    // Dimensions, in pixels.
    unsigned int width() const;
    unsigned int height() const;

    // Colour of pixel (x, y). Throws std::out_of_range if (x, y) is outside the image.
    const Colour& pixel(unsigned int x, unsigned int y) const;

    // Sets pixel (x, y) to colour. Throws std::out_of_range if (x, y) is outside the image.
    void setPixel(unsigned int x, unsigned int y, const Colour& colour);
};