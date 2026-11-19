#include <iostream>
#include <math/vector.hpp>
#include <geometry/sphere.hpp>
#include <colour/colour.hpp>
#include <camera/camera.hpp>
#include <image/image.hpp>
#include <io/png_saver.hpp>

int main() {
    std::cout << "Hello, Raytracer!\n";

    const int imageWidth = 512;
    const int imageHeight = 512;

    Camera camera(Vector(0, 0, -1), 2.0);

    // Sphere, centre, rayon et couleur
    Sphere sphere(Vector(0, 0, 9), 5, Colour(1, 0, 0));

    Image image = camera.render(sphere, imageWidth, imageHeight);

    PngSaver saver = PngSaver();
    saver.save(image, "output.png");

    return 0;
}
