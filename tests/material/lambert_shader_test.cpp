#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <cmath>

#include "material/lambert_shader.hpp"
#include "material/material.hpp"
#include "geometry/hit_info.hpp"
#include "light/light.hpp"
#include "math/vector.hpp"
#include "colour/colour.hpp"

using Catch::Matchers::WithinAbs;

// In every test, the surface is hit at the origin and its normal points towards -Z.

TEST_CASE("A Lambert shader gives the full colour when the light is straight along the normal", "[material][lambert]") {
    LambertShader shader(Colour(0.25, 0.5, 0.75));
    HitInfo hit{1.0, Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, -1.0), &shader};
    Light light(Vector(0.0, 0.0, -10.0), Colour(1.0, 1.0, 1.0));

    Colour colour = shader.shade(hit, light);

    REQUIRE(colour.getR() == 0.25);
    REQUIRE(colour.getG() == 0.5);
    REQUIRE(colour.getB() == 0.75);
}

TEST_CASE("A Lambert shader scales the colour by the cosine of the angle to the light", "[material][lambert]") {
    LambertShader shader(Colour(1.0, 1.0, 1.0));
    HitInfo hit{1.0, Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, -1.0), &shader};
    // Light at 60 degrees from the normal: cos(60) = 0.5.
    Light light(Vector(std::sqrt(3.0), 0.0, -1.0), Colour(1.0, 1.0, 1.0));

    Colour colour = shader.shade(hit, light);

    REQUIRE_THAT(colour.getR(), WithinAbs(0.5, 1e-12));
    REQUIRE_THAT(colour.getG(), WithinAbs(0.5, 1e-12));
    REQUIRE_THAT(colour.getB(), WithinAbs(0.5, 1e-12));
}

TEST_CASE("A Lambert shader gives black when the light grazes the surface", "[material][lambert]") {
    LambertShader shader(Colour(1.0, 1.0, 1.0));
    HitInfo hit{1.0, Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, -1.0), &shader};
    Light light(Vector(10.0, 0.0, 0.0), Colour(1.0, 1.0, 1.0));

    Colour colour = shader.shade(hit, light);

    REQUIRE(colour.getR() == 0.0);
    REQUIRE(colour.getG() == 0.0);
    REQUIRE(colour.getB() == 0.0);
}

TEST_CASE("A Lambert shader gives black when the light is behind the surface", "[material][lambert]") {
    LambertShader shader(Colour(1.0, 1.0, 1.0));
    HitInfo hit{1.0, Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, -1.0), &shader};
    Light light(Vector(0.0, 0.0, 10.0), Colour(1.0, 1.0, 1.0));

    Colour colour = shader.shade(hit, light);

    REQUIRE(colour.getR() == 0.0);
    REQUIRE(colour.getG() == 0.0);
    REQUIRE(colour.getB() == 0.0);
}

TEST_CASE("A Lambert shader does not depend on the distance to the light", "[material][lambert]") {
    LambertShader shader(Colour(1.0, 0.5, 0.25));
    HitInfo hit{1.0, Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, -1.0), &shader};
    Light nearLight(Vector(0.0, 0.0, -1.0), Colour(1.0, 1.0, 1.0));
    Light farLight(Vector(0.0, 0.0, -1000.0), Colour(1.0, 1.0, 1.0));

    Colour nearColour = shader.shade(hit, nearLight);
    Colour farColour = shader.shade(hit, farLight);

    REQUIRE(nearColour.getR() == farColour.getR());
    REQUIRE(nearColour.getG() == farColour.getG());
    REQUIRE(nearColour.getB() == farColour.getB());
}

TEST_CASE("A Lambert shader multiplies the surface colour by the light colour", "[material][lambert]") {
    LambertShader shader(Colour(1.0, 0.5, 1.0));
    HitInfo hit{1.0, Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, -1.0), &shader};
    Light light(Vector(0.0, 0.0, -10.0), Colour(0.5, 1.0, 0.0));

    Colour colour = shader.shade(hit, light);

    REQUIRE(colour.getR() == 0.5);
    REQUIRE(colour.getG() == 0.5);
    REQUIRE(colour.getB() == 0.0);
}

TEST_CASE("A Lambert shader can be used through a Material reference", "[material][lambert]") {
    LambertShader shader(Colour(0.0, 1.0, 0.0));
    const Material& material = shader;
    HitInfo hit{1.0, Vector(0.0, 0.0, 0.0), Vector(0.0, 0.0, -1.0), &shader};
    Light light(Vector(0.0, 0.0, -10.0), Colour(1.0, 1.0, 1.0));

    Colour colour = material.shade(hit, light);

    REQUIRE(colour.getR() == 0.0);
    REQUIRE(colour.getG() == 1.0);
    REQUIRE(colour.getB() == 0.0);
}
