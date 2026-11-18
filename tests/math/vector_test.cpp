#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include "math/vector.hpp"

// ---------- add ----------

TEST_CASE("Adding two vectors adds each component", "[vector][add]") {
    Vector a(1.0, 2.0, 3.0);
    Vector b(4.0, 5.0, 6.0);

    Vector result = a + b;

    REQUIRE(result.x() == 5.0);
    REQUIRE(result.y() == 7.0);
    REQUIRE(result.z() == 9.0);
}

TEST_CASE("Adding the zero vector gives the same vector", "[vector][add]") {
    Vector a(1.0, 2.0, 3.0);
    Vector zero(0.0, 0.0, 0.0);

    Vector result = a + zero;

    REQUIRE(result.x() == 1.0);
    REQUIRE(result.y() == 2.0);
    REQUIRE(result.z() == 3.0);
}

TEST_CASE("Adding works with negative components", "[vector][add]") {
    Vector a(1.0, -2.0, 3.0);
    Vector b(-4.0, 5.0, -6.0);

    Vector result = a + b;

    REQUIRE(result.x() == -3.0);
    REQUIRE(result.y() == 3.0);
    REQUIRE(result.z() == -3.0);
}

TEST_CASE("Adding works with decimal components", "[vector][add]") {
    Vector a(0.1, 0.2, 0.3);
    Vector b(0.2, 0.3, 0.4);

    Vector result = a + b;

    // Decimal numbers are not stored exactly, so we compare with Approx.
    REQUIRE(result.x() == Catch::Approx(0.3));
    REQUIRE(result.y() == Catch::Approx(0.5));
    REQUIRE(result.z() == Catch::Approx(0.7));
}

TEST_CASE("Adding does not change the original vectors", "[vector][add]") {
    Vector a(1.0, 2.0, 3.0);
    Vector b(4.0, 5.0, 6.0);

    a + b;

    REQUIRE(a.x() == 1.0);
    REQUIRE(a.y() == 2.0);
    REQUIRE(a.z() == 3.0);
    REQUIRE(b.x() == 4.0);
    REQUIRE(b.y() == 5.0);
    REQUIRE(b.z() == 6.0);
}

// ---------- subtract ----------

TEST_CASE("Subtracting two vectors subtracts each component", "[vector][subtract]") {
    Vector a(5.0, 7.0, 9.0);
    Vector b(1.0, 2.0, 3.0);

    Vector result = a - b;

    REQUIRE(result.x() == 4.0);
    REQUIRE(result.y() == 5.0);
    REQUIRE(result.z() == 6.0);
}

TEST_CASE("Subtracting (-5, 2, 1) from (-1, 4, 0) gives (4, 2, -1)", "[vector][subtract]") {
    Vector a(-1.0, 4.0, 0.0);
    Vector b(-5.0, 2.0, 1.0);

    Vector result = a - b;

    REQUIRE(result.x() == 4.0);
    REQUIRE(result.y() == 2.0);
    REQUIRE(result.z() == -1.0);
}

TEST_CASE("Subtracting a vector from itself gives the zero vector", "[vector][subtract]") {
    Vector a(1.0, 2.0, 3.0);

    Vector result = a - a;

    REQUIRE(result.x() == 0.0);
    REQUIRE(result.y() == 0.0);
    REQUIRE(result.z() == 0.0);
}

TEST_CASE("Subtracting can give negative components", "[vector][subtract]") {
    Vector a(1.0, 2.0, 3.0);
    Vector b(4.0, 5.0, 6.0);

    Vector result = a - b;

    REQUIRE(result.x() == -3.0);
    REQUIRE(result.y() == -3.0);
    REQUIRE(result.z() == -3.0);
}

TEST_CASE("Subtracting works with decimal components", "[vector][subtract]") {
    Vector a(0.5, 0.7, 0.9);
    Vector b(0.2, 0.3, 0.4);

    Vector result = a - b;

    REQUIRE(result.x() == Catch::Approx(0.3));
    REQUIRE(result.y() == Catch::Approx(0.4));
    REQUIRE(result.z() == Catch::Approx(0.5));
}

TEST_CASE("Subtracting is not the same as adding", "[vector][subtract]") {
    Vector a(1.0, 2.0, 3.0);
    Vector b(4.0, 5.0, 6.0);

    Vector result = a - b;

    REQUIRE(result.x() != (a + b).x());
}

// ---------- multiply by a number ----------

TEST_CASE("Multiplying a vector by a number multiplies each component", "[vector][multiply]") {
    Vector v(1.0, 2.0, 3.0);

    Vector result = v * 2;

    REQUIRE(result.x() == 2.0);
    REQUIRE(result.y() == 4.0);
    REQUIRE(result.z() == 6.0);
}

TEST_CASE("Multiplying a vector by 1 gives the same vector", "[vector][multiply]") {
    Vector v(1.0, -2.0, 3.0);

    Vector result = v * 1;

    REQUIRE(result.x() == 1.0);
    REQUIRE(result.y() == -2.0);
    REQUIRE(result.z() == 3.0);
}

TEST_CASE("Multiplying a vector by 0 gives the zero vector", "[vector][multiply]") {
    Vector v(1.0, 2.0, 3.0);

    Vector result = v * 0;

    REQUIRE(result.x() == 0.0);
    REQUIRE(result.y() == 0.0);
    REQUIRE(result.z() == 0.0);
}

TEST_CASE("Multiplying a vector by a negative number flips its direction", "[vector][multiply]") {
    Vector v(1.0, -2.0, 3.0);

    Vector result = v * -1;

    REQUIRE(result.x() == -1.0);
    REQUIRE(result.y() == 2.0);
    REQUIRE(result.z() == -3.0);
}

TEST_CASE("Multiplying a vector by a decimal number", "[vector][multiply]") {
    Vector v(1.0, 2.0, 3.0);

    Vector result = v * 0.5;

    REQUIRE(result.x() == Catch::Approx(0.5));
    REQUIRE(result.y() == Catch::Approx(1.0));
    REQUIRE(result.z() == Catch::Approx(1.5));
}

TEST_CASE("Multiplying does not change the original vector", "[vector][multiply]") {
    Vector v(1.0, 2.0, 3.0);

    v * 2;

    REQUIRE(v.x() == 1.0);
    REQUIRE(v.y() == 2.0);
    REQUIRE(v.z() == 3.0);
}
