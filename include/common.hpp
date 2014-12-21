/**
 * \file common.hpp
 * Utility macros.
 */

#ifndef COMMON_H
#define COMMON_H

#include <stdexcept>

#if (defined(unix) || defined(__unix__) || defined(__unix) || defined(__APPLE__) && defined(__MACH__))
/**
 * Defined if running in a sensible OS.
 */
#define SENSIBLE_OS
#endif

/**
 * Macro for minimum of a and b.
 */
#define MIN(a, b) ((a) < (b) ? (a) : (b))
/**
 * Macro for maximum of a and b.
 */
#define MAX(a, b) ((a) > (b) ? (a) : (b))
/**
 * Macro for absolute value of a.
 */
#define ABS(a) ((a) >= 0 ? (a) : (-(a)))

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
        _Coord(T x, T y);
        /**
         * Sum two _Coords, (a,b) + (c, d) = (a+c, b+d).
         */
        _Coord &operator+=(const _Coord &coord);
        /**
         * Subtract two _Coords, (a,b) - (c, d) = (a-c, b-d).
         */
        _Coord &operator-=(const _Coord &coord);
        /**
         * Multiply two _Coords, (a,b) * (c, d) = (a*c, b*d).
         */
        _Coord &operator*=(const _Coord &coord);
        /**
         * Divide two _Coords, (a,b) / (c, d) = (a/c, b/d).
         */
        _Coord &operator/=(const _Coord &coord);
        /**
         * True if _Coords are equal, (a,b) == (c, d) = a==c && b==d.
         */
        bool operator==(const _Coord &coord);
        /**
         * Return ith coordinant, x = coord[0], y = coord[1].
         */
        T operator[](const int &i);
        /**
         * The x-coordinate.
         */
        T x;
        /**
         * The y-coordinate.
         */
        T y;
};

template <class T> _Coord<T>::_Coord() {
    x = y = 0;
}

template <class T> _Coord<T>::_Coord(T x, T y) {
    this->x = x;
    this->y = y;
}

template <class T> _Coord<T> operator+(const _Coord<T> &a, const _Coord<T> &b) {
    _Coord<T> ret(a.x+b.x, a.y+b.y);
    return ret;
}

template <class T> _Coord<T> &_Coord<T>::operator+=(const _Coord<T> &coord) {
    this->x += coord.x;
    this->y += coord.y;
    return *this;
}

template <class T> _Coord<T> operator-(const _Coord<T> &a, const _Coord<T> &b) {
    _Coord<T> ret(a.x-b.x, a.y-b.y);
    return ret;
}

template <class T> _Coord<T> &_Coord<T>::operator-=(const _Coord<T> &coord) {
    this->x -= coord.x;
    this->y -= coord.y;
    return *this;
}

template <class T> _Coord<T> operator*(const _Coord<T> &a, const _Coord<T> &b) {
    _Coord<T> ret(a.x*b.x, a.y*b.y);
    return ret;
}

template <class T> _Coord<T> &_Coord<T>::operator*=(const _Coord<T> &coord) {
    this->x *= coord.x;
    this->y *= coord.y;
    return *this;
}

template <class T> _Coord<T> operator/(const _Coord<T> &a, const _Coord<T> &b) {
    _Coord<T> ret(a.x/b.x, a.y/b.y);
    return ret;
}

template <class T> _Coord<T> &_Coord<T>::operator/=(const _Coord<T> &coord) {
    this->x /= coord.x;
    this->y /= coord.y;
    return *this;
}

template <class T> bool _Coord<T>::operator==(const _Coord<T> &coord) {
    return this->x == coord.x && this->y == coord.y;
}

template <class T> T _Coord<T>::operator[](const int &i) {
    switch(i) {
    case 0:
        return this->x;
    case 1:
        return this->y;
    default:
        throw std::out_of_range("tried to get out of range index from _Coord");
    }
}

/**
 * Type of single coordinate.
 */
#define COORDTYPE int

//bypassing linker errors and get inlined operators
typedef _Coord<COORDTYPE> Coord;

#endif
