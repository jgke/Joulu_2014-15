/**
 * \file pair.hpp
 * Pair class.
 */

#ifndef PAIR_HPP
#define PAIR_HPP

/**
 * Pair class.
 */
template<class A, class B> class Pair {
    public:
        /**
         * Constructor for Pair.
         */
        Pair(A a, B b): a(a), b(b) {}
        /**
         * First member.
         */
        A a;
        /**
         * Second member.
         */
        B b;
};

#endif
