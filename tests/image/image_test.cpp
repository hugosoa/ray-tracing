#include <catch2/catch_test_macros.hpp>

#include <stdexcept>

#include "colour/colour.hpp"
#include "image/image.hpp"

// ---------- constructor and getters ----------

TEST_CASE("An image keeps the width and height it was created with", "[image][constructor]") {
    Image image(640u, 480u);

    REQUIRE(image.width() == 640u);
    REQUIRE(image.height() == 480u);
}

TEST_CASE("Assigning an image replaces its dimensions", "[image][copy]") {
    Image image(1u, 1u);

    image = Image(800u, 600u);

    REQUIRE(image.width() == 800u);
    REQUIRE(image.height() == 600u);
}

// ---------- pixels ----------

TEST_CASE("A new image is all black", "[image][pixel]") {
    Image image(3u, 2u);

    for (unsigned int y = 0; y < 2u; ++y) {
        for (unsigned int x = 0; x < 3u; ++x) {
            REQUIRE(image.pixel(x, y).r() == 0.0);
            REQUIRE(image.pixel(x, y).g() == 0.0);
            REQUIRE(image.pixel(x, y).b() == 0.0);
        }
    }
}

TEST_CASE("Setting a pixel stores its colour at that coordinate", "[image][pixel]") {
    Image image(3u, 2u);

    image.setPixel(2u, 1u, Colour(1.0, 0.5, 0.25));

    REQUIRE(image.pixel(2u, 1u).r() == 1.0);
    REQUIRE(image.pixel(2u, 1u).g() == 0.5);
    REQUIRE(image.pixel(2u, 1u).b() == 0.25);
}

TEST_CASE("setPixel(3, 2) sets the pixel at column 3, row 2 and leaves the others black", "[image][pixel]") {
    // 5 columns x 4 rows, so (2, 3) is also inside the image and a column/row swap would be caught.
    Image image(5u, 4u);

    image.setPixel(3u, 2u, Colour(1.0, 0.5, 0.25));

    for (unsigned int row = 0; row < image.height(); ++row) {
        for (unsigned int column = 0; column < image.width(); ++column) {
            const Colour& colour = image.pixel(column, row);
            if (column == 3u && row == 2u) {
                REQUIRE(colour.r() == 1.0);
                REQUIRE(colour.g() == 0.5);
                REQUIRE(colour.b() == 0.25);
            } else {
                REQUIRE(colour.r() == 0.0);
                REQUIRE(colour.g() == 0.0);
                REQUIRE(colour.b() == 0.0);
            }
        }
    }
}

TEST_CASE("Accessing a pixel outside the image throws", "[image][pixel]") {
    Image image(3u, 2u);
    Colour white(1.0, 1.0, 1.0);

    REQUIRE_THROWS_AS(image.setPixel(3u, 0u, white), std::out_of_range);
    REQUIRE_THROWS_AS(image.setPixel(0u, 2u, white), std::out_of_range);
    REQUIRE_THROWS_AS(image.pixel(3u, 0u), std::out_of_range);
    REQUIRE_THROWS_AS(image.pixel(0u, 2u), std::out_of_range);
}
