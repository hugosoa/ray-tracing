#include <iostream>

#include "greeting.hpp"

int main(int argc, char* argv[]) {
    const char* name = argc > 1 ? argv[1] : "";
    std::cout << raytracer::greet(name) << '\n';
    return 0;
}
