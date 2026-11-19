#include <catch2/catch_test_macros.hpp>

#include "ray/ray.hpp"
#include "math/vector.hpp"

// ---------- constructor and getters ----------

TEST_CASE("A ray keeps the origin it was created with", "[ray][constructor]") {
    Vector origin(1.0, 2.0, 3.0);
    Vector direction(4.0, 5.0, 6.0);

    Ray ray(origin, direction);

    REQUIRE(ray.getOrigin().x() == 1.0);
    REQUIRE(ray.getOrigin().y() == 2.0);
    REQUIRE(ray.getOrigin().z() == 3.0);
}

TEST_CASE("A ray keeps the direction it was created with", "[ray][constructor]") {
    Vector origin(1.0, 2.0, 3.0);
    Vector direction(4.0, 5.0, 6.0);

    Ray ray(origin, direction);

    REQUIRE(ray.getDirection().x() == 4.0);
    REQUIRE(ray.getDirection().y() == 5.0);
    REQUIRE(ray.getDirection().z() == 6.0);
}

TEST_CASE("A ray works with negative and decimal values", "[ray][constructor]") {
    Ray ray(Vector(-1.5, 0.0, -3.25), Vector(0.5, -2.0, 0.75));

    REQUIRE(ray.getOrigin().x() == -1.5);
    REQUIRE(ray.getOrigin().y() == 0.0);
    REQUIRE(ray.getOrigin().z() == -3.25);
    REQUIRE(ray.getDirection().x() == 0.5);
    REQUIRE(ray.getDirection().y() == -2.0);
    REQUIRE(ray.getDirection().z() == 0.75);
}

TEST_CASE("A ray keeps its own copy of the vectors", "[ray][constructor]") {
    Vector origin(1.0, 2.0, 3.0);
    Vector direction(4.0, 5.0, 6.0);
    Ray ray(origin, direction);

    // Changing the original variables must not change the ray.
    origin = Vector(9.0, 9.0, 9.0);
    direction = Vector(9.0, 9.0, 9.0);

    REQUIRE(ray.getOrigin().x() == 1.0);
    REQUIRE(ray.getDirection().x() == 4.0);
}

// ---------- copy ----------

TEST_CASE("Copying a ray gives the same origin and direction", "[ray][copy]") {
    Ray original(Vector(1.0, 2.0, 3.0), Vector(4.0, 5.0, 6.0));

    Ray copy = original;

    REQUIRE(copy.getOrigin().x() == 1.0);
    REQUIRE(copy.getOrigin().y() == 2.0);
    REQUIRE(copy.getOrigin().z() == 3.0);
    REQUIRE(copy.getDirection().x() == 4.0);
    REQUIRE(copy.getDirection().y() == 5.0);
    REQUIRE(copy.getDirection().z() == 6.0);
}
