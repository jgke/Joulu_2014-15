/**
 * \file qtree.hpp
 * Quadtree implementation.
 */

#ifndef QTREE_HPP
#define QTREE_HPP

#include <iostream>
#include <cstdlib> //rand

#include "common.hpp"
#include "coord.hpp"

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
        Qtree &operator= (const Qtree<T> &qtree);
        /**
         * Add an element to coord at this quadtree.
         * O(log n).
         * @param t element to add
         * @param coord position of element
         */
        void add(const T &t, const Coord &coord);
        /**
         * Return true if this quadtree contains an element at coord.
         * O(log n).
         */
        bool contains(const Coord &coord) const;
        /**
         * Get the  top left corner of this quadtree.
         * O(1).
         */
        Coord corner() const;
        /**
         * Get an element from coord at this quadtree.
         * O(log n).
         */
        T get(const Coord &coord) const;
        /**
         * Get an element from coord at this quadtree,
         * return value if coord is not in this quadtree.
         * O(log n).
         */
        T get(const Coord &coord, T value) const;
        /**
         * Get the height of this quadtree.
         */
        int height() const;
        /**
         * Call cb for each value with value and position.
         */
        void map(void *data, void (*cb)(const T &value, const Coord &pos, void *data));
        /**
         * Return a random coord that this qtree contains.
         */
        Coord random() const;
        /**
         * Render this quadtree.
         * O(log n).
         * @returns new-allocated Array containing all elements as a 2d array.
         */
        T **render() const;
        /**
         * Get amount of members in this quadtree.
         */
        int size() const;
        /**
         * Get the width of this quadtree.
         */
        int width() const;
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
         * @param coord position of this node
         */
        QtreeNode(const Coord &coord, int size);
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
         * @param coord position of the element
         * @returns true if a new value was created
         * */
        bool add(const T &t, const Coord &coord);
        /** Add an QtreeNode to this QtreeNode.
         * O(log n).
         * @param node QtreeNode to add
         */
        void add(QtreeNode<T> *node);
        /** Return true if coord is within this QtreeNode
         * O(1).
         */
        bool contains(const Coord &coord) const;
        /** Return true if this QtreeNode contains a value at coord.
         * O(log n).
         */
        bool containsValue(const Coord &coord) const;
        /** Get the element from this QtreeNode from coord.
         * O(log n).
         */
        T get(const Coord &coord) const;
        /**
         * Return a coordinate by an index.
         * O(log n).
         */
        const Coord &get(int index) const;
        /**
         * Call cb for each value with value and position.
         */
        void map(void *data, void (*cb)(const T &value, const Coord &pos, void *data));
        /** Render this QtreeNode to target.
         * Applies transformation pos -= (minx, miny).
         * @param target Array to render to.
         * @param minx Smallest x-value in the quadtree.
         * @param miny Smallest y-value in the quadtree.
         */
        void render(T **target, int minx, int miny) const;
        /**
         * Destructor for QtreeNode.
         */
        ~QtreeNode();
        /**
         * Position of the QtreeNode.
         */
        Coord coord;
        /**
         * Amount of members in this quadtree.
         */
        int memberCount;
        /**
         * Size of the QtreeNode.
         */
        int size;
    private:
        void fill_content();
        int get_id(const Coord &coord) const;
        QtreeNode<T> *content[4];
        bool value_set;
        T value;
};

#include <stdexcept>

template <class T> Qtree<T>::Qtree() {
    this->child = new QtreeNode<T>(Coord(0, 0), 1);
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
    delete this->child;
    this->child = new QtreeNode<T>(*qtree.child);
    this->minx = qtree.minx;
    this->maxx = qtree.maxx;
    this->miny = qtree.miny;
    this->maxy = qtree.maxy;
    return *this;
}

template <class T> void Qtree<T>::add(const T &t, const Coord &coord) {
    minx = MIN(minx, coord.x);
    maxx = MAX(maxx, coord.x);
    miny = MIN(miny, coord.y);
    maxy = MAX(maxy, coord.y);
    if(this->child->contains(coord))
        this->child->add(t, coord);
    else {
        /* add would be out of bounds so create
           a new child and double the size */
        QtreeNode<T> *oc = this->child;
        int ns;
        ns = oc->size;
        Coord newpos = oc->coord;
        if(coord.x < newpos.x)
            newpos.x -= ns;
        if(coord.y < newpos.y)
            newpos.y -= ns;
        ns *= 2;
        this->child = new QtreeNode<T>(newpos, ns*2);
        this->child->add(oc);
        /* tail call recursion */
        this->add(t, coord);
    }
}

template <class T> bool Qtree<T>::contains(const Coord &coord) const {
    return this->child->containsValue(coord);
}

template <class T> Coord Qtree<T>::corner() const {
    return Coord(this->minx, this->miny);
}

template <class T> T Qtree<T>::get(const Coord &coord) const {
    return this->child->get(coord);
}

template <class T> T Qtree<T>::get(const Coord &coord, T value) const {
    return this->child->containsValue(coord) ? this->child->get(coord) : value;
}

template <class T> int Qtree<T>::height() const {
    return this->maxy - this->miny+1;
}

template <class T> void Qtree<T>::map(void *data, void (*cb)(const T &value,
            const Coord &pos, void *data)) {
    this->child->map(data, cb);
}

template <class T> Coord Qtree<T>::random() const {
    if(this->child->memberCount == 0)
        return Coord(0, 0);
    return this->child->get(rand()%this->child->memberCount);
}

template <class T> T **Qtree<T>::render() const {
    T **target = new T *[this->height()];
    for(int i = 0; i < this->height(); i++)
        target[i] = new T[this->width()]();
    this->child->render(target, this->minx, this->miny);
    return target;
}

template <class T> int Qtree<T>::size() const {
    return this->child->memberCount;
}

template <class T> int Qtree<T>::width() const {
    return this->maxx - this->minx+1;
}

template <class T> Qtree<T>::~Qtree() {
    delete this->child;
}

template <class T> QtreeNode<T>::QtreeNode(const Coord &coord, int size):
        coord(coord), size(size) {
#ifdef DEBUG
    if(size == 0)
        throw std::invalid_argument("Tried to create a QtreeNode with size 0");
#endif

    for(int i = 0; i < 4; i++) {
        this->content[i] = NULL;
    }
    this->coord = coord;
    this->size = size;
    this->value_set = false;
    this->memberCount = 0;
}

template <class T> QtreeNode<T>::QtreeNode(const QtreeNode &node):
        coord(node.coord), size(node.size) {
    this->memberCount = node.memberCount;
    for(int i = 0; i < 4; i++) {
        this->content[i] = NULL;
    }
    if(node.size == 1) {
        this->value_set = node.value_set;
        this->value = node.value;
    }
    if(node.content[0] != NULL)
        for(int i = 0; i < 4; i++)
            this->content[i] = new QtreeNode(*node.content[i]);
}

template <class T> QtreeNode<T> &QtreeNode<T>::operator= (
        const QtreeNode<T> &node) {
    this->size = node.size;
    this->coord = node.coord;
    this->memberCount = node.memberCount;
    for(int i = 0; i < 4; i++) {
        this->content[i] = NULL;
    }
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
        this->content[0] = new QtreeNode<T>(this->coord, hs);
    if(this->content[1] == NULL)
        this->content[1] = new QtreeNode<T>(this->coord + Coord(hs, 0), hs);
    if(this->content[2] == NULL)
        this->content[2] = new QtreeNode<T>(this->coord + Coord(0, hs), hs);
    if(this->content[3] == NULL)
        this->content[3] = new QtreeNode<T>(this->coord + Coord(hs, hs), hs);
}

template <class T> bool QtreeNode<T>::add(const T &t, const Coord &coord) {
#ifdef DEBUG
    if(!this->contains(coord))
        throw std::out_of_range("tried to add an out of range value to QtreeNode");
#endif
    if(this->size == 1) {
        bool ret = !this->value_set;
        this->value = t;
        this->value_set = true;
        this->memberCount = 1;
        return ret;
    }
    fill_content();
    for(int i = 0; i < 4; i++)
        if(this->content[i]->contains(coord)) {
            bool ret = this->content[i]->add(t, coord);
            if(ret)
                this->memberCount++;
            return ret;
        }
    //never reached
    throw std::out_of_range("tried to add an out of range value to QtreeNode");
}

template <class T> void QtreeNode<T>::add(QtreeNode *node) {
#ifdef DEBUG
    if(!this->contains(node->coord))
        throw std::out_of_range("tried to add an out of range QtreeNode");
#endif
    int id = get_id(node->coord);
    fill_content();
    if(this->size == node->size*2) {
        this->memberCount -= this->content[id]->memberCount;
        delete this->content[id];
        this->content[id] = node;
        this->memberCount += this->content[id]->memberCount;
    }
    else
        this->content[id]->add(node);
}

template <class T> bool QtreeNode<T>::contains(const Coord &coord) const {
    return (this->coord.x <= coord.x && this->coord.y <= coord.y &&
             this->coord.x + this->size > coord.x &&
             this->coord.y + this->size > coord.y);
}

template <class T> bool QtreeNode<T>::containsValue(const Coord &coord) const {
    if(!this->contains(coord))
        return false;
    if(this->size == 1)
        return this->value_set;
    int id = get_id(coord);
    return this->content[id] != NULL && this->content[id]->containsValue(coord);
}

template <class T> T QtreeNode<T>::get(const Coord &coord) const {
#ifdef DEBUG
    if(!this->contains(coord))
        throw std::out_of_range("tried to add an out of range QtreeNode");
#endif
    if(this->size == 1)
        return this->value;
    for(int i = 0; i < 4; i++)
        if(this->content[i]->contains(coord))
            return this->content[i]->get(coord);
    throw std::out_of_range("tried to add an out of range QtreeNode");
}

template <class T> const Coord &QtreeNode<T>::get(int index) const {
    if(this->size == 1)
        return this->coord;
    for(int i = 0; i < 4; i++) {
        if(index < this->content[i]->memberCount)
            return this->content[i]->get(index);
        index -= this->content[i]->memberCount;
    }
    throw std::out_of_range("tried to get an out of range index");
}

//get the index to this->content where (x, y) is
template <class T> int QtreeNode<T>::get_id(const Coord &coord) const {
#ifdef DEBUG
    if(size == 1)
        throw std::invalid_argument("Tried to get id of content from a QtreeNode with size 1");
#endif
    if(this->coord.x + this->size/2 > coord.x)
        if(this->coord.y + this->size/2 > coord.y)
            return 0;
        else
            return 2;
    else if(this->coord.y + this->size/2 > coord.y)
        return 1;
    return 3;
}

template <class T> void QtreeNode<T>::map(void *data,
        void (*cb)(const T &value, const Coord &pos, void *data)) {
    if(size == 1 && this->value_set)
        cb(this->value, this->coord, data);
    else if(size > 1 && this->content[0] != NULL)
        for(int i = 0; i < 4; i++)
            this->content[i]->map(data, cb);
}

template <class T> void QtreeNode<T>::render(T **target, int minx,
        int miny) const {
    if(size == 1 && this->value_set)
        target[this->coord.y - miny][this->coord.x - minx] = this->value;
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
