#include <gtest/gtest.h>
#include "Life.h"

TEST(Life, DefaultConstructor) {
    ASSERT_NO_THROW(Life(3, 3));
    ASSERT_THROW(Life(2, 3), LifeException);
    ASSERT_THROW(Life(3, 2), LifeException);
    ASSERT_THROW(Life(2, 2), LifeException);
}

TEST(Life, Getters) {
    Life game(3, 4);
    ASSERT_EQ(game.getHeight(), 4);
    ASSERT_EQ(game.getWidth(), 3);
    ASSERT_EQ(game.getCellStates().size(), 12);
    for (int i = 0; i < 12; ++i) {
        ASSERT_FALSE(game.getCellStates()[i]);
    }
//    for(auto cellState: game.getCellStates()){
//        ASSERT_FALSE(cellState);
//    }
}

TEST(Life, Setters) {
    Life game(3, 4);
    game.setCellAlive(0, 0);
    game.setCellDeda(1, 2);
    ASSERT_TRUE(game.getCellStates()[0]);
    ASSERT_FALSE(game.getCellStates()[7]);
    ASSERT_THROW(game.setCellAlive(4, 0), LifeException);
}

