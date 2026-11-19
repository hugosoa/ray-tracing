#include <iostream>
#include <memory>
#include <math/vector.hpp>
#include <geometry/sphere.hpp>
#include <colour/colour.hpp>
#include <material/lambert_shader.hpp>
#include <light/light.hpp>
#include <camera/camera.hpp>
#include <image/image.hpp>
#include <io/png_saver.hpp>

int main() {
    std::cout << "Hello, Raytracer!\n";

    const int imageWidth = 512;
    const int imageHeight = 512;

    Camera camera(Vector(0, 0, -1), 2.0);

    // Sphere, centre, rayon et materiau
    auto yellow = std::make_shared<LambertShader>(Colour(1, 1, 0));
    Sphere sphere(Vector(0, 0, 9), 5, yellow);

    // White light up, left and in front of the sphere.
    Light light(Vector(-10, 10, -5), Colour(1, 1, 1));

    Image image = camera.render(sphere, light, imageWidth, imageHeight);

    PngSaver saver = PngSaver();
    saver.save(image, "output.png");

    return 0;
}
