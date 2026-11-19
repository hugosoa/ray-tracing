#include <catch2/catch_test_macros.hpp>

#include "material/flat_shader.hpp"
#include "material/material.hpp"
#include "geometry/hit_info.hpp"
#include "light/light.hpp"
#include "math/vector.hpp"
#include "colour/colour.hpp"

TEST_CASE("A flat shader shades with the colour it was created with", "[material][flat]") {
    FlatShader shader(Colour(0.25, 0.5, 0.75));
    HitInfo hit{Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, -1.0), &shader};
    Light light(Vector(0.0, 0.0, -10.0), Colour(1.0, 1.0, 1.0));

    Colour colour = shader.shade(hit, light);

    REQUIRE(colour.r() == 0.25);
    REQUIRE(colour.g() == 0.5);
    REQUIRE(colour.b() == 0.75);
}

TEST_CASE("A flat shader ignores the light", "[material][flat]") {
    FlatShader shader(Colour(0.25, 0.5, 0.75));
    HitInfo hit{Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, -1.0), &shader};
    // Light behind the surface, with a colour that would change the result if it were used.
    Light light(Vector(0.0, 0.0, 10.0), Colour(0.0, 0.5, 0.0));

    Colour colour = shader.shade(hit, light);

    REQUIRE(colour.r() == 0.25);
    REQUIRE(colour.g() == 0.5);
    REQUIRE(colour.b() == 0.75);
}

TEST_CASE("A flat shader can be used through a Material reference", "[material][flat]") {
    FlatShader shader(Colour(0.0, 1.0, 0.0));
    const Material& material = shader;
    HitInfo hit{Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, -1.0), &shader};
    Light light(Vector(0.0, 0.0, -10.0), Colour(1.0, 1.0, 1.0));

    Colour colour = material.shade(hit, light);

    REQUIRE(colour.r() == 0.0);
    REQUIRE(colour.g() == 1.0);
    REQUIRE(colour.b() == 0.0);
}
