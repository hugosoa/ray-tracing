#include <gtest/gtest.h>

#include "greeting.hpp"

TEST(Greet, GreetsTheGivenName) {
    EXPECT_EQ(raytracer::greet("Alice"), "Hello, Alice!");
}

TEST(Greet, GreetsTheWorldWhenNameIsEmpty) {
    EXPECT_EQ(raytracer::greet(""), "Hello, World!");
}
