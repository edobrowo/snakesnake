#ifndef __GAME_SNAKE_CONTROLLER__
#define __GAME_SNAKE_CONTROLLER__

#include "player_action.hpp"
#include "snake.hpp"

namespace game {
    class SnakeController {
    public:
        SnakeController();

        void handleAction(const PlayerAction action, Snake& snake) const;
    };
}

#endif
