#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include <memory>
#include <optional>

#include "geometry/sphere.hpp"
#include "geometry/hit_info.hpp"
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

    REQUIRE(sphere.hit(ray).has_value());
}

TEST_CASE("A ray passing beside the sphere misses it", "[sphere][hit]") {
    Sphere sphere(Vector(0.0, 0.0, 0.0), 1.0, std::make_shared<FlatShader>(Colour(1.0, 0.0, 0.0)));
    Ray ray(Vector(5.0, 0.0, -10.0), Vector(0.0, 0.0, 1.0));

    REQUIRE_FALSE(sphere.hit(ray).has_value());
}

TEST_CASE("A ray pointing away from the sphere misses it", "[sphere][hit]") {
    Sphere sphere(Vector(0.0, 0.0, 0.0), 1.0, std::make_shared<FlatShader>(Colour(1.0, 0.0, 0.0)));
    // The sphere is behind the ray.
    Ray ray(Vector(0.0, 0.0, 10.0), Vector(0.0, 0.0, 1.0));

    REQUIRE_FALSE(sphere.hit(ray).has_value());
}

TEST_CASE("A ray starting inside the sphere hits it", "[sphere][hit]") {
    Sphere sphere(Vector(0.0, 0.0, 0.0), 5.0, std::make_shared<FlatShader>(Colour(1.0, 0.0, 0.0)));
    Ray ray(Vector(1.0, 1.0, 1.0), Vector(0.0, 0.0, 1.0));

    REQUIRE(sphere.hit(ray).has_value());
}

TEST_CASE("A ray touching the edge of the sphere hits it", "[sphere][hit]") {
    Sphere sphere(Vector(0.0, 0.0, 0.0), 1.0, std::make_shared<FlatShader>(Colour(1.0, 0.0, 0.0)));
    // Passes exactly at x = 1, the edge of the sphere.
    Ray ray(Vector(1.0, 0.0, -10.0), Vector(0.0, 0.0, 1.0));

    REQUIRE(sphere.hit(ray).has_value());
}

TEST_CASE("A ray with a non-unit direction still hits the sphere", "[sphere][hit]") {
    Sphere sphere(Vector(0.0, 0.0, 0.0), 1.0, std::make_shared<FlatShader>(Colour(1.0, 0.0, 0.0)));
    Ray ray(Vector(0.0, 0.0, -10.0), Vector(0.0, 0.0, 7.0));

    REQUIRE(sphere.hit(ray).has_value());
}

// ---------- hit info ----------
// Unit sphere at the origin, ray coming from z = -10 along +Z: it enters the sphere at (0, 0, -1).

TEST_CASE("The hit point is where the ray enters the sphere", "[sphere][hit][hitinfo]") {
    Sphere sphere(Vector(0.0, 0.0, 0.0), 1.0, std::make_shared<FlatShader>(Colour(1.0, 0.0, 0.0)));
    Ray ray(Vector(0.0, 0.0, -10.0), Vector(0.0, 0.0, 1.0));

    std::optional<HitInfo> hit = sphere.hit(ray);

    REQUIRE(hit.has_value());
    REQUIRE(hit->point.x() == 0.0);
    REQUIRE(hit->point.y() == 0.0);
    REQUIRE(hit->point.z() == -1.0);
}

TEST_CASE("The hit point does not depend on the length of the ray direction", "[sphere][hit][hitinfo]") {
    Sphere sphere(Vector(0.0, 0.0, 0.0), 1.0, std::make_shared<FlatShader>(Colour(1.0, 0.0, 0.0)));
    Ray ray(Vector(0.0, 0.0, -10.0), Vector(0.0, 0.0, 7.0));

    std::optional<HitInfo> hit = sphere.hit(ray);

    REQUIRE(hit.has_value());
    REQUIRE(hit->point.x() == 0.0);
    REQUIRE(hit->point.y() == 0.0);
    REQUIRE(hit->point.z() == Catch::Approx(-1.0));
}

TEST_CASE("A ray starting inside the sphere hits it where it leaves", "[sphere][hit][hitinfo]") {
    Sphere sphere(Vector(0.0, 0.0, 0.0), 5.0, std::make_shared<FlatShader>(Colour(1.0, 0.0, 0.0)));
    Ray ray(Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, 1.0));

    std::optional<HitInfo> hit = sphere.hit(ray);

    // The entry point (t = -5) is behind the ray, so the closest non negative t is the exit point.
    REQUIRE(hit.has_value());
    REQUIRE(hit->point.z() == 5.0);
}

TEST_CASE("The normal points from the centre of the sphere to the hit point", "[sphere][hit][hitinfo]") {
    Sphere sphere(Vector(0.0, 0.0, 0.0), 1.0, std::make_shared<FlatShader>(Colour(1.0, 0.0, 0.0)));
    Ray ray(Vector(0.0, 0.0, -10.0), Vector(0.0, 0.0, 1.0));

    std::optional<HitInfo> hit = sphere.hit(ray);

    REQUIRE(hit.has_value());
    REQUIRE(hit->normal.x() == 0.0);
    REQUIRE(hit->normal.y() == 0.0);
    REQUIRE(hit->normal.z() == -1.0);
}

TEST_CASE("The normal has length 1 even on a big sphere", "[sphere][hit][hitinfo]") {
    Sphere sphere(Vector(1.0, 2.0, 3.0), 5.0, std::make_shared<FlatShader>(Colour(1.0, 0.0, 0.0)));
    // Comes from the left and hits the sphere at (-4, 2, 3).
    Ray ray(Vector(-10.0, 2.0, 3.0), Vector(1.0, 0.0, 0.0));

    std::optional<HitInfo> hit = sphere.hit(ray);

    REQUIRE(hit.has_value());
    REQUIRE(hit->normal.x() == Catch::Approx(-1.0));
    REQUIRE(hit->normal.y() == Catch::Approx(0.0));
    REQUIRE(hit->normal.z() == Catch::Approx(0.0));
    REQUIRE(hit->normal.length() == Catch::Approx(1.0));
}

TEST_CASE("The hit info carries the material of the sphere", "[sphere][hit][hitinfo]") {
    auto material = std::make_shared<FlatShader>(Colour(0.25, 0.5, 0.75));
    Sphere sphere(Vector(0.0, 0.0, 0.0), 1.0, material);
    Ray ray(Vector(0.0, 0.0, -10.0), Vector(0.0, 0.0, 1.0));

    std::optional<HitInfo> hit = sphere.hit(ray);

    REQUIRE(hit.has_value());
    REQUIRE(hit->material == material.get());
}
