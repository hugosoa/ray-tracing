#pragma once

#include <string>

#include "io/image_saver.hpp"

// Saves an image to disk as an 8-bit RGB PNG file, using LodePNG.
class PngSaver : public ImageSaver {
public:
    // Encodes the image as PNG and writes it to path, replacing any existing file.
    // Colour components are clamped to [0, 1], then scaled to [0, 255].
    // Throws std::runtime_error if the image cannot be encoded or written.
    void save(const Image& image, const std::string& path) override;
};
