#include "pos.hpp"

namespace game {
    Pos::Pos() : m_x{0}, m_y{0} {}

    Pos::Pos(Pos::Coord x, Pos::Coord y) : m_x{x}, m_y{y} {}

    Pos::Pos(const Pos& other) : m_x{other.m_x}, m_y{other.m_y} {}

    Pos& Pos::operator=(const Pos& other) {
        if (this != &other) {
            m_x = other.m_x;
            m_y = other.m_y;
        }
        return *this;
    }

    Pos& Pos::operator+=(const Pos& other) {
        m_x += other.m_x;
        m_y += other.m_y;
        return *this;
    }

    Pos Pos::operator+(const Pos& other) {
        Pos new_pos{*this};
        new_pos += other;
        return new_pos;
    }

    bool Pos::operator==(const Pos& other) const {
        return m_x == other.m_x && m_y == other.m_y;
    }

    Pos::Coord Pos::x() const {
        return m_x;
    }

    Pos::Coord Pos::y() const {
        return m_y;
    }
}
