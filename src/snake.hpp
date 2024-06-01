#ifndef __GAME_SNAKE__
#define __GAME_SNAKE__

#include <random>
#include <vector>

#include "board.hpp"
#include "cell.hpp"
#include "pos.hpp"

namespace game {
    class FoodGenerator {
    public:
        using Engine = std::mt19937;
        using Distribution = std::uniform_int_distribution<Pos::Coord>;

        FoodGenerator(Board<Cell>::Size width, Board<Cell>::Size height);
        Pos spawnFood(const Board<Cell>& board) const;

    private:
        Board<Cell>::Size boardWidth;
        mutable Engine rng;
        mutable Distribution dist;
    };

    struct SnakeInitSettings {
        Board<Cell>::Size boardWidth;
        Board<Cell>::Size boardHeight;
        Pos head;
        Pos tail;
        Direction direction;
        float tilesPerSecond;
    };

    class Snake {
    public:
        Snake();

        const Board<Cell>& board() const;
        void update();
        bool isAlive() const;
        void setDirection(Direction dir);
        Pos food() const;
        float tilesPerSecond() const;
        void restart();

    private:
        void reset();
        static bool validDirectionChange(Direction old_dir, Direction new_dir);

        const SnakeInitSettings m_settings{20, 20, Pos(3, 1), Pos(1, 1), Direction::Right, 10.0};
        const std::vector<Pos> m_increments{Pos(0, -1), Pos(0, 1), Pos(-1, 0), Pos(1, 0)};

        Board<Cell> m_board;
        Pos m_head;
        Pos m_tail;
        Direction m_headDirection;
        bool m_alive;
        float m_tilesPerSecond;

        FoodGenerator m_foodGenerator;
        Pos m_food;
    };
}

#endif
