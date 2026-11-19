#include <catch2/catch_test_macros.hpp>

#include <memory>

#include "geometry/sphere.hpp"
#include "math/vector.hpp"
#include "ray/ray.hpp"
#include "colour/colour.hpp"
#include "material/flat_shader.hpp"

// ---------- constructor and getters ----------

TEST_CASE("A sphere keeps the center it was created with", "[sphere][constructor]") {
    Sphere sphere(Vector(1.0, 2.0, 3.0), 4.0, std::make_shared<FlatShader>(Colour(1.0, 0.0, 0.0)));

    REQUIRE(sphere.center().x() == 1.0);
    REQUIRE(sphere.center().y() == 2.0);
    REQUIRE(sphere.center().z() == 3.0);
}

TEST_CASE("A sphere keeps the radius it was created with", "[sphere][constructor]") {
    Sphere sphere(Vector(1.0, 2.0, 3.0), 4.0, std::make_shared<FlatShader>(Colour(1.0, 0.0, 0.0)));

    REQUIRE(sphere.radius() == 4.0);
}

TEST_CASE("A sphere keeps the material it was created with", "[sphere][constructor]") {
    auto material = std::make_shared<FlatShader>(Colour(0.25, 0.5, 0.75));
    Sphere sphere(Vector(1.0, 2.0, 3.0), 4.0, material);

    REQUIRE(&sphere.material() == material.get());
}

// ---------- hit ----------

TEST_CASE("A ray pointing at the sphere hits it", "[sphere][hit]") {
    Sphere sphere(Vector(0.0, 0.0, 0.0), 1.0, std::make_shared<FlatShader>(Colour(1.0, 0.0, 0.0)));
    Ray ray(Vector(0.0, 0.0, -10.0), Vector(0.0, 0.0, 1.0));

    REQUIRE(sphere.hit(ray));
}

TEST_CASE("A ray passing beside the sphere misses it", "[sphere][hit]") {
    Sphere sphere(Vector(0.0, 0.0, 0.0), 1.0, std::make_shared<FlatShader>(Colour(1.0, 0.0, 0.0)));
    Ray ray(Vector(5.0, 0.0, -10.0), Vector(0.0, 0.0, 1.0));

    REQUIRE_FALSE(sphere.hit(ray));
}

TEST_CASE("A ray pointing away from the sphere misses it", "[sphere][hit]") {
    Sphere sphere(Vector(0.0, 0.0, 0.0), 1.0, std::make_shared<FlatShader>(Colour(1.0, 0.0, 0.0)));
    // The sphere is behind the ray.
    Ray ray(Vector(0.0, 0.0, 10.0), Vector(0.0, 0.0, 1.0));

    REQUIRE_FALSE(sphere.hit(ray));
}

TEST_CASE("A ray starting inside the sphere hits it", "[sphere][hit]") {
    Sphere sphere(Vector(0.0, 0.0, 0.0), 5.0, std::make_shared<FlatShader>(Colour(1.0, 0.0, 0.0)));
    Ray ray(Vector(1.0, 1.0, 1.0), Vector(0.0, 0.0, 1.0));

    REQUIRE(sphere.hit(ray));
}

TEST_CASE("A ray touching the edge of the sphere hits it", "[sphere][hit]") {
    Sphere sphere(Vector(0.0, 0.0, 0.0), 1.0, std::make_shared<FlatShader>(Colour(1.0, 0.0, 0.0)));
    // Passes exactly at x = 1, the edge of the sphere.
    Ray ray(Vector(1.0, 0.0, -10.0), Vector(0.0, 0.0, 1.0));

    REQUIRE(sphere.hit(ray));
}

TEST_CASE("A ray with a non-unit direction still hits the sphere", "[sphere][hit]") {
    Sphere sphere(Vector(0.0, 0.0, 0.0), 1.0, std::make_shared<FlatShader>(Colour(1.0, 0.0, 0.0)));
    Ray ray(Vector(0.0, 0.0, -10.0), Vector(0.0, 0.0, 7.0));

    REQUIRE(sphere.hit(ray));
}
