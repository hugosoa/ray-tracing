#include <catch2/catch_test_macros.hpp>

#include <memory>
#include <optional>

#include "scene/scene.hpp"
#include "geometry/hit_info.hpp"
#include "geometry/sphere.hpp"
#include "geometry/plane.hpp"
#include "math/vector.hpp"
#include "ray/ray.hpp"
#include "colour/colour.hpp"
#include "light/light.hpp"
#include "material/flat_shader.hpp"

// In every test: the ray leaves (0, 0, -1) along +Z, and a red sphere of radius 5 is centred at (0, 0, 9),
// so the ray meets it at z = 4, t = 5. The materials are flat, so the colour tells which shape was hit.

TEST_CASE("The nearest hit is the plane in front of the sphere, even when added second", "[scene][nearest]") {
    Light light(Vector(0.0, 0.0, -10.0), Colour(1.0, 1.0, 1.0));
    Scene scene(light);
    scene.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 9.0), 5.0, std::make_shared<FlatShader>(Colour(1.0, 0.0, 0.0))));
    // The plane z = 2 is met at t = 3, before the sphere.
    scene.add(std::make_unique<Plane>(Vector(0.0, 0.0, 2.0), Vector(0.0, 0.0, -1.0), std::make_shared<FlatShader>(Colour(0.0, 0.0, 1.0))));
    Ray ray(Vector(0.0, 0.0, -1.0), Vector(0.0, 0.0, 1.0));

    std::optional<HitInfo> hit = scene.nearestHit(ray);

    REQUIRE(hit.has_value());
    REQUIRE(hit->t == 3.0);
    Colour colour = hit->material->shade(*hit, light);
    REQUIRE(colour.getR() == 0.0);
    REQUIRE(colour.getG() == 0.0);
    REQUIRE(colour.getB() == 1.0);
}

TEST_CASE("The nearest hit is the sphere in front of the plane, even when added first", "[scene][nearest]") {
    Light light(Vector(0.0, 0.0, -10.0), Colour(1.0, 1.0, 1.0));
    Scene scene(light);
    scene.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 9.0), 5.0, std::make_shared<FlatShader>(Colour(1.0, 0.0, 0.0))));
    // The plane z = 20 is met at t = 21, after the sphere.
    scene.add(std::make_unique<Plane>(Vector(0.0, 0.0, 20.0), Vector(0.0, 0.0, -1.0), std::make_shared<FlatShader>(Colour(0.0, 0.0, 1.0))));
    Ray ray(Vector(0.0, 0.0, -1.0), Vector(0.0, 0.0, 1.0));

    std::optional<HitInfo> hit = scene.nearestHit(ray);

    REQUIRE(hit.has_value());
    REQUIRE(hit->t == 5.0);
    Colour colour = hit->material->shade(*hit, light);
    REQUIRE(colour.getR() == 1.0);
    REQUIRE(colour.getG() == 0.0);
    REQUIRE(colour.getB() == 0.0);
}

TEST_CASE("A ray that misses every shape gives no hit", "[scene][nearest]") {
    Light light(Vector(0.0, 0.0, -10.0), Colour(1.0, 1.0, 1.0));
    Scene scene(light);
    // Centred at x = 6 with radius 5: the ray along the Z axis passes 1 unit beside it.
    scene.add(std::make_unique<Sphere>(Vector(6.0, 0.0, 9.0), 5.0, std::make_shared<FlatShader>(Colour(1.0, 0.0, 0.0))));
    Ray ray(Vector(0.0, 0.0, -1.0), Vector(0.0, 0.0, 1.0));

    std::optional<HitInfo> hit = scene.nearestHit(ray);

    REQUIRE_FALSE(hit.has_value());
}
