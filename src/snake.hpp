#include <vector>

#include "board.hpp"

namespace game {

    enum class Direction {
        Up = 0,
        Down = 1,
        Left = 2,
        Right = 3
    };

    class Snake {
    public:
        Snake();

        void update();
        void setDirection(const Direction dir);

    private:
        void spawnFood();
        static bool validDirectionChange(Direction old_dir, Direction new_dir);

        Board<Direction> board;
        Pos food;
        Pos tail;
        Pos head;

        float speed;
        int sizeIncrease;
    };
}
