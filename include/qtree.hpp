#ifndef QTREE_HPP
#define QTREE_HPP

#include <iostream>

template <class T> class QtreeNode;

template <class T> class Qtree {
    public:
        Qtree();
        void add(const T &t, int x, int y);
        bool contains(int x, int y);
        T get(int x, int y);
        ~Qtree();
    private:
        QtreeNode<T> *child;
        int x, y, size;
};

template <class T> class QtreeNode {
    public:
        QtreeNode(int size, int x, int y);
        void add(const T &t, int x, int y);
        void add(QtreeNode *node, int x, int y, int size);
        bool contains(int x, int y);
        T get(int x, int y);
        ~QtreeNode();
        int size, x, y;
    private:
        void fill_content();
        QtreeNode<T> *content[4];
        QtreeNode<T> *nbor[4];
        T value;
};

#include <stdexcept>

template <class T> Qtree<T>::Qtree() {
    this->child = new QtreeNode<T>(0, 0, 1);
}

template <class T> void Qtree<T>::add(const T &t, int x, int y) {
    if(this->child->contains(x, y))
        this->child->add(t, x, y);
    else {
        QtreeNode<T> *oc = this->child;
        int nx, ny, ns;
        nx = oc->x;
        ny = oc->y;
        ns = oc->size;
        if(x < nx)
            nx -= ns;
        if(y < ny)
            ny -= ns;
        this->child = new QtreeNode<T>(nx, ny, ns*2);
        this->child->add(oc, oc->x, oc->y, oc->size);
        /* tail call recursion */
        this->add(t, x, y);
    }
}

template <class T> T Qtree<T>::get(int x, int y) {
    return this->child->get(x, y);
}

template <class T> Qtree<T>::~Qtree() {
    delete this->child;
}

template <class T> QtreeNode<T>::QtreeNode(int x, int y, int size) {
    for(int i = 0; i < 4; i++) {
        this->content[i] = NULL;
        this->nbor[i] = NULL;
    }
    this->x = x;
    this->y = y;
    this->size = size;
}

template <class T> void QtreeNode<T>::fill_content() {
    int hs = size/2;
    if(this->content[0] == NULL)
        this->content[0] = new QtreeNode<T>(this->x, this->y, hs);
    if(this->content[1] == NULL)
        this->content[1] = new QtreeNode<T>(this->x+hs, this->y, hs);
    if(this->content[2] == NULL)
        this->content[2] = new QtreeNode<T>(this->x, this->y+hs, hs);
    if(this->content[3] == NULL)
        this->content[3] = new QtreeNode<T>(this->x+hs, this->y+hs, hs);
}

template <class T> void QtreeNode<T>::add(const T &t, int x, int y) {
    if(!this->contains(x, y))
        throw std::out_of_range("tried to add an out of range value to QtreeNode");
    if(this->size == 1) {
        this->value = t;
        return;
    }
    fill_content();
    for(int i = 0; i < 4; i++)
        if(this->content[i]->contains(x, y))
            this->content[i]->add(t, x, y);
}

template <class T> void QtreeNode<T>::add(QtreeNode *node, int x, int y,
        int size) {
    if(!this->contains(x, y))
        throw std::out_of_range("tried to add an out of range QtreeNode");
    int id;
    if(this->x + this->size/2 > x)
        if(this->y + this->size/2 > y)
            id = 0;
        else
            id = 2;
    else
        if(this->y + this->size/2 > y)
            id = 1;
        else
            id = 3;
    if(this->size == size*2) {
        if(this->content[0] == NULL)
            delete this->content[id];
        this->content[id] = node;
    }
    else {
        fill_content();
        this->content[id]->add(node, x, y, size);
    }
}

template <class T> bool QtreeNode<T>::contains(int x, int y) {
    return (this->x <= x && this->y <= y &&
             this->x + size > x && this->y + size > y);
}

template <class T> T QtreeNode<T>::get(int x, int y) {
    if(!this->contains(x, y))
        throw std::out_of_range("tried to add an out of range QtreeNode");
    if(this->size == 1)
        return this->value;
    for(int i = 0; i < 4; i++)
        if(this->content[i]->contains(x, y))
            return this->content[i]->get(x, y);
    throw std::out_of_range("tried to add an out of range QtreeNode");
}

template <class T> QtreeNode<T>::~QtreeNode() {}

#endif
