#ifndef __GAME_BOARD__
#define __GAME_BOARD__

#include <algorithm>
#include <vector>

#include "pos.hpp"

namespace game {
    template <class T>
    class Board {
    public:
        using Size = Pos::Coord;

        Board(Pos::Coord width, Pos::Coord height, T init);

        T& operator()(const Pos::Coord& x, const Pos::Coord& y);
        const T& operator()(const Pos::Coord& x, const Pos::Coord& y) const;
        T& operator()(const Pos& pos);
        const T& operator()(const Pos& pos) const;

        bool inBounds(const Pos& pos) const;
        Size width() const;
        Size height() const;
        void fill(T val);

    private:
        std::vector<T> values;
        Size boardWidth;
        Size boardHeight;
    };

    template <class T>
    Board<T>::Board(Size width, Size height, T init)
        : values{std::vector<T>(width * height, init)},
          boardWidth{width},
          boardHeight{height} {}

    template <class T>
    T& Board<T>::operator()(const Pos::Coord& x, const Pos::Coord& y) {
        int index = y * boardWidth + x;
        return values[index];
    }

    template <class T>
    const T& Board<T>::operator()(const Pos::Coord& x, const Pos::Coord& y) const {
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
        return 0 <= pos.x && pos.x < boardWidth && 0 <= pos.y && pos.y < boardHeight;
    }

    template <class T>
    Board<T>::Size Board<T>::width() const {
        return boardWidth;
    }

    template <class T>
    Board<T>::Size Board<T>::height() const {
        return boardHeight;
    }

    template <class T>
    void Board<T>::fill(T val) {
        std::fill(values.begin(), values.end(), val);
    }
}

#endif
