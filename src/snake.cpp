#include "snake.hpp"

#include <cassert>
#include <iostream>

namespace game {

    Snake::Snake()
        : m_board{Board<Cell>(m_settings.boardWidth, m_settings.boardHeight, Cell{Empty{}})},
          m_head{m_settings.head},
          m_tail{m_settings.tail},
          m_headDirection{m_settings.direction},
          m_alive{true},
          m_tilesPerSecond{m_settings.tilesPerSecond},
          m_foodGenerator{m_settings.boardWidth, m_settings.boardHeight} {
        reset();
    }

    const Board<Cell>& Snake::board() const {
        return m_board;
    }

    void Snake::update() {
        Pos new_head{m_head + m_increments[static_cast<size_t>(m_headDirection)]};

        if (!m_board.inBounds(new_head) || !std::get_if<game::Empty>(&m_board(new_head))) {
            m_alive = false;
            return;
        }

        m_board(m_head) = m_headDirection;
        m_board(new_head) = m_headDirection;
        m_head = new_head;

        if (m_head == m_food) {
            m_food = m_foodGenerator.spawnFood(m_board);
        } else {
            SnakeBody snake_body = std::get<SnakeBody>(m_board(m_tail));
            Pos new_tail{m_tail + m_increments[static_cast<Pos::Coord>(snake_body.direction())]};
            m_board(m_tail) = Cell{Empty{}};
            m_tail = new_tail;
        }
    }

    bool Snake::isAlive() const {
        return m_alive;
    }

    void Snake::setDirection(Direction dir) {
        if (validDirectionChange(m_headDirection, dir)) {
            m_headDirection = dir;
        }
    }

    Pos Snake::food() const {
        return m_food;
    }

    float Snake::tilesPerSecond() const {
        return m_tilesPerSecond;
    }

    void Snake::restart() {
        m_head = m_settings.head;
        m_tail = m_settings.tail;
        m_headDirection = m_settings.direction;

        reset();
    }

    void Snake::reset() {
        m_board.fill(Cell{Empty{}});

        for (Pos::Coord x = m_tail.x(); x <= m_head.x(); ++x) {
            m_board(x, m_head.y()) = m_settings.direction;
        }

        m_alive = true;
        m_food = m_foodGenerator.spawnFood(m_board);
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

std::ostream& operator<<(std::ostream& os, const game::Snake& snake) {
    int h = snake.board().height();
    int w = snake.board().width();
    for (game::Pos::Coord y = 0; y < h; ++y) {
        for (game::Pos::Coord x = 0; x < w; ++x) {
            if (game::Pos(x, y) == snake.food()) {
                os << 'F';
                continue;
            }

            if (std::get_if<game::Empty>(&snake.board()(x, y))) {
                os << '.';
                continue;
            }

            const game::SnakeBody& snake_body = std::get<game::SnakeBody>(snake.board()(x, y));
            const game::Direction direction = snake_body.direction();
            switch (direction) {
            case game::Direction::Up:
                os << 'U';
                break;
            case game::Direction::Down:
                os << 'D';
                break;
            case game::Direction::Left:
                os << 'L';
                break;
            case game::Direction::Right:
                os << 'R';
                break;
            }
        }
        os << '\n';
    }
    return os;
}
