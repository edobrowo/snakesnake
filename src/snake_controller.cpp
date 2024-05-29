#include "snake_controller.hpp"

namespace game {
    SnakeController::SnakeController() {}

    void SnakeController::handleAction(const PlayerAction action, Snake& snake) const {
        switch (action) {
        case PlayerAction::moveUp:
            snake.setDirection(Direction::Up);
            break;
        case PlayerAction::moveDown:
            snake.setDirection(Direction::Down);
            break;
        case PlayerAction::moveLeft:
            snake.setDirection(Direction::Left);
            break;
        case PlayerAction::moveRight:
            snake.setDirection(Direction::Right);
            break;
        case PlayerAction::quit:
        case PlayerAction::invalid:
            return;
        }
    }
}
