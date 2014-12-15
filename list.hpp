#ifndef LIST_HPP
#define LIST_HPP

#include <vector>

#define LIST_DEFAULT_SIZE 16;

template <class T> class List {
    public:
        List();
        int add(T t);
        T get(int i);
        T remove(int i);
        int size();
        ~List();
    private:
        std::vector<T> *arr;
};

#include "list.cpp"

#endif
