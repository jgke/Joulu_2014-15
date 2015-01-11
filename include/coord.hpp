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
        _Coord(const T &x, const T &y, const T &z);
        /**
         * Constructor for coord.
         */
        _Coord(const _Coord<T> &c);
        /**
         * Constructor for typecasted coord.
         */
        template <class V> _Coord(const _Coord<V> &c);
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
         * Assignment operator for typecasted coord.
         */
        template <class V> _Coord &operator=(const _Coord<V> &c);
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
        /**
         * The z-coordinate.
         */
        T z;
};

template <class T> _Coord<T>::_Coord(): x(0), y(0), z(0) {}

template <class T> _Coord<T>::_Coord(const T &x, const T &y): x(x), y(y), z(0) {}

template <class T> _Coord<T>::_Coord(const T &x, const T &y, const T &z):
    x(x), y(y), z(z) {}

template <class T> _Coord<T>::_Coord(const _Coord<T> &c): x(c.x), y(c.y), z(c.z) {}

template <class T>
template <class V>
_Coord<T>::_Coord(const _Coord<V> &c):
    x(static_cast<T>(c.x)),
    y(static_cast<T>(c.y)),
    z(static_cast<T>(c.z)) {}

template <class T> T _Coord<T>::length() const {
    return ABS(this->x) + ABS(this->y) + ABS(this->z);
}

template <class T> _Coord<T> &_Coord<T>::operator=(const _Coord<T> &c) {
    x = c.x;
    y = c.y;
    z = c.z;
    return *this;
}

/**
 * Assignment operator for typecasting Coord.
 */
template <class T> template <class V> _Coord<T> &_Coord<T>::operator=(const _Coord<V> &c) {
    x = static_cast<T>(c.x);
    y = static_cast<T>(c.y);
    z = static_cast<T>(c.z);
    return *this;
}

/**
 * Sum two coords.
 */
template <class T> _Coord<T> operator+(const _Coord<T> &a, const _Coord<T> &b) {
    return _Coord<T>(a.x+b.x, a.y+b.y, a.z+b.z);
}

template <class T> _Coord<T> _Coord<T>::operator+=(const _Coord<T> &coord) {
    this->x += coord.x;
    this->y += coord.y;
    this->z += coord.z;
    return *this;
}

/**
 * Subtract two coords.
 */
template <class T> _Coord<T> operator-(const _Coord<T> &a, const _Coord<T> &b) {
    return _Coord<T>(a.x-b.x, a.y-b.y, a.z-b.z);
}

template <class T> _Coord<T> _Coord<T>::operator-=(const _Coord<T> &coord) {
    this->x -= coord.x;
    this->y -= coord.y;
    this->z -= coord.z;
    return *this;
}

template <class T> bool _Coord<T>::operator== (const _Coord<T> &coord) const {
    return this->x == coord.x && this->y == coord.y && this->z == coord.z;
}

template <class T> bool _Coord<T>::operator!=(const _Coord<T> &coord) const {
    return this->x != coord.x || this->y != coord.y || this->z != coord.z;
}

/**
 * Output coord to stream.
 */
template <class T> std::ostream &operator<<(std::ostream &stream,
        const _Coord<T> &a) {
    return stream << a.x << ", " << a.y << ", " << a.z << "]";
}

namespace std {
    /**
     * Swap two coords.
     */
    template <class T> void swap(_Coord<T> &a, _Coord<T> &b) {
        std::swap(a.x, b.x);
        std::swap(a.y, b.y);
        std::swap(a.z, b.z);
    }
}

/**
 * Coord used for coordinates.
 */
typedef _Coord<int> Coord;
/**
 * Coord used for OpenGL coordinates.
 */
typedef _Coord<double> GLCoord;

#endif
