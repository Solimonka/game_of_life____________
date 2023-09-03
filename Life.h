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

    const std::vector<bool> &getCellStates() const;

    size_t getWidth() const;

    size_t getHeight() const;

private:
    size_t width_;
    size_t height_;
    std::vector<bool> cell_states_;
};
