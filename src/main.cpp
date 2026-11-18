#include <iostream>
#include <math/vector.hpp>
#include <ray/ray.hpp>
#include <geometry/sphere.hpp>

int main() {
    std::cout << "Hello, Raytracer!\n";

    Ray ray(Vector(0, 0, -1), Vector(0, 0, 1));

    Sphere sphere(Vector(0, 0, 9), 5 );
    
    bool hit = sphere.hit(ray);
    if (hit) {
        std::cout << "Ray hit the sphere!\n";
    } else {
        std::cout << "Ray missed the sphere.\n";
    }

    return 0;
}
