#ifndef __GAME_CELL__
#define __GAME_CELL__

#include <variant>

#include "direction.hpp"

namespace game {
    class Empty {
    public:
        Empty() {}
    };

    class SnakeBody {
    public:
        SnakeBody(Direction direction) : direction{direction} {}
        Direction direction;
    };

    using Cell = std::variant<SnakeBody, Empty>;
}

#endif
