#include "Life.h"

Life::Life(size_t width, size_t height) {
    width_ = width;
    height_ = height;
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