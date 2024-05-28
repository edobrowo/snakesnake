#include "board.hpp"

#include <vector>

using namespace game;

template <class T>
Board<T>::Board(int width, int height)
    : _width{width}, _height{height} {
    this->values = std::vector<T>(width * height);
}

template <class T>
T& Board<T>::operator()(size_t x, size_t y) {
    int index = y * this->_width + x;
    return board.values[index];
}

template <class T>
T& Board<T>::operator()(const Pos& pos) {
    int index = pos->y * this->_width + pos->x;
    return board.values[index];
}

template <class T>
bool Board<T>::inBounds(const Pos& pos) const {
    return pos->x < this->_width && pos->y < this->_height;
}

template <class T>
int Board<T>::width() const {
    return this->_width;
}

template <class T>
int Board<T>::height() const {
    return this->_height;
}

constexpr Pos::Pos() : x{0}, y{0} {}

constexpr Pos::Pos(size_t x, size_t y) : x{x}, y{y} {}

Pos::Pos(const Pos& other) : x{other.x}, y{other.y} {}

Pos Pos::operator=(const Pos& other) {
    return Pos(other);
}

Pos Pos::operator+=(const Pos& other) {
    x += other.x;
    y += other.y;
}

bool Pos::operator==(const Pos& other) {
    return x == other.x && y == other.y;
}