#include <vector>

namespace game {
    template <class T>
    class Board {
    public:
        Board(int width, int height);

        T& operator()(size_t x, size_t y);
        T& operator()(const Pos& pos);

        bool inBounds(const Pos& pos) const;
        int width() const;
        int height() const;

    private:
        std::vector<T> values;
        int boardWidth;
        int boardHeight;
    };

    struct Pos {
        size_t x;
        size_t y;

        constexpr Pos();
        constexpr Pos(size_t x, size_t y);
        Pos(const Pos& other);
        Pos operator=(const Pos& other);

        Pos operator+=(const Pos& other);
        bool operator==(const Pos& other);
    };
}
