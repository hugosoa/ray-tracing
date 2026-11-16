#pragma once

#include <string>
#include <string_view>

namespace raytracer {

/// Returns "Hello, <name>!", or "Hello, World!" when the name is empty.
std::string greet(std::string_view name);

} // namespace raytracer
