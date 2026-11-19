#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <memory>
#include <optional>

#include "geometry/plane.hpp"
#include "geometry/hit_info.hpp"
#include "math/vector.hpp"
#include "ray/ray.hpp"
#include "colour/colour.hpp"
#include "light/light.hpp"
#include "material/flat_shader.hpp"

using Catch::Matchers::WithinAbs;

// The floor: point (0, 0, 0), normal (0, 1, 0), green.

TEST_CASE("A ray going down hits the floor", "[plane][hit]") {
    auto green = std::make_shared<FlatShader>(Colour(0.0, 1.0, 0.0));
    Plane floor(Vector(0.0, 0.0, 0.0), Vector(0.0, 1.0, 0.0), green);
    // n.(Q - O) = -8 and n.D = -4, so t = 2 and the hit is at (0, 8, 0) + 2 * (3, -4, 0).
    Ray ray(Vector(0.0, 8.0, 0.0), Vector(3.0, -4.0, 0.0));

    std::optional<HitInfo> hit = floor.hit(ray);

    REQUIRE(hit.has_value());
    REQUIRE(hit->t == 2.0);
    REQUIRE(hit->point.x() == 6.0);
    REQUIRE(hit->point.y() == 0.0);
    REQUIRE(hit->point.z() == 0.0);
    REQUIRE(hit->normal.x() == 0.0);
    REQUIRE(hit->normal.y() == 1.0);
    REQUIRE(hit->normal.z() == 0.0);

    // The material of the hit is the floor's: a flat shader gives green whatever the light.
    Light light(Vector(0.0, 10.0, 0.0), Colour(1.0, 1.0, 1.0));
    Colour colour = hit->material->shade(*hit, light);
    REQUIRE(colour.r() == 0.0);
    REQUIRE(colour.g() == 1.0);
    REQUIRE(colour.b() == 0.0);
}

TEST_CASE("A ray hits the plane of the line 3x + 4y = 24, with a unit normal", "[plane][hit]") {
    auto green = std::make_shared<FlatShader>(Colour(0.0, 1.0, 0.0));
    Plane plane(Vector(8.0, 0.0, 0.0), Vector(3.0, 4.0, 0.0), green);
    // n.(Q - O) = 48 and n.D = 24 (before normalising), so t = 2 and the hit is at (0, 6, 0).
    Ray ray(Vector(-8.0, 0.0, 0.0), Vector(4.0, 3.0, 0.0));

    std::optional<HitInfo> hit = plane.hit(ray);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(2.0, 1e-9));
    REQUIRE_THAT(hit->point.x(), WithinAbs(0.0, 1e-9));
    REQUIRE_THAT(hit->point.y(), WithinAbs(6.0, 1e-9));
    REQUIRE_THAT(hit->point.z(), WithinAbs(0.0, 1e-9));
    // (3, 4, 0) has length 5, so the normal is (3/5, 4/5, 0).
    REQUIRE_THAT(hit->normal.x(), WithinAbs(0.6, 1e-9));
    REQUIRE_THAT(hit->normal.y(), WithinAbs(0.8, 1e-9));
    REQUIRE_THAT(hit->normal.z(), WithinAbs(0.0, 1e-9));
}

TEST_CASE("A ray parallel to the floor misses it", "[plane][hit]") {
    auto green = std::make_shared<FlatShader>(Colour(0.0, 1.0, 0.0));
    Plane floor(Vector(0.0, 0.0, 0.0), Vector(0.0, 1.0, 0.0), green);
    // n.D = 0: the ray never gets closer to the floor.
    Ray ray(Vector(0.0, 8.0, 0.0), Vector(5.0, 0.0, 0.0));

    std::optional<HitInfo> hit = floor.hit(ray);

    REQUIRE_FALSE(hit.has_value());
}

TEST_CASE("A ray going up misses the floor behind it", "[plane][hit]") {
    auto green = std::make_shared<FlatShader>(Colour(0.0, 1.0, 0.0));
    Plane floor(Vector(0.0, 0.0, 0.0), Vector(0.0, 1.0, 0.0), green);
    // n.(Q - O) = -8 and n.D = 4, so t = -2: the floor is behind the ray.
    Ray ray(Vector(0.0, 8.0, 0.0), Vector(3.0, 4.0, 0.0));

    std::optional<HitInfo> hit = floor.hit(ray);

    REQUIRE_FALSE(hit.has_value());
}
