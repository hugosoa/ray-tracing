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
