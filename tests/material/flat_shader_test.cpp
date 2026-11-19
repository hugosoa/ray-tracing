#include <catch2/catch_test_macros.hpp>

#include "material/flat_shader.hpp"
#include "material/material.hpp"
#include "colour/colour.hpp"

TEST_CASE("A flat shader shades with the colour it was created with", "[material][flat]") {
    FlatShader shader(Colour(0.25, 0.5, 0.75));

    Colour colour = shader.shade();

    REQUIRE(colour.r() == 0.25);
    REQUIRE(colour.g() == 0.5);
    REQUIRE(colour.b() == 0.75);
}

TEST_CASE("A flat shader can be used through a Material reference", "[material][flat]") {
    FlatShader shader(Colour(0.0, 1.0, 0.0));
    const Material& material = shader;

    Colour colour = material.shade();

    REQUIRE(colour.r() == 0.0);
    REQUIRE(colour.g() == 1.0);
    REQUIRE(colour.b() == 0.0);
}
