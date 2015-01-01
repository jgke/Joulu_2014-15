/**
 * \file glcoord.hpp
 * Coordinate class for graphics, duplicate code from Coord efficiency reasons.
 */

#ifndef GLCOORD_H
#define GLCOORD_H

#include <algorithm>
#include <stdexcept>

#include "common.hpp"

/**
 * Class for a coordinate.
 */
template <class T> class _GLCoord {
    public:
        /**
         * Constructor for _GLCoord.
         */
        _GLCoord();
        /**
         * Constructor for _GLCoord.
         */
        _GLCoord(const T &x, const T &y, const T &z);
        /**
         * Constructor for _GLCoord.
         */
        _GLCoord(const _GLCoord<T> &c);
        /**
         * Length of this _GLCoord.
         * ABS(x) + ABS(y).
         */
        T length() const;
        /**
         * Assignment operator for _GLCoord.
         */
        _GLCoord &operator=(const _GLCoord<T> &c);
        /**
         * Sum two _GLCoords.
         */
        _GLCoord operator+=(const _GLCoord &_GLCoord);
        /**
         * Subtract two _GLCoords.
         */
        _GLCoord operator-=(const _GLCoord &_GLCoord);
        /**
         * True if _GLCoords are equal.
         */
        bool operator==(const _GLCoord &_GLCoord) const;
        /**
         * True if _GLCoords are not equal.
         */
        bool operator!=(const _GLCoord &_GLCoord) const;
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

template <class T> _GLCoord<T>::_GLCoord(): x(0), y(0), z(0) {}

template <class T> _GLCoord<T>::_GLCoord(const T &x, const T &y, const T &z): x(x), y(y), z(z) {}

template <class T> _GLCoord<T>::_GLCoord(const _GLCoord<T> &c): x(c.x), y(c.y), z(c.z) {}

template <class T> T _GLCoord<T>::length() const {
    return ABS(this->x) + ABS(this->y) + ABS(this->z);
}

template <class T> _GLCoord<T> &_GLCoord<T>::operator=(const _GLCoord<T> &c) {
    x = c.x;
    y = c.y;
    z = c.z;
    return *this;
}

/**
 * Sum two _GLCoords.
 */
template <class T> _GLCoord<T> operator+(const _GLCoord<T> &a, const _GLCoord<T> &b) {
    return _GLCoord<T>(a.x+b.x, a.y+b.y, a.z+b.z);
}

template <class T> _GLCoord<T> _GLCoord<T>::operator+=(const _GLCoord<T> &_GLCoord) {
    this->x += _GLCoord.x;
    this->y += _GLCoord.y;
    this->z += _GLCoord.z;
    return *this;
}

/**
 * Subtract two _GLCoords.
 */
template <class T> _GLCoord<T> operator-(const _GLCoord<T> &a, const _GLCoord<T> &b) {
    return _GLCoord<T>(a.x-b.x, a.y-b.y, a.z-b.z);
}

template <class T> _GLCoord<T> _GLCoord<T>::operator-=(const _GLCoord<T> &_GLCoord) {
    this->x -= _GLCoord.x;
    this->y -= _GLCoord.y;
    this->z -= _GLCoord.z;
    return *this;
}

template <class T> bool _GLCoord<T>::operator== (const _GLCoord<T> &_GLCoord) const {
    return this->x == _GLCoord.x && this->y == _GLCoord.y && this->z == _GLCoord.z;
}

template <class T> bool _GLCoord<T>::operator!=(const _GLCoord<T> &_GLCoord) const {
    return this->x != _GLCoord.x || this->y != _GLCoord.y || this->z != _GLCoord.z;
}

/**
 * Output _GLCoord to stream.
 */
template <class T> std::ostream &operator<<(std::ostream &stream,
        const _GLCoord<T> &a) {
    return stream << a.x << ", " << a.y << ", " << a.z << "]";
}

namespace std {
    /**
     * Swap two _GLCoords.
     */
    template <class T> void swap(_GLCoord<T> &a, _GLCoord<T> &b) {
        std::swap(a.x, b.x);
        std::swap(a.y, b.y);
        std::swap(a.z, b.z);
    }
}

/**
 * GLCoord used for gl coordinates.
 */
typedef _GLCoord<double> GLCoord;

#endif
