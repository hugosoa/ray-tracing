#include <catch2/catch_test_macros.hpp>

#include "colour/colour.hpp"

// ---------- constructor and getters ----------

TEST_CASE("A colour keeps the components it was created with", "[colour][constructor]") {
    Colour colour(0.1, 0.5, 0.9);

    REQUIRE(colour.r() == 0.1);
    REQUIRE(colour.g() == 0.5);
    REQUIRE(colour.b() == 0.9);
}

TEST_CASE("Black has all components at 0", "[colour][constructor]") {
    Colour black(0.0, 0.0, 0.0);

    REQUIRE(black.r() == 0.0);
    REQUIRE(black.g() == 0.0);
    REQUIRE(black.b() == 0.0);
}

TEST_CASE("Assigning a colour replaces all its components", "[colour][copy]") {
    Colour colour(0.0, 0.0, 0.0);

    colour = Colour(1.0, 0.5, 0.25);

    REQUIRE(colour.r() == 1.0);
    REQUIRE(colour.g() == 0.5);
    REQUIRE(colour.b() == 0.25);
}
