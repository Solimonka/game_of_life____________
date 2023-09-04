#include <random>
#include "Life.h"

Life::Life(size_t width, size_t height) : width_(width), height_(height) {
    if (width_ < 3 || height_ < 3) {
        throw LifeException("kto-to lozhanulsya");
    }
    cell_states_.resize(width * height);
}

size_t Life::getWidth() const {
    return width_;
}

size_t Life::getHeight() const {
    return height_;
}

const std::vector<bool> &Life::getCellStates() const {
    return cell_states_;
}

void Life::setCellState(size_t x, size_t y, bool state) {
    if (!isValidCell(x, y)) {
        throw LifeException("kto-to lozhanulsya: x = " +
                            std::to_string(x) + " y = " + std::to_string(y));
    }
    cell_states_[y * width_ + x] = state;
}

void Life::setCellDeda(size_t x, size_t y) {
    setCellState(x, y, false);
}

void Life::setCellAlive(size_t x, size_t y) {
    setCellState(x, y, true);
}

bool Life::getCellState(size_t x, size_t y) {
    if (!isValidCell(x, y)) {
        throw LifeException("kto-to lozhanulsya: x = " +
                            std::to_string(x) + " y = " + std::to_string(y));
    }
    rightCoordinates(x, y);
    return cell_states_[y * width_ + x];
}

void Life::rightCoordinates(size_t &x, size_t &y) {
    if (x == -1) {
        x = x + width_;
    }
    if (y == -1) {
        y = y + height_;
    }
    if (x == width_) {
        x = 0;
    }
    if (y == height_) {
        y = 0;
    }
}

size_t Life::getAliveNeighboursCount(size_t x, size_t y) {
    if (!isValidCell(x, y)) {
        throw LifeException("kto-to lozhanulsya: x = " +
                            std::to_string(x) + " y = " + std::to_string(y));
    } else {
        size_t count = 0;
        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                if (i == 0 && j == 0) {
                    continue;
                }
                size_t xx = x + i;
                size_t yy = y + j;
                rightCoordinates(xx, yy);
                if (getCellState(xx, yy)) {
                    count++;
                }
            }
        }
        return count;
    }
}

bool Life::isValidCell(size_t x, size_t y) const {
    return x >= 0 && y >= 0 && x < width_ && y < height_;
}

//Любая живая клетка с двумя или тремя живыми соседями выживает.
//Любая мертвая ячейка с тремя живыми соседями становится живой ячейкой.
//Все остальные живые клетки умирают в следующем поколении. Точно так же все остальные мертвые клетки остаются мертвыми.

void Life::updateCellStates() {
    Life other_life(width_, height_);
    std::vector<bool> new_cell_states = cell_states_;
    for (int x = 0; x < width_; ++x) {
        for (int y = 0; y < height_; ++y) {
            if (getAliveNeighboursCount(x, y) == 3 || getCellState(x, y) && getAliveNeighboursCount(x, y) == 2) {
                    other_life.setCellAlive(x, y);
                } else {
                    other_life.setCellDeda(x, y);
                }
//            if (!getCellState(x, y)) {
//                if (getAliveNeighboursCount(x, y) == 3) {
//                    other_life.setCellAlive(x, y);
//                } else {
//                    continue;
//                }
//            } else {
//                if (getAliveNeighboursCount(x, y) == 2 ||
//                    getAliveNeighboursCount(x, y) == 3) {////////////////////////////////optimise
//                    other_life.setCellAlive(x, y);
//                } else {
//                    other_life.setCellDeda(x, y);
//                }
//            }
        }
    }
    std::swap(*this, other_life);
}

//std::ostream &operator<<(std::ostream &os, Life &life) {
//    for (size_t y = 0; y < life.getHeight(); ++y) {
//        for (size_t x = 0; x < life.getWidth(); ++x) {
//            if (x == life.getWidth() - 1) {
//                os << (life.getCellState(x, y) ? '*' : '.');
//            }
//            os << (life.getCellState(x, y) ? '*' : '.');
//        }
//        os << std::endl;
//    }
//    return os;
//}

std::string Life::string() {
    std::string result;
    for (auto y = 0; y < getHeight(); ++y) {
        for (auto x = 0; x < getWidth(); ++x) {
            if (x == getWidth() - 1) {
                result += getCellState(x, y) ? "X\n" : ".\n";
            } else {
                result += getCellState(x, y) ? "X " : ". ";
            }
        }
    }
    return result;
}

void Life::fillRandomStates() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);
    std::vector<bool> random_states;
    for (int i = 0; i < width_ * height_; ++i) {
        cell_states_[i] = dis(gen);
    }
}
