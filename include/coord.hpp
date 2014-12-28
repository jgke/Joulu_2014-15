/**
 * \file coord.hpp
 * Coordinate class.
 */

#ifndef COORD_H
#define COORD_H

#include <algorithm>
#include <stdexcept>

#include "common.hpp"

/**
 * Class for a coordinate.
 */
template <class T> class _Coord {
    public:
        /**
         * Constructor for coord.
         */
        _Coord();
        /**
         * Constructor for coord.
         */
        _Coord(const T &x, const T &y);
        /**
         * Constructor for coord.
         */
        _Coord(const _Coord<T> &c);
        /**
         * Length of this coord.
         * ABS(x) + ABS(y).
         */
        T length() const;
        /**
         * Assignment operator for coord.
         */
        _Coord &operator=(const _Coord<T> &c);
        /**
         * Sum two _Coords, (a,b) + (c, d) = (a+c, b+d).
         */
        _Coord operator+=(const _Coord &coord);
        /**
         * Subtract two _Coords, (a,b) - (c, d) = (a-c, b-d).
         */
        _Coord operator-=(const _Coord &coord);
        /**
         * True if _Coords are equal, (a,b) == (c, d) = a==c && b==d.
         */
        bool operator==(const _Coord &coord) const;
        /**
         * True if _Coords are not equal, (a,b) != (c, d) = a!=c || b!=d.
         */
        bool operator!=(const _Coord &coord) const;
        /**
         * The x-coordinate.
         */
        T x;
        /**
         * The y-coordinate.
         */
        T y;
};

template <class T> _Coord<T>::_Coord(): x(0), y(0) {}

template <class T> _Coord<T>::_Coord(const T &x, const T &y): x(x), y(y) {}

template <class T> _Coord<T>::_Coord(const _Coord<T> &c): x(c.x), y(c.y) {}

template <class T> T _Coord<T>::length() const {
    return ABS(this->x) + ABS(this->y);
}

template <class T> _Coord<T> &_Coord<T>::operator=(const _Coord<T> &c) {
    x = c.x;
    y = c.y;
    return *this;
}

/**
 * Sum two coords.
 */
template <class T> _Coord<T> operator+(const _Coord<T> &a, const _Coord<T> &b) {
    return _Coord<T>(a.x+b.x, a.y+b.y);
}

template <class T> _Coord<T> _Coord<T>::operator+=(const _Coord<T> &coord) {
    this->x += coord.x;
    this->y += coord.y;
    return *this;
}

/**
 * Subtract two coords.
 */
template <class T> _Coord<T> operator-(const _Coord<T> &a, const _Coord<T> &b) {
    return _Coord<T>(a.x-b.x, a.y-b.y);
}

template <class T> _Coord<T> _Coord<T>::operator-=(const _Coord<T> &coord) {
    this->x -= coord.x;
    this->y -= coord.y;
    return *this;
}

template <class T> bool _Coord<T>::operator== (const _Coord<T> &coord) const {
    return this->x == coord.x && this->y == coord.y;
}

template <class T> bool _Coord<T>::operator!=(const _Coord<T> &coord) const {
    return this->x != coord.x || this->y != coord.y;
}

/**
 * Output coord to stream.
 */
template <class T> std::ostream &operator<<(std::ostream &stream,
        const _Coord<T> &a) {
    return stream << a.x << ", " << a.y << "]";
}

namespace std {
    /**
     * Swap two coords.
     */
    template <class T> void swap(_Coord<T> &a, _Coord<T> &b) {
        std::swap(a.x, b.x);
        std::swap(a.y, b.y);
    }
}

/**
 * Type of single coordinate.
 */
#define COORDTYPE int

/**
 * Coord used for coordinates.
 */
typedef _Coord<COORDTYPE> Coord;

#endif
