#include <catch2/catch_test_macros.hpp>

#include <filesystem>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

#include <lodepng.h>

#include "colour/colour.hpp"
#include "image/image.hpp"
#include "io/image_saver.hpp"
#include "io/png_saver.hpp"

namespace {

// A path in the system temp directory, removed when the object goes out of scope.
class TempFile {
private:
    std::filesystem::path _path;

public:
    explicit TempFile(const std::string& name)
        : _path(std::filesystem::temp_directory_path() / name) {
        std::filesystem::remove(_path);
    }
    ~TempFile() { std::filesystem::remove(_path); }

    std::string string() const { return _path.string(); }
};

// Pixels of a PNG file, decoded as 8-bit RGB.
struct DecodedPng {
    std::vector<unsigned char> rgb;
    unsigned int width = 0;
    unsigned int height = 0;
};

DecodedPng decode(const std::string& path) {
    DecodedPng png;
    unsigned int error = lodepng::decode(png.rgb, png.width, png.height, path, LCT_RGB, 8);
    REQUIRE(error == 0u);
    return png;
}

}  // namespace

// ---------- structure ----------

TEST_CASE("ImageSaver is an abstract class", "[saver]") {
    STATIC_REQUIRE(std::is_abstract_v<ImageSaver>);
}

TEST_CASE("PngSaver is a concrete ImageSaver", "[saver][png]") {
    STATIC_REQUIRE(std::is_base_of_v<ImageSaver, PngSaver>);
    STATIC_REQUIRE_FALSE(std::is_abstract_v<PngSaver>);
}

// ---------- saving ----------

TEST_CASE("Saving writes a PNG file with the image's dimensions", "[saver][png]") {
    TempFile file("raytracer_png_saver_dimensions.png");
    Image image(5u, 4u);

    PngSaver().save(image, file.string());

    DecodedPng png = decode(file.string());
    REQUIRE(png.width == 5u);
    REQUIRE(png.height == 4u);
}

TEST_CASE("Saving writes each pixel at its column and row", "[saver][png]") {
    TempFile file("raytracer_png_saver_pixels.png");
    Image image(5u, 4u);
    image.setPixel(3u, 2u, Colour(1.0, 0.0, 0.0));

    PngSaver().save(image, file.string());

    DecodedPng png = decode(file.string());
    for (unsigned int row = 0; row < png.height; ++row) {
        for (unsigned int column = 0; column < png.width; ++column) {
            std::size_t i = (static_cast<std::size_t>(row) * png.width + column) * 3;
            bool isRed = (column == 3u && row == 2u);
            REQUIRE(png.rgb[i] == (isRed ? 255 : 0));
            REQUIRE(png.rgb[i + 1] == 0);
            REQUIRE(png.rgb[i + 2] == 0);
        }
    }
}

TEST_CASE("Saving converts components from [0, 1] to [0, 255]", "[saver][png]") {
    TempFile file("raytracer_png_saver_components.png");
    Image image(1u, 1u);
    image.setPixel(0u, 0u, Colour(0.0, 0.5, 1.0));

    PngSaver().save(image, file.string());

    DecodedPng png = decode(file.string());
    REQUIRE(png.rgb[0] == 0);
    REQUIRE(png.rgb[1] == 128);
    REQUIRE(png.rgb[2] == 255);
}

TEST_CASE("Saving clamps components outside [0, 1]", "[saver][png]") {
    TempFile file("raytracer_png_saver_clamp.png");
    Image image(1u, 1u);
    image.setPixel(0u, 0u, Colour(-0.5, 1.5, 2.0));

    PngSaver().save(image, file.string());

    DecodedPng png = decode(file.string());
    REQUIRE(png.rgb[0] == 0);
    REQUIRE(png.rgb[1] == 255);
    REQUIRE(png.rgb[2] == 255);
}

TEST_CASE("Saving to a path that cannot be written throws", "[saver][png]") {
    Image image(1u, 1u);

    REQUIRE_THROWS_AS(PngSaver().save(image, "/nonexistent-directory/out.png"), std::runtime_error);
}
