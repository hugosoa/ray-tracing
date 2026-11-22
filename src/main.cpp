#include <iostream>
#include <memory>
#include "math/vector.hpp"
#include "geometry/sphere.hpp"
#include "geometry/plane.hpp"
#include "scene/scene.hpp"
#include "colour/colour.hpp"
#include "material/lambert_shader.hpp"
#include "light/light.hpp"
#include "camera/camera.hpp"
#include "image/image.hpp"
#include "io/png_saver.hpp"

int main() {
    std::cout << "Hello, Raytracer!\n";

    const int imageWidth = 512;
    const int imageHeight = 512;

    Camera camera(Vector(0, 0, -1), 2.0);

    // White light up, left and in front of the sphere.
    Light light(Vector(-10, 10, -5), Colour(1, 1, 1));
    Scene scene(light);

    // Yellow sphere: centre, radius and material.
    auto yellow = std::make_shared<LambertShader>(Colour(1, 1, 0));
    scene.add(std::make_unique<Sphere>(Vector(0, 0, 9), 5, yellow));

    // Grey floor, just under the sphere.
    auto grey = std::make_shared<LambertShader>(Colour(0.8, 0.8, 0.8));
    scene.add(std::make_unique<Plane>(Vector(0, -5, 0), Vector(0, 1, 0), grey));

    Image image = camera.render(scene, imageWidth, imageHeight);

    PngSaver saver = PngSaver();
    saver.save(image, "output.png");

    return 0;
}
