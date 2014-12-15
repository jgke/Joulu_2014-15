#include <vector>

#include "list.hpp"

template <class T> List<T>::List() {
    this->arr = new std::vector<T>();
}

template <class T> int List<T>::add(T t) {
    this->arr->push_back(t);
    return this->arr->size()-1;
}

template <class T> T List<T>::get(int i) {
    return (*this->arr)[i];
}

template <class T> T List<T>::remove(int i) {
    T ret = (*this->arr)[i];
    this->arr->erase(this->arr->begin() + i);
    return ret;
}

template <class T> int List<T>::size() {
    return this->arr->size();
}

template <class T> List<T>::~List() {
    delete this->arr;
}
