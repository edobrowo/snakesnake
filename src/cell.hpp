#ifndef __GAME_CELL__
#define __GAME_CELL__

#include <variant>

#include "direction.hpp"

namespace game {
    class Empty {};

    class SnakeBody {
    public:
        SnakeBody(const Direction direction) : m_direction{direction} {}
        Direction direction() const {
            return m_direction;
        }

    private:
        Direction m_direction;
    };

    using Cell = std::variant<SnakeBody, Empty>;
}

#endif
