/**
 * \file list.hpp
 * Dynamic list.
 */

#ifndef LIST_HPP
#define LIST_HPP

#include <vector>

/**
 * Dynamic list.
 */
template <class T> class List {
    public:
        /**
         * Constructor for list.
         */
        List();
        /**
         * Add a member to this list.
         * O(1).
         * @param t Member to add.
         */
        void add(T t);
        /**
         * Get a member from this list.
         * O(1).
         * @param i Index of member.
         */
        T get(int i) const;
        /**
         * Remove a member from this list.
         * O(n).
         * @param i Index of member.
         */
        T remove(int i);
        /**
         * Get size of this list.
         */
        int size() const;
        /**
         * Destructor for list.
         */
        ~List();
    private:
        std::vector<T> arr;
};

template <class T> List<T>::List(): arr(std::vector<T>()) {}

template <class T> void List<T>::add(T t) {
    this->arr.push_back(t);
}

template <class T> T List<T>::get(int i) const {
    return this->arr.at(i);
}

template <class T> T List<T>::remove(int i) {
    T ret = this->arr.at(i);
    this->arr.erase(this->arr.begin() + i);
    return ret;
}

template <class T> int List<T>::size() const {
    return this->arr.size();
}

template <class T> List<T>::~List() {}

#endif
