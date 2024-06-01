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

        Board(Pos::Coord width, Pos::Coord height, const T& init);

        T& operator()(Pos::Coord x, Pos::Coord y);
        const T& operator()(Pos::Coord x, Pos::Coord y) const;
        T& operator()(const Pos& pos);
        const T& operator()(const Pos& pos) const;

        bool inBounds(const Pos& pos) const;
        Size width() const;
        Size height() const;
        void fill(const T& val);

    private:
        std::vector<T> m_values;
        Size m_width;
        Size m_height;
    };

    template <class T>
    Board<T>::Board(Size width, Size height, const T& init)
        : m_values{std::vector<T>(width * height, init)},
          m_width{width},
          m_height{height} {}

    template <class T>
    T& Board<T>::operator()(Pos::Coord x, Pos::Coord y) {
        int index = y * m_width + x;
        return m_values[index];
    }

    template <class T>
    const T& Board<T>::operator()(Pos::Coord x, Pos::Coord y) const {
        int index = y * m_width + x;
        return m_values[index];
    }

    template <class T>
    T& Board<T>::operator()(const Pos& pos) {
        int index = pos.y() * m_width + pos.x();
        return m_values[index];
    }

    template <class T>
    const T& Board<T>::operator()(const Pos& pos) const {
        int index = pos.y() * m_width + pos.x();
        return m_values[index];
    }

    template <class T>
    bool Board<T>::inBounds(const Pos& pos) const {
        return 0 <= pos.x() && pos.x() < m_width && 0 <= pos.y() && pos.y() < m_height;
    }

    template <class T>
    Board<T>::Size Board<T>::width() const {
        return m_width;
    }

    template <class T>
    Board<T>::Size Board<T>::height() const {
        return m_height;
    }

    template <class T>
    void Board<T>::fill(const T& val) {
        std::fill(m_values.begin(), m_values.end(), val);
    }
}

#endif
