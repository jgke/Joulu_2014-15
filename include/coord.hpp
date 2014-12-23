#ifndef COORD_H
#define COORD_H

#include <stdexcept>

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
         * Assignment operator for coord.
         */
        _Coord operator=(const _Coord<T> &c);
        /**
         * Sum two _Coords, (a,b) + (c, d) = (a+c, b+d).
         */
        _Coord operator+=(const _Coord &coord);
        /**
         * Subtract two _Coords, (a,b) - (c, d) = (a-c, b-d).
         */
        _Coord operator-=(const _Coord &coord);
        /**
         * Multiply two _Coords, (a,b) * (c, d) = (a*c, b*d).
         */
        _Coord operator*=(const _Coord &coord);
        /**
         * Divide two _Coords, (a,b) / (c, d) = (a/c, b/d).
         */
        _Coord operator/=(const _Coord &coord);
        /**
         * True if _Coords are equal, (a,b) == (c, d) = a==c && b==d.
         */
        bool operator==(const _Coord &coord) const;
        /**
         * True if _Coords are not equal, (a,b) != (c, d) = a!=c || b!=d.
         */
        bool operator!=(const _Coord &coord) const;
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

template <class T> _Coord<T>::_Coord(const T &x, const T &y): x(x), y(y) {}

template <class T> _Coord<T>::_Coord(const _Coord<T> &c) {
    x = c.x;
    y = c.y;
}

template <class T> _Coord<T> _Coord<T>::operator=(const _Coord<T> &c) {
    x = c.x;
    y = c.y;
    return *this;
}

template <class T> _Coord<T> operator+(const _Coord<T> &a, const _Coord<T> &b) {
    return _Coord<T>(a.x+b.x, a.y+b.y);
}

template <class T> _Coord<T> _Coord<T>::operator+=(const _Coord<T> &coord) {
    this->x += coord.x;
    this->y += coord.y;
    return *this;
}

template <class T> _Coord<T> operator-(const _Coord<T> &a, const _Coord<T> &b) {
    return _Coord<T>(a.x-b.x, a.y-b.y);
}

template <class T> _Coord<T> _Coord<T>::operator-=(const _Coord<T> &coord) {
    this->x -= coord.x;
    this->y -= coord.y;
    return *this;
}

template <class T> _Coord<T> operator*(const _Coord<T> &a, const _Coord<T> &b) {
    return _Coord<T>(a.x*b.x, a.y*b.y);
}

template <class T> _Coord<T> _Coord<T>::operator*=(const _Coord<T> &coord) {
    this->x *= coord.x;
    this->y *= coord.y;
    return *this;
}

template <class T> _Coord<T> operator/(const _Coord<T> &a, const _Coord<T> &b) {
    return _Coord<T>(a.x/b.x, a.y/b.y);
}

template <class T> _Coord<T> _Coord<T>::operator/=(const _Coord<T> &coord) {
    this->x /= coord.x;
    this->y /= coord.y;
    return *this;
}

template <class T> bool _Coord<T>::operator== (const _Coord<T> &coord) const {
    return this->x == coord.x && this->y == coord.y;
}

template <class T> bool _Coord<T>::operator!=(const _Coord<T> &coord) const {
    return this->x != coord.x || this->y != coord.y;
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

template <class T> std::ostream &operator<<(std::ostream &stream, const _Coord<T> &a) {
    return stream << a.x << ", " << a.y << "]";
}

/**
 * Type of single coordinate.
 */
#define COORDTYPE int

//bypassing linker errors and letting compiler inline operators
typedef _Coord<COORDTYPE> Coord;

#endif
