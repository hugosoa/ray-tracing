#pragma once

#include <string>

#include "image/image.hpp"

// Saves an image to a file, in some format.
// Each format (PNG, PPM, ...) is a subclass that implements save().
class ImageSaver {
public:
    // Virtual so that deleting a subclass through an ImageSaver pointer is safe.
    virtual ~ImageSaver() = default;

    // Saves the image to the file at path. Implemented by each subclass.
    virtual void save(const Image& image, const std::string& path) = 0;
};
