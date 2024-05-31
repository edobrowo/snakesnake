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
        : board{Board<Cell>(BOARD_INIT_WIDTH, BOARD_INIT_HEIGHT, Cell{Empty{}})},
          head{SNAKE_INIT_HEAD},
          tail{SNAKE_INIT_TAIL},
          headDir{SNAKE_INIT_DIR},
          foodGenerator{BOARD_INIT_WIDTH, BOARD_INIT_HEIGHT},
          snakeAlive{true} {
        reset();
    }

    const Board<Cell>& Snake::boardState() const {
        return board;
    }

    void Snake::update() {
        Pos new_head{head + increments[static_cast<size_t>(headDir)]};

        if (!board.inBounds(new_head) || !std::get_if<game::Empty>(&board(new_head))) {
            snakeAlive = false;
            return;
        }

        board(head) = headDir;
        board(new_head) = headDir;
        head = new_head;

        if (head == food) {
            food = foodGenerator.spawnFood(board);
        } else {
            SnakeBody snake_body = std::get<SnakeBody>(board(tail));
            Pos new_tail{tail + increments[static_cast<Pos::Coord>(snake_body.direction)]};
            board(tail) = Cell{Empty{}};
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

        board.fill(Cell{Empty{}});

        for (Pos::Coord x = tail.x; x <= head.x; ++x) {
            board(x, head.y) = SNAKE_INIT_DIR;
        }

        snakeAlive = true;
        food = foodGenerator.spawnFood(board);
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

    FoodGenerator::FoodGenerator(Board<Cell>::Size width, Board<Cell>::Size height)
        : boardWidth{width} {
        std::random_device dev;
        rng = Engine(dev());
        dist = Distribution(0, width * height - 1);
    }

    Pos FoodGenerator::spawnFood(const Board<Cell>& board) const {
        Pos sample_pos;
        do {
            Pos::Coord val = dist(rng);
            sample_pos = Pos(val % boardWidth, val / boardWidth);
        } while (!std::get_if<game::Empty>(&board(sample_pos)));
        return sample_pos;
    }
}
