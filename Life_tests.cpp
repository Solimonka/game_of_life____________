#include <gtest/gtest.h>
#include "Life.cpp"

TEST(Life, DefaultConstructor) {
    ASSERT_NO_THROW(Life(3, 3));
}

TEST(Life, DefaultConstructorWithWrongParameters) {
    ASSERT_THROW(Life(2, 3), LifeException);
    ASSERT_THROW(Life(3, 2), LifeException);
    ASSERT_THROW(Life(2, 2), LifeException);
}