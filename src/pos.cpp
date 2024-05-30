#include "pos.hpp"

namespace game {
    Pos::Pos(const Pos& other) : x{other.x}, y{other.y} {}

    Pos& Pos::operator=(const Pos& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
    }

    Pos& Pos::operator+=(const Pos& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    bool Pos::operator==(const Pos& other) const {
        return x == other.x && y == other.y;
    }
}
