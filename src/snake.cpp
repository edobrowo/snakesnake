#include "snake.hpp"

#include <cassert>
#include <iostream>

namespace game {

    constexpr int BOARD_INIT_WIDTH = 10;
    constexpr int BOARD_INIT_HEIGHT = 10;

    constexpr Pos SNAKE_INIT_HEAD = Pos(1, 3);
    constexpr Pos SNAKE_INIT_TAIL = Pos(1, 1);
    constexpr Direction SNAKE_INIT_DIR = Direction::Right;

    Snake::Snake()
        : board{Board<Direction>(BOARD_INIT_WIDTH, BOARD_INIT_HEIGHT, Direction::None)},
          head{SNAKE_INIT_HEAD},
          tail{SNAKE_INIT_TAIL},
          foodGenerator{BOARD_INIT_WIDTH, BOARD_INIT_HEIGHT} {
        assert(head.x == tail.x && head.x < board.width() && head.y > tail.y && tail.y > 0);
        for (Pos::Coord y = tail.y; y <= head.y; ++y) {
            board(head.x, y) = SNAKE_INIT_DIR;
        }
    }

    const Board<Direction>& Snake::boardState() const {
        return board;
    }

    void Snake::update() {
        head += increments[static_cast<Pos::Coord>(board(head))];

        if (!board.inBounds(head)) {
            // TODO : return false or make a game over callback
            return;
        }

        if (head == food) {
            food = foodGenerator.spawnFood(board);
        } else {
            tail += increments[static_cast<Pos::Coord>(board(tail))];
        }
    }

    void Snake::setDirection(const Direction dir) {
        std::cout << static_cast<int>(dir) << std::endl;
        if (dir != board(head) &&
            validDirectionChange(board(head), dir)) {
            board(head) = dir;
        }
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
