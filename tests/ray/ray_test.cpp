#include <catch2/catch_test_macros.hpp>

#include "ray/ray.hpp"
#include "math/vector.hpp"

// ---------- constructor and getters ----------

TEST_CASE("A ray keeps the origin it was created with", "[ray][constructor]") {
    Vector origin(1.0, 2.0, 3.0);
    Vector direction(4.0, 5.0, 6.0);

    Ray ray(origin, direction);

    REQUIRE(ray.getOrigin().getX() == 1.0);
    REQUIRE(ray.getOrigin().getY() == 2.0);
    REQUIRE(ray.getOrigin().getZ() == 3.0);
}

TEST_CASE("A ray keeps the direction it was created with", "[ray][constructor]") {
    Vector origin(1.0, 2.0, 3.0);
    Vector direction(4.0, 5.0, 6.0);

    Ray ray(origin, direction);

    REQUIRE(ray.getDirection().getX() == 4.0);
    REQUIRE(ray.getDirection().getY() == 5.0);
    REQUIRE(ray.getDirection().getZ() == 6.0);
}

TEST_CASE("A ray works with negative and decimal values", "[ray][constructor]") {
    Ray ray(Vector(-1.5, 0.0, -3.25), Vector(0.5, -2.0, 0.75));

    REQUIRE(ray.getOrigin().getX() == -1.5);
    REQUIRE(ray.getOrigin().getY() == 0.0);
    REQUIRE(ray.getOrigin().getZ() == -3.25);
    REQUIRE(ray.getDirection().getX() == 0.5);
    REQUIRE(ray.getDirection().getY() == -2.0);
    REQUIRE(ray.getDirection().getZ() == 0.75);
}

TEST_CASE("A ray keeps its own copy of the vectors", "[ray][constructor]") {
    Vector origin(1.0, 2.0, 3.0);
    Vector direction(4.0, 5.0, 6.0);
    Ray ray(origin, direction);

    // Changing the original variables must not change the ray.
    origin = Vector(9.0, 9.0, 9.0);
    direction = Vector(9.0, 9.0, 9.0);

    REQUIRE(ray.getOrigin().getX() == 1.0);
    REQUIRE(ray.getDirection().getX() == 4.0);
}

// ---------- copy ----------

TEST_CASE("Copying a ray gives the same origin and direction", "[ray][copy]") {
    Ray original(Vector(1.0, 2.0, 3.0), Vector(4.0, 5.0, 6.0));

    Ray copy = original;

    REQUIRE(copy.getOrigin().getX() == 1.0);
    REQUIRE(copy.getOrigin().getY() == 2.0);
    REQUIRE(copy.getOrigin().getZ() == 3.0);
    REQUIRE(copy.getDirection().getX() == 4.0);
    REQUIRE(copy.getDirection().getY() == 5.0);
    REQUIRE(copy.getDirection().getZ() == 6.0);
}

// ---------- at ----------

TEST_CASE("The point at t = 0 is the origin of the ray", "[ray][at]") {
    Ray ray(Vector(1.0, 2.0, 3.0), Vector(4.0, 5.0, 6.0));

    Vector point = ray.at(0.0);

    REQUIRE(point.getX() == 1.0);
    REQUIRE(point.getY() == 2.0);
    REQUIRE(point.getZ() == 3.0);
}

TEST_CASE("The point at t is origin + t * direction", "[ray][at]") {
    Ray ray(Vector(1.0, 2.0, 3.0), Vector(4.0, 5.0, 6.0));

    Vector point = ray.at(2.0);

    REQUIRE(point.getX() == 9.0);
    REQUIRE(point.getY() == 12.0);
    REQUIRE(point.getZ() == 15.0);
}

TEST_CASE("The point at a negative t is behind the origin", "[ray][at]") {
    Ray ray(Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, 1.0));

    Vector point = ray.at(-3.0);

    REQUIRE(point.getZ() == -3.0);
}
