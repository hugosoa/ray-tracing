#include "io/png_saver.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <vector>

#include <lodepng.h>

namespace {

// Converts a colour component from [0, 1] to a byte in [0, 255].
// Values outside [0, 1] are clamped first.
unsigned char toByte(double component) {
    double clamped = std::clamp(component, 0.0, 1.0);
    return static_cast<unsigned char>(std::lround(clamped * 255.0));
}

}  // namespace

void PngSaver::save(const Image& image, const std::string& path) {
    // LodePNG expects the pixels row by row from the top-left corner, 3 bytes (R, G, B) each,
    // which is the same order as Image.
    std::vector<unsigned char> rgb;
    rgb.reserve(static_cast<std::size_t>(image.width()) * image.height() * 3);

    for (unsigned int y = 0; y < image.height(); ++y) {
        for (unsigned int x = 0; x < image.width(); ++x) {
            const Colour& colour = image.pixel(x, y);
            rgb.push_back(toByte(colour.r()));
            rgb.push_back(toByte(colour.g()));
            rgb.push_back(toByte(colour.b()));
        }
    }

    unsigned int error = lodepng::encode(path, rgb, image.width(), image.height(), LCT_RGB, 8);
    if (error != 0) {
        throw std::runtime_error("cannot save PNG to '" + path + "': " + lodepng_error_text(error));
    }
}
