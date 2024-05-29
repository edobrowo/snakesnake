#ifndef __GAME_ACTION__
#define __GAME_ACTION__

namespace game {
    enum class PlayerAction {
        moveUp = 0,
        moveDown = 1,
        moveLeft = 2,
        moveRight = 3,
        quit = 100,
        invalid = 101,
    };
}

#endif
