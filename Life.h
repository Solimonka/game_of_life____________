#pragma once

#include <iostream>
#include <vector>

class LifeException : public std::runtime_error {
public:
    explicit LifeException(const std::string &message) : std::runtime_error(message) {}
};

class Life {
public:

    explicit Life(size_t width, size_t height);

    size_t getWidth() const;

    size_t getHeight() const;

    const std::vector<bool> &getCellStates() const;

    void setCellDeda(size_t x, size_t y);

    void setCellAlive(size_t x, size_t y);

    bool getCellState(size_t x, size_t y);

private:
    void setCellState(size_t x, size_t y, bool state);

    size_t width_;
    size_t height_;
    std::vector<bool> cell_states_;
};
