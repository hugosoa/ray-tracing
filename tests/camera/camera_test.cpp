#include <catch2/catch_test_macros.hpp>

#include <memory>

#include "camera/camera.hpp"
#include "math/vector.hpp"
#include "ray/ray.hpp"
#include "geometry/sphere.hpp"
#include "colour/colour.hpp"
#include "material/flat_shader.hpp"
#include "material/lambert_shader.hpp"
#include "light/light.hpp"
#include "scene/scene.hpp"
#include "image/image.hpp"

// ---------- constructor and getters ----------

TEST_CASE("A camera keeps the position it was created with", "[camera][constructor]") {
    Camera camera(Vector(1.0, 2.0, 3.0));

    REQUIRE(camera.position().x() == 1.0);
    REQUIRE(camera.position().y() == 2.0);
    REQUIRE(camera.position().z() == 3.0);
}

// ---------- rayThroughCenter ----------

TEST_CASE("The center ray starts at the camera position", "[camera][ray]") {
    Camera camera(Vector(1.0, 2.0, 3.0));

    Ray ray = camera.rayThroughCenter();

    REQUIRE(ray.getOrigin().x() == 1.0);
    REQUIRE(ray.getOrigin().y() == 2.0);
    REQUIRE(ray.getOrigin().z() == 3.0);
}

TEST_CASE("The center ray points along +Z", "[camera][ray]") {
    Camera camera(Vector(1.0, 2.0, 3.0));

    Ray ray = camera.rayThroughCenter();

    REQUIRE(ray.getDirection().x() == 0.0);
    REQUIRE(ray.getDirection().y() == 0.0);
    REQUIRE(ray.getDirection().z() == 1.0);
}

// ---------- rayThroughPixel ----------
// Camera at (0, 0, -1), screen at z = 0, 5 units wide.
// Image of 5 columns x 3 rows, so each pixel is 1 unit wide.

TEST_CASE("The ray through the center pixel points along +Z", "[camera][ray][pixel]") {
    Camera camera(Vector(0.0, 0.0, -1.0), 5.0);

    Ray ray = camera.rayThroughPixel(2, 1, 5, 3);

    REQUIRE(ray.getDirection().x() == 0.0);
    REQUIRE(ray.getDirection().y() == 0.0);
    REQUIRE(ray.getDirection().z() == 1.0);
}

TEST_CASE("The ray through the top right pixel points up and right", "[camera][ray][pixel]") {
    Camera camera(Vector(0.0, 0.0, -1.0), 5.0);

    Ray ray = camera.rayThroughPixel(4, 0, 5, 3);

    REQUIRE(ray.getDirection().x() == 2.0);
    REQUIRE(ray.getDirection().y() == 1.0);
    REQUIRE(ray.getDirection().z() == 1.0);
}

TEST_CASE("The ray through the bottom left pixel points down and left", "[camera][ray][pixel]") {
    Camera camera(Vector(0.0, 0.0, -1.0), 5.0);

    Ray ray = camera.rayThroughPixel(0, 2, 5, 3);

    REQUIRE(ray.getDirection().x() == -2.0);
    REQUIRE(ray.getDirection().y() == -1.0);
    REQUIRE(ray.getDirection().z() == 1.0);
}

TEST_CASE("The ray through a pixel starts at the camera position", "[camera][ray][pixel]") {
    Camera camera(Vector(0.0, 0.0, -1.0), 5.0);

    Ray ray = camera.rayThroughPixel(4, 0, 5, 3);

    REQUIRE(ray.getOrigin().x() == 0.0);
    REQUIRE(ray.getOrigin().y() == 0.0);
    REQUIRE(ray.getOrigin().z() == -1.0);
}

// Camera at (0, 0, -1), screen at z = 0, 2 units wide.
// Image of 512 x 256, so each pixel is 2 / 512 = 1/256 unit wide and the screen is 1 unit high.
// All the values below are multiples of 1/512, so they are exact in double.

TEST_CASE("With a 2 unit screen and a 512 x 256 image, the corner rays go through the corner pixel centres", "[camera][ray][pixel]") {
    Camera camera(Vector(0.0, 0.0, -1.0), 2.0);

    // Top-left pixel centre: x = (0.5 - 256) / 256, y = (128 - 0.5) / 256.
    Ray topLeft = camera.rayThroughPixel(0, 0, 512, 256);
    REQUIRE(topLeft.getDirection().x() == -0.998046875);
    REQUIRE(topLeft.getDirection().y() == 0.498046875);
    REQUIRE(topLeft.getDirection().z() == 1.0);

    // Bottom-right pixel centre: x = (511.5 - 256) / 256, y = (128 - 255.5) / 256.
    Ray bottomRight = camera.rayThroughPixel(511, 255, 512, 256);
    REQUIRE(bottomRight.getDirection().x() == 0.998046875);
    REQUIRE(bottomRight.getDirection().y() == -0.498046875);
    REQUIRE(bottomRight.getDirection().z() == 1.0);
}

// ---------- trace ----------
// Camera at (0, 0, -1), a scene with a sphere of radius 1 centred at (0, 0, 5), white light next to the camera.

TEST_CASE("Tracing a ray that hits the sphere gives the sphere's colour", "[camera][trace]") {
    Camera camera(Vector(0.0, 0.0, -1.0));
    Light light(Vector(0.0, 0.0, -1.0), Colour(1.0, 1.0, 1.0));
    Scene scene(light);
    scene.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 5.0), 1.0, std::make_shared<FlatShader>(Colour(0.0, 1.0, 0.0))));
    Ray ray(Vector(0.0, 0.0, -1.0), Vector(0.0, 0.0, 1.0));

    Colour colour = camera.trace(ray, scene);

    REQUIRE(colour.r() == 0.0);
    REQUIRE(colour.g() == 1.0);
    REQUIRE(colour.b() == 0.0);
}

TEST_CASE("Tracing a ray with a Lambert sphere lit from the side darkens the colour", "[camera][trace]") {
    Camera camera(Vector(0.0, 0.0, -1.0));
    Light light(Vector(10.0, 0.0, 4.0), Colour(1.0, 1.0, 1.0));
    Scene scene(light);
    scene.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 5.0), 1.0, std::make_shared<LambertShader>(Colour(1.0, 1.0, 1.0))));
    // The ray hits the sphere at (0, 0, 4), where the normal is (0, 0, -1).
    // The light is perpendicular to that normal, so the point is not lit.
    Ray ray(Vector(0.0, 0.0, -1.0), Vector(0.0, 0.0, 1.0));

    Colour colour = camera.trace(ray, scene);

    REQUIRE(colour.r() == 0.0);
    REQUIRE(colour.g() == 0.0);
    REQUIRE(colour.b() == 0.0);
}

TEST_CASE("Tracing a ray that misses the sphere gives black", "[camera][trace]") {
    Camera camera(Vector(0.0, 0.0, -1.0));
    Light light(Vector(0.0, 0.0, -1.0), Colour(1.0, 1.0, 1.0));
    Scene scene(light);
    scene.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 5.0), 1.0, std::make_shared<FlatShader>(Colour(1.0, 0.0, 0.0))));
    Ray ray(Vector(0.0, 0.0, -1.0), Vector(0.0, 1.0, 0.0));

    Colour colour = camera.trace(ray, scene);

    REQUIRE(colour.r() == 0.0);
    REQUIRE(colour.g() == 0.0);
    REQUIRE(colour.b() == 0.0);
}

// ---------- render ----------

TEST_CASE("Rendering gives an image of the requested size", "[camera][render]") {
    Camera camera(Vector(0.0, 0.0, -1.0), 2.0);
    Light light(Vector(0.0, 0.0, -1.0), Colour(1.0, 1.0, 1.0));
    Scene scene(light);
    scene.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 5.0), 1.0, std::make_shared<FlatShader>(Colour(1.0, 0.0, 0.0))));

    Image image = camera.render(scene, 4, 3);

    REQUIRE(image.width() == 4);
    REQUIRE(image.height() == 3);
}

TEST_CASE("Rendering a sphere in front of the camera colours the centre red and the corners black", "[camera][render]") {
    Camera camera(Vector(0.0, 0.0, -1.0), 2.0);
    Light light(Vector(0.0, 0.0, -1.0), Colour(1.0, 1.0, 1.0));
    Scene scene(light);
    scene.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 5.0), 1.0, std::make_shared<FlatShader>(Colour(1.0, 0.0, 0.0))));

    Image image = camera.render(scene, 5, 5);

    REQUIRE(image.pixel(2, 2).r() == 1.0);
    REQUIRE(image.pixel(0, 0).r() == 0.0);
    REQUIRE(image.pixel(4, 4).r() == 0.0);
}
