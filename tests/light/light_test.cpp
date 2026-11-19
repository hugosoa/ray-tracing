#include <catch2/catch_test_macros.hpp>

#include "light/light.hpp"
#include "math/vector.hpp"
#include "colour/colour.hpp"

// ---------- constructor and getters ----------

TEST_CASE("A light keeps the position it was created with", "[light][constructor]") {
    Light light(Vector(1.0, 2.0, 3.0), Colour(1.0, 1.0, 1.0));

    REQUIRE(light.position().x() == 1.0);
    REQUIRE(light.position().y() == 2.0);
    REQUIRE(light.position().z() == 3.0);
}

TEST_CASE("A light keeps the colour it was created with", "[light][constructor]") {
    Light light(Vector(1.0, 2.0, 3.0), Colour(0.25, 0.5, 0.75));

    REQUIRE(light.colour().r() == 0.25);
    REQUIRE(light.colour().g() == 0.5);
    REQUIRE(light.colour().b() == 0.75);
}
