#include <catch2/catch_test_macros.hpp>

#include "colour/colour.hpp"

// ---------- constructor and getters ----------

TEST_CASE("A colour keeps the components it was created with", "[colour][constructor]") {
    Colour colour(0.1, 0.5, 0.9);

    REQUIRE(colour.getR() == 0.1);
    REQUIRE(colour.getG() == 0.5);
    REQUIRE(colour.getB() == 0.9);
}

TEST_CASE("Black has all components at 0", "[colour][constructor]") {
    Colour black(0.0, 0.0, 0.0);

    REQUIRE(black.getR() == 0.0);
    REQUIRE(black.getG() == 0.0);
    REQUIRE(black.getB() == 0.0);
}

TEST_CASE("Assigning a colour replaces all its components", "[colour][copy]") {
    Colour colour(0.0, 0.0, 0.0);

    colour = Colour(1.0, 0.5, 0.25);

    REQUIRE(colour.getR() == 1.0);
    REQUIRE(colour.getG() == 0.5);
    REQUIRE(colour.getB() == 0.25);
}
