#ifndef __GAME_POS__
#define __GAME_POS__

namespace game {
    class Pos {
    public:
        using Coord = int;

        Pos();
        Pos(Coord x, Coord y);
        Pos(const Pos& other);
        Pos& operator=(const Pos& other);

        Pos& operator+=(const Pos& other);
        Pos operator+(const Pos& other);
        bool operator==(const Pos& other) const;

        Coord x() const;
        Coord y() const;

    private:
        Coord m_x;
        Coord m_y;
    };
}

#endif
