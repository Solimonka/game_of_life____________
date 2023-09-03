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
    if (x >= width_ || y >= height_) {
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
    if (x >= width_ || y >= height_) {
        throw LifeException("kto-to lozhanulsya: x = " +
                            std::to_string(x) + " y = " + std::to_string(y));
    }
    return cell_states_[y * width_ + x];
}
