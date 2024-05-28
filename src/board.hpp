#ifndef __GAME_BOARD__
#define __GAME_BOARD__

#include <vector>

namespace game {
    class Pos {
    public:
        size_t x;
        size_t y;

        constexpr Pos() : x{0}, y{0} {}
        constexpr Pos(size_t x, size_t y) : x{x}, y{y} {}
        Pos(const Pos& other);
        Pos operator=(const Pos& other);

        Pos operator+=(const Pos& other);
        bool operator==(const Pos& other) const;
    };

    template <class T>
    class Board {
    public:
        Board(size_t width, size_t height, T init);

        T& operator()(size_t x, size_t y);
        T& operator()(const Pos& pos);
        const T& operator()(const Pos& pos) const;

        bool inBounds(const Pos& pos) const;
        size_t width() const;
        size_t height() const;

    private:
        std::vector<T> values;
        size_t boardWidth;
        size_t boardHeight;
    };

    template <class T>
    Board<T>::Board(size_t width, size_t height, T init)
        : values{std::vector<T>(width * height, init)},
          boardWidth{width},
          boardHeight{height} {}

    template <class T>
    T& Board<T>::operator()(size_t x, size_t y) {
        int index = y * boardWidth + x;
        return values[index];
    }

    template <class T>
    T& Board<T>::operator()(const Pos& pos) {
        int index = pos.y * boardWidth + pos.x;
        return values[index];
    }

    template <class T>
    const T& Board<T>::operator()(const Pos& pos) const {
        int index = pos.y * boardWidth + pos.x;
        return values[index];
    }

    template <class T>
    bool Board<T>::inBounds(const Pos& pos) const {
        return pos.x < boardWidth && pos.y < boardHeight;
    }

    template <class T>
    size_t Board<T>::width() const {
        return boardWidth;
    }

    template <class T>
    size_t Board<T>::height() const {
        return boardHeight;
    }
}

#endif
