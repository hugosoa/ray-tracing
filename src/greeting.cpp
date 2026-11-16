#include "greeting.hpp"

namespace raytracer {

std::string greet(std::string_view name) {
    if (name.empty()) {
        name = "World";
    }
    return "Hello, " + std::string(name) + "!";
}

} // namespace raytracer
