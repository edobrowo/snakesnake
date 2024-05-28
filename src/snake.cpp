#include "snake.hpp"

#include <random>

using namespace game;

constexpr size_t BOARD_INIT_WIDTH = 10;
constexpr size_t BOARD_INIT_HEIGHT = 10;

constexpr Pos SNAKE_INIT_HEAD = Pos(1, 1);
constexpr Pos SNAKE_INIT_TAIL = Pos(1, 3);

constexpr Direction SNAKE_INIT_DIR = Direction::Right;

std::vector<Pos> increments = {Pos(0, 1), Pos(0, -1), Pos(-1, 0), Pos(1, 0)};

Snake::Snake()
    : board{Board<Direction>(BOARD_INIT_WIDTH, BOARD_INIT_HEIGHT)},
      head{SNAKE_INIT_HEAD},
      tail{SNAKE_INIT_TAIL} {
    // TODO : make a FoodGenerator class to wrap this
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 6);
}

void Snake::update() {
    head += increments[static_cast<size_t>(board(head))];

    if (!board.inBounds(head)) {
        // TODO : return false or make a game over callback
        return;
    }

    if (head == food) {
        spawnFood();
    } else {
        tail += increments[static_cast<size_t>(board(tail))];
    }
}

void Snake::setDirection(const Direction dir) {
    if (dir != board(head) &&
        validDirectionChange(board(head), dir)) {
        board(head) = dir;
    }
}

void Snake::spawnFood() {
    // TODO : use the FoodGenerator
}

bool Snake::validDirectionChange(Direction old_dir, Direction new_dir) {
    switch (old_dir) {
    case Direction::Up:
        return new_dir != Direction::Down;
    case Direction::Down:
        return new_dir != Direction::Up;
    case Direction::Left:
        return new_dir != Direction::Right;
    case Direction::Right:
        return new_dir != Direction::Left;
    }
    return false;
}
