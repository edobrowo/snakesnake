#include "snake.hpp"

#include <cassert>
#include <iostream>

namespace game {

    constexpr int BOARD_INIT_WIDTH = 20;
    constexpr int BOARD_INIT_HEIGHT = 20;

    constexpr Pos SNAKE_INIT_HEAD = Pos(3, 1);
    constexpr Pos SNAKE_INIT_TAIL = Pos(1, 1);
    constexpr Direction SNAKE_INIT_DIR = Direction::Right;

    Snake::Snake()
        : board{Board<Direction>(BOARD_INIT_WIDTH, BOARD_INIT_HEIGHT, Direction::None)},
          head{SNAKE_INIT_HEAD},
          tail{SNAKE_INIT_TAIL},
          headDir{SNAKE_INIT_DIR},
          foodGenerator{BOARD_INIT_WIDTH, BOARD_INIT_HEIGHT},
          snakeAlive{true} {
        reset();
    }

    const Board<Direction>& Snake::boardState() const {
        return board;
    }

    void Snake::update() {
        Pos new_head = head + increments[static_cast<size_t>(headDir)];

        if (!board.inBounds(new_head) || board(new_head) != Direction::None) {
            snakeAlive = false;
            return;
        }

        board(head) = headDir;
        board(new_head) = headDir;
        head = new_head;

        if (head == food) {
            food = foodGenerator.spawnFood(board);
        } else {
            Pos new_tail = tail + increments[static_cast<Pos::Coord>(board(tail))];
            board(tail) = Direction::None;
            tail = new_tail;
        }
    }

    bool Snake::isAlive() const {
        return snakeAlive;
    }

    void Snake::setDirection(const Direction dir) {
        if (validDirectionChange(headDir, dir)) {
            headDir = dir;
        }
    }

    const Pos Snake::foodPos() const {
        return food;
    }

    void Snake::reset() {
        assert(head.x > tail.x && head.x < board.width() && head.y == tail.y && tail.y > 0);

        board.fill(Direction::None);

        for (Pos::Coord x = tail.x; x <= head.x; ++x) {
            board(x, head.y) = SNAKE_INIT_DIR;
        }
        snakeAlive = true;
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
        default:
            return false;
        }
        return false;
    }

    FoodGenerator::FoodGenerator(Board<Direction>::Size width, Board<Direction>::Size height)
        : boardWidth{width} {
        std::random_device dev;
        rng = Engine(dev());
        dist = Distribution(0, width * height - 1);
    }

    Pos FoodGenerator::spawnFood(const Board<Direction>& board) const {
        Pos sample_pos;
        do {
            Pos::Coord val = dist(rng);
            sample_pos = Pos(val % boardWidth, val / boardWidth);
        } while (board(sample_pos) != Direction::None);
        return sample_pos;
    }
}
