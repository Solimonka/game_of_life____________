#include <gtest/gtest.h>
#include "../life_backend/include/Life.h"
using life_backend::Life;
using life_backend::LifeException;


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

TEST(Life, GetCellState) {
    Life game(3, 4);
    game.setCellAlive(0, 0);
    game.setCellDeda(1, 2);
    ASSERT_TRUE(game.getCellState(0, 0));
    ASSERT_FALSE(game.getCellState(1, 2));
    ASSERT_THROW(game.getCellState(4, 0), LifeException);
}

TEST(Life, CountNeighbours) {
    Life game(3, 4);
    game.setCellAlive(0, 0);
    game.setCellAlive(1, 2);
    game.setCellAlive(2, 2);
    ASSERT_EQ(game.getAliveNeighboursCount(0, 0), 0);   /// + - -
    ASSERT_EQ(game.getAliveNeighboursCount(2, 3), 3);   /// - - -
    ASSERT_EQ(game.getAliveNeighboursCount(2, 2), 1);   /// - + +
    ASSERT_EQ(game.getAliveNeighboursCount(1, 1), 3);   /// - - -
    ASSERT_THROW(game.getAliveNeighboursCount(3, 3), LifeException);
}

TEST(Life, OperatorOstream) {
    Life game(3, 4);
    game.setCellAlive(0, 0);
    game.setCellAlive(1, 2);
    game.setCellAlive(2, 2);
//    std::cout << game;
//    std::stringstream ss;
//    ss << game;
    std::cout << game.string() << std::endl;
}

//TEST(Life, Play) {
//    Life game(30, 20);
////    game.fillRandomStates();
//    game.setCellAlive(0, 1);
//    game.setCellAlive(1, 2);
//    game.setCellAlive(2, 0);
//    game.setCellAlive(2, 1);
//    game.setCellAlive(2, 2);
//    while(true){
//        system("sleep 0.5");
//        std::cout<<game.string()<<std::endl;
//        game.updateCellStates();
//        system("clear");
//    }
//}
