/**
 * \file qtree.hpp
 * Quadtree implementation.
 */

#ifndef QTREE_HPP
#define QTREE_HPP

#include <iostream>

#include "util.hpp"

template <class T> class QtreeNode;

/**
 * Quadtree implementation.
 */
template <class T> class Qtree {
    public:
        /**
         * Constructor for Qtree.
         */
        Qtree();
        /**
         * Copy constructor for Qtree.
         */
        Qtree(const Qtree<T> &qtree);
        /**
         * Assignment operator for Qtree.
         */
        Qtree& operator= (const Qtree<T>& qtree);
        /**
         * Add an element to (x, y) at this quadtree.
         * O(log n).
         * @param t element to add
         * @param x x-position of element
         * @param y y-position of element
         */
        void add(const T &t, int x, int y);
        /**
         * Return true if this quadtree contains an element at (x, y).
         * O(log n).
         */
        bool contains(int x, int y);
        /**
         * Get an element from (x, y) at this quadtree.
         * O(log n).
         */
        T get(int x, int y);
        /**
         * Get the height of this quadtree.
         */
        int height();
        /**
         * Render this quadtree.
         * @returns new-allocated Array containing all elements as a 2d array.
         */
        T **render();
        /**
         * Get the width of this quadtree.
         */
        int width();
        /**
         * Destructor for Qtree.
         */
        ~Qtree();
    private:
        QtreeNode<T> *child;
        int minx, miny, maxx, maxy;
};

/**
 * A single Qtree node.
 */
template <class T> class QtreeNode {
    public:
        /**
         * Constructor for QtreeNode.
         * @param size positive power of 2 size of this node
         * @param x x-position of this node
         * @param y y-position of this node
         */
        QtreeNode(int size, int x, int y);
        /**
         * Copy constructor for QtreeNode.
         */
        QtreeNode(const QtreeNode<T> &node);
        /**
         * Assignment operator for QtreeNode.
         */
        QtreeNode& operator= (const QtreeNode<T>& node);
        /** Add an element to this QtreeNode.
         * O(log n).
         * @param t element to add
         * @param x x-position of the element
         * @param y y-position of the element
         * */
        void add(const T &t, int x, int y);
        /** Add an QtreeNode to this QtreeNode.
         * O(log n).
         * @param node QtreeNode to add
         */
        void add(QtreeNode<T> *node);
        /** Return true if (x, y) is within this QtreeNode
         * O(1).
         */
        bool contains(int x, int y);
        /** Return true if this QtreeNode contains a value at (x, y).
         * O(log n).
         */
        bool containsValue(int x, int y);
        /** Get the element from this QtreeNode from (x, y).
         * O(log n).
         */
        T get(int x, int y);
        /** Render this QtreeNode to target.
         * Applies transformation pos -= (minx, miny).
         * @param target Array to render to.
         * @param minx Smallest x-value in the quadtree.
         * @param miny Smallest y-value in the quadtree.
         */
        void render(T **target, int minx, int miny);
        /**
         * Destructor for QtreeNode.
         */
        ~QtreeNode();
        /**
         * x-position of the QtreeNode.
         */
        int x;
        /**
         * y-position of the QtreeNode.
         */
        int y;
        /**
         * Size of the QtreeNode.
         */
        int size;
    private:
        void fill_content();
        int get_id(int x, int y);
        QtreeNode<T> *content[4];
        bool value_set;
        T value;
};

#include <stdexcept>

template <class T> Qtree<T>::Qtree() {
    this->child = new QtreeNode<T>(0, 0, 1);
    minx = miny = maxx = maxy = 0;
}

template <class T> Qtree<T>::Qtree(const Qtree &qtree) {
    this->child = new QtreeNode<T>(*qtree.child);
    this->minx = qtree.minx;
    this->maxx = qtree.maxx;
    this->miny = qtree.miny;
    this->maxy = qtree.maxy;
}

template <class T> Qtree<T> &Qtree<T>::operator= (const Qtree<T> &qtree) {
    this->child = new QtreeNode<T>(*qtree.child);
    this->minx = qtree.minx;
    this->maxx = qtree.maxx;
    this->miny = qtree.miny;
    this->maxy = qtree.maxy;
    return *this;
}

template <class T> void Qtree<T>::add(const T &t, int x, int y) {
    minx = MIN(minx, x);
    maxx = MAX(maxx, x);
    miny = MIN(miny, y);
    maxy = MAX(maxy, y);
    if(this->child->contains(x, y))
        this->child->add(t, x, y);
    else {
        /* add would be out of bounds so create
           a new child and double the size */
        QtreeNode<T> *oc = this->child;
        int nx, ny, ns;
        nx = oc->x;
        ny = oc->y;
        ns = oc->size;
        if(x < nx)
            nx -= ns;
        if(y < ny)
            ny -= ns;
        ns *= 2;
        this->child = new QtreeNode<T>(nx, ny, ns*2);
        this->child->add(oc);
        /* tail call recursion */
        this->add(t, x, y);
    }
}

template <class T> bool Qtree<T>::contains(int x, int y) {
    return this->child->containsValue(x, y);
}

template <class T> T Qtree<T>::get(int x, int y) {
    return this->child->get(x, y);
}

template <class T> int Qtree<T>::height() {
    return this->maxy - this->miny+1;
}

template <class T> T **Qtree<T>::render() {
    T **target = new T *[this->height()];
    for(int i = 0; i < this->height(); i++)
        target[i] = new T[this->width()]();
    this->child->render(target, this->minx, this->miny);
    return target;
}

template <class T> int Qtree<T>::width() {
    return this->maxx - this->minx+1;
}

template <class T> Qtree<T>::~Qtree() {
    delete this->child;
}

template <class T> QtreeNode<T>::QtreeNode(int x, int y, int size) {
    if(size == 0)
        throw std::invalid_argument("Tried to create a QtreeNode with size 0");

    for(int i = 0; i < 4; i++) {
        this->content[i] = NULL;
    }
    this->x = x;
    this->y = y;
    this->size = size;
    this->value_set = false;
}

template <class T> QtreeNode<T>::QtreeNode(const QtreeNode &node) {
    this->size = node.size;
    if(node.size == 1) {
        this->x = node.x;
        this->y = node.y;
        this->value_set = node.value_set;
        this->value = node.value;
    }
    if(node.content[0] != NULL)
        for(int i = 0; i < 4; i++)
            this->content[i] = new QtreeNode(*node.content[i]);
}

template <class T> QtreeNode<T> &QtreeNode<T>::operator= (const QtreeNode<T> &node) {
    this->size = node.size;
    this->x = node.x;
    this->y = node.y;
    if(node.size == 1) {
        this->value_set = node.value_set;
        if(this->value_set)
            this->value = node.value;
    }
    if(node.content[0] != NULL)
        for(int i = 0; i < 4; i++)
            this->content[i] = new QtreeNode(*node.content[i]);
    return *this;
}

template <class T> void QtreeNode<T>::fill_content() {
    int hs = this->size/2;
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
        this->value_set = true;
        return;
    }
    fill_content();
    for(int i = 0; i < 4; i++)
        if(this->content[i]->contains(x, y))
            this->content[i]->add(t, x, y);
}

template <class T> void QtreeNode<T>::add(QtreeNode *node) {
    if(!this->contains(node->x, node->y))
        throw std::out_of_range("tried to add an out of range QtreeNode");
    int id = get_id(node->x, node->y);
    fill_content();
    if(this->size == node->size*2) {
        delete this->content[id];
        this->content[id] = node;
    }
    else
        this->content[id]->add(node);
}

template <class T> bool QtreeNode<T>::contains(int x, int y) {
    return (this->x <= x && this->y <= y &&
             this->x + size > x && this->y + size > y);
}

template <class T> bool QtreeNode<T>::containsValue(int x, int y) {
    if(!this->contains(x, y))
        return false;
    if(this->size == 1)
        return this->value_set;
    int id = get_id(x, y);
    return this->content[id] != NULL && this->content[id]->containsValue(x, y);
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

//get the index to this->content where (x, y) is
template <class T> int QtreeNode<T>::get_id(int x, int y) {
    if(size == 1)
        throw std::invalid_argument("Tried to get id of content from a QtreeNode with size 1");
    if(this->x + this->size/2 > x)
        if(this->y + this->size/2 > y)
            return 0;
        else
            return 2;
    else if(this->y + this->size/2 > y)
        return 1;
    return 3;
}

template <class T> void QtreeNode<T>::render(T **target, int minx, int miny) {
    if(size == 1 && this->value_set)
        target[this->y - miny][this->x - minx] = this->value;
    else if(size > 1 && this->content[0] != NULL)
        for(int i = 0; i < 4; i++)
            this->content[i]->render(target, minx, miny);
}

template <class T> QtreeNode<T>::~QtreeNode() {
    if(this->content[0] != NULL)
        for(int i = 0; i < 4; i++)
            delete this->content[i];
}

#endif
