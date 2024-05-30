#ifndef __GAME_POS__
#define __GAME_POS__

namespace game {
    class Pos {
    public:
        using Coord = int;

        Coord x;
        Coord y;

        constexpr Pos() : x{0}, y{0} {}
        constexpr Pos(Coord x, Coord y) : x{x}, y{y} {}
        Pos(const Pos& other);
        Pos& operator=(const Pos& other);

        Pos& operator+=(const Pos& other);
        bool operator==(const Pos& other) const;
    };
}

#endif
