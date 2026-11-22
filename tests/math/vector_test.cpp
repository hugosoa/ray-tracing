#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include "math/vector.hpp"

// ---------- add ----------

TEST_CASE("Adding two vectors adds each component", "[vector][add]") {
    Vector a(1.0, 2.0, 3.0);
    Vector b(4.0, 5.0, 6.0);

    Vector result = a + b;

    REQUIRE(result.getX() == 5.0);
    REQUIRE(result.getY() == 7.0);
    REQUIRE(result.getZ() == 9.0);
}

TEST_CASE("Adding the zero vector gives the same vector", "[vector][add]") {
    Vector a(1.0, 2.0, 3.0);
    Vector zero(0.0, 0.0, 0.0);

    Vector result = a + zero;

    REQUIRE(result.getX() == 1.0);
    REQUIRE(result.getY() == 2.0);
    REQUIRE(result.getZ() == 3.0);
}

TEST_CASE("Adding works with negative components", "[vector][add]") {
    Vector a(1.0, -2.0, 3.0);
    Vector b(-4.0, 5.0, -6.0);

    Vector result = a + b;

    REQUIRE(result.getX() == -3.0);
    REQUIRE(result.getY() == 3.0);
    REQUIRE(result.getZ() == -3.0);
}

TEST_CASE("Adding works with decimal components", "[vector][add]") {
    Vector a(0.1, 0.2, 0.3);
    Vector b(0.2, 0.3, 0.4);

    Vector result = a + b;

    // Decimal numbers are not stored exactly, so we compare with Approx.
    REQUIRE(result.getX() == Catch::Approx(0.3));
    REQUIRE(result.getY() == Catch::Approx(0.5));
    REQUIRE(result.getZ() == Catch::Approx(0.7));
}

TEST_CASE("Adding does not change the original vectors", "[vector][add]") {
    Vector a(1.0, 2.0, 3.0);
    Vector b(4.0, 5.0, 6.0);

    a + b;

    REQUIRE(a.getX() == 1.0);
    REQUIRE(a.getY() == 2.0);
    REQUIRE(a.getZ() == 3.0);
    REQUIRE(b.getX() == 4.0);
    REQUIRE(b.getY() == 5.0);
    REQUIRE(b.getZ() == 6.0);
}

// ---------- subtract ----------

TEST_CASE("Subtracting two vectors subtracts each component", "[vector][subtract]") {
    Vector a(5.0, 7.0, 9.0);
    Vector b(1.0, 2.0, 3.0);

    Vector result = a - b;

    REQUIRE(result.getX() == 4.0);
    REQUIRE(result.getY() == 5.0);
    REQUIRE(result.getZ() == 6.0);
}

TEST_CASE("Subtracting (-5, 2, 1) from (-1, 4, 0) gives (4, 2, -1)", "[vector][subtract]") {
    Vector a(-1.0, 4.0, 0.0);
    Vector b(-5.0, 2.0, 1.0);

    Vector result = a - b;

    REQUIRE(result.getX() == 4.0);
    REQUIRE(result.getY() == 2.0);
    REQUIRE(result.getZ() == -1.0);
}

TEST_CASE("Subtracting a vector from itself gives the zero vector", "[vector][subtract]") {
    Vector a(1.0, 2.0, 3.0);

    Vector result = a - a;

    REQUIRE(result.getX() == 0.0);
    REQUIRE(result.getY() == 0.0);
    REQUIRE(result.getZ() == 0.0);
}

TEST_CASE("Subtracting can give negative components", "[vector][subtract]") {
    Vector a(1.0, 2.0, 3.0);
    Vector b(4.0, 5.0, 6.0);

    Vector result = a - b;

    REQUIRE(result.getX() == -3.0);
    REQUIRE(result.getY() == -3.0);
    REQUIRE(result.getZ() == -3.0);
}

TEST_CASE("Subtracting works with decimal components", "[vector][subtract]") {
    Vector a(0.5, 0.7, 0.9);
    Vector b(0.2, 0.3, 0.4);

    Vector result = a - b;

    REQUIRE(result.getX() == Catch::Approx(0.3));
    REQUIRE(result.getY() == Catch::Approx(0.4));
    REQUIRE(result.getZ() == Catch::Approx(0.5));
}

TEST_CASE("Subtracting is not the same as adding", "[vector][subtract]") {
    Vector a(1.0, 2.0, 3.0);
    Vector b(4.0, 5.0, 6.0);

    Vector result = a - b;

    REQUIRE(result.getX() != (a + b).getX());
}

// ---------- multiply by a number ----------

TEST_CASE("Multiplying a vector by a number multiplies each component", "[vector][multiply]") {
    Vector v(1.0, 2.0, 3.0);

    Vector result = v * 2;

    REQUIRE(result.getX() == 2.0);
    REQUIRE(result.getY() == 4.0);
    REQUIRE(result.getZ() == 6.0);
}

TEST_CASE("Multiplying a vector by 1 gives the same vector", "[vector][multiply]") {
    Vector v(1.0, -2.0, 3.0);

    Vector result = v * 1;

    REQUIRE(result.getX() == 1.0);
    REQUIRE(result.getY() == -2.0);
    REQUIRE(result.getZ() == 3.0);
}

TEST_CASE("Multiplying a vector by 0 gives the zero vector", "[vector][multiply]") {
    Vector v(1.0, 2.0, 3.0);

    Vector result = v * 0;

    REQUIRE(result.getX() == 0.0);
    REQUIRE(result.getY() == 0.0);
    REQUIRE(result.getZ() == 0.0);
}

TEST_CASE("Multiplying a vector by a negative number flips its direction", "[vector][multiply]") {
    Vector v(1.0, -2.0, 3.0);

    Vector result = v * -1;

    REQUIRE(result.getX() == -1.0);
    REQUIRE(result.getY() == 2.0);
    REQUIRE(result.getZ() == -3.0);
}

TEST_CASE("Multiplying a vector by a decimal number", "[vector][multiply]") {
    Vector v(1.0, 2.0, 3.0);

    Vector result = v * 0.5;

    REQUIRE(result.getX() == Catch::Approx(0.5));
    REQUIRE(result.getY() == Catch::Approx(1.0));
    REQUIRE(result.getZ() == Catch::Approx(1.5));
}

TEST_CASE("Multiplying does not change the original vector", "[vector][multiply]") {
    Vector v(1.0, 2.0, 3.0);

    v * 2;

    REQUIRE(v.getX() == 1.0);
    REQUIRE(v.getY() == 2.0);
    REQUIRE(v.getZ() == 3.0);
}

// ---------- constructor and getters ----------

TEST_CASE("A vector keeps the components it was created with", "[vector][constructor]") {
    Vector v(1.5, -2.0, 3.25);

    REQUIRE(v.getX() == 1.5);
    REQUIRE(v.getY() == -2.0);
    REQUIRE(v.getZ() == 3.25);
}

// ---------- number * vector ----------

TEST_CASE("Multiplying a number by a vector gives the same result as vector * number", "[vector][multiply]") {
    Vector v(1.0, -2.0, 3.0);

    Vector result = 2 * v;

    REQUIRE(result.getX() == 2.0);
    REQUIRE(result.getY() == -4.0);
    REQUIRE(result.getZ() == 6.0);
}

// ---------- dot ----------

TEST_CASE("The dot product multiplies components and adds them", "[vector][dot]") {
    Vector a(1.0, 2.0, 3.0);
    Vector b(4.0, -5.0, 6.0);

    // 1*4 + 2*(-5) + 3*6 = 12
    REQUIRE(a.dot(b) == 12.0);
}

TEST_CASE("The dot product of perpendicular vectors is 0", "[vector][dot]") {
    Vector a(1.0, 0.0, 0.0);
    Vector b(0.0, 1.0, 0.0);

    REQUIRE(a.dot(b) == 0.0);
}

TEST_CASE("The dot product does not depend on the order", "[vector][dot]") {
    Vector a(1.0, 2.0, 3.0);
    Vector b(4.0, -5.0, 6.0);

    REQUIRE(a.dot(b) == b.dot(a));
}

// ---------- length ----------

TEST_CASE("The length of (3, 4, 0) is 5", "[vector][length]") {
    Vector v(3.0, 4.0, 0.0);

    REQUIRE(v.length() == Catch::Approx(5.0));
}

TEST_CASE("The length of the zero vector is 0", "[vector][length]") {
    Vector v(0.0, 0.0, 0.0);

    REQUIRE(v.length() == 0.0);
}

TEST_CASE("The length is never negative", "[vector][length]") {
    Vector v(-3.0, -4.0, 0.0);

    REQUIRE(v.length() == Catch::Approx(5.0));
}

// ---------- normalised ----------

TEST_CASE("A normalised vector has length 1", "[vector][normalised]") {
    Vector v(1.0, 2.0, 3.0);

    REQUIRE(v.normalised().length() == Catch::Approx(1.0));
}

TEST_CASE("A normalised vector keeps the same direction", "[vector][normalised]") {
    Vector v(0.0, 0.0, 5.0);

    Vector result = v.normalised();

    REQUIRE(result.getX() == Catch::Approx(0.0));
    REQUIRE(result.getY() == Catch::Approx(0.0));
    REQUIRE(result.getZ() == Catch::Approx(1.0));
}
