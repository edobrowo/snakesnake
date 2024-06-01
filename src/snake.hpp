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
    };

    class Snake {
    public:
        Snake();

        const Board<Cell>& board() const;
        void update();
        bool isAlive() const;
        void setDirection(Direction dir);
        const Pos food() const;

    private:
        void reset();
        static bool validDirectionChange(Direction old_dir, Direction new_dir);

        SnakeInitSettings m_settings;
        Board<Cell> m_board;
        Pos m_head;
        Pos m_tail;
        Direction m_headDirection;

        FoodGenerator m_foodGenerator;
        Pos m_food;

        bool m_alive;

        const std::vector<Pos> m_increments = {Pos(0, -1), Pos(0, 1), Pos(-1, 0), Pos(1, 0)};
    };
}

#endif
