#ifndef __GAME_POS__
#define __GAME_POS__

#include <cstddef>

namespace game {
    class Pos {
    public:
        using Coord = ::size_t;

        Coord x;
        Coord y;

        constexpr Pos() : x{0}, y{0} {}
        constexpr Pos(Coord x, Coord y) : x{x}, y{y} {}
        Pos(const Pos& other);
        Pos operator=(const Pos& other);

        Pos operator+=(const Pos& other);
        bool operator==(const Pos& other) const;
    };
}

#endif