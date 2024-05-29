#ifndef __GAME_SNAKE__
#define __GAME_SNAKE__

#include <random>
#include <vector>

#include "board.hpp"
#include "direction.hpp"
#include "pos.hpp"

namespace game {
    class FoodGenerator {
    public:
        using Engine = std::mt19937;
        using Distribution = std::uniform_int_distribution<Pos::Coord>;

        FoodGenerator(Board<Direction>::Size width, Board<Direction>::Size height);
        Pos spawnFood(const Board<Direction>& board) const;

    private:
        Board<Direction>::Size boardWidth;
        mutable Engine rng;
        mutable Distribution dist;
    };

    class Snake {
    public:
        Snake();

        const Board<Direction>& boardState() const;
        void update();
        void setDirection(const Direction dir);

        // params
        // float tilesPerSecond;  // TODO
        // int sizeIncrease;      // TODO

    private:
        static bool validDirectionChange(Direction old_dir, Direction new_dir);

        Board<Direction> board;
        Pos head;
        Pos tail;

        FoodGenerator foodGenerator;
        Pos food;

        const std::vector<Pos> increments = {Pos(0, 1), Pos(0, -1), Pos(-1, 0), Pos(1, 0)};
    };
}

#endif
