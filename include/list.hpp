#ifndef LIST_HPP
#define LIST_HPP

#include <vector>

#define LIST_DEFAULT_SIZE 16;

template <class T> class List {
    public:
        List();
        void add(T t);
        T get(int i);
        T remove(int i);
        int size();
        ~List();
    private:
        std::vector<T> *arr;
};

#include <vector>

template <class T> List<T>::List() {
    this->arr = new std::vector<T>();
}

template <class T> void List<T>::add(T t) {
    this->arr->push_back(t);
}

template <class T> T List<T>::get(int i) {
    return this->arr->at(i);
}

template <class T> T List<T>::remove(int i) {
    T ret = this->arr->at(i);
    this->arr->erase(this->arr->begin() + i);
    return ret;
}

template <class T> int List<T>::size() {
    return this->arr->size();
}

template <class T> List<T>::~List() {
    delete this->arr;
}

#endif
