#ifndef QTREE_HPP
#define QTREE_HPP

#include <iostream>

template <class T> class QtreeNode;

template <class T> class Qtree {
    public:
        Qtree();
        Qtree(const Qtree<T> &qtree);
        Qtree& operator= (const Qtree<T>& qtree);
        void add(const T &t, int x, int y);
        bool containsValue(int x, int y);
        T get(int x, int y);
        QtreeNode<T> *getChild();
        ~Qtree();
    private:
        QtreeNode<T> *child;
};

template <class T> class QtreeNode {
    public:
        QtreeNode(int size, int x, int y);
        QtreeNode(const QtreeNode<T> &node);
        QtreeNode& operator= (const QtreeNode<T>& node);
        void add(const T &t, int x, int y);
        void add(QtreeNode<T> *node, int x, int y, int size);
        bool contains(int x, int y);
        bool containsValue(int x, int y);
        T get(int x, int y);
        int getSize();
        ~QtreeNode();
        int x, y;
    private:
        int size;
        void fill_content();
        int get_id(int x, int y);
        QtreeNode<T> *content[4];
        bool value_set;
        T value;
};

#include <stdexcept>

template <class T> Qtree<T>::Qtree() {
    this->child = new QtreeNode<T>(0, 0, 1);
}

template <class T> Qtree<T>::Qtree(const Qtree &qtree) {
    QtreeNode<T> *child = qtree.getChild();
    this->child = new QtreeNode<T>(*child);
}

template <class T> Qtree<T> &Qtree<T>::operator= (const Qtree<T> &qtree) {
    this->child = new QtreeNode<T>(*qtree.child);
    return *this;
}

template <class T> void Qtree<T>::add(const T &t, int x, int y) {
    if(this->child->contains(x, y))
        this->child->add(t, x, y);
    else {
        QtreeNode<T> *oc = this->child;
        int nx, ny, ns;
        nx = oc->x;
        ny = oc->y;
        ns = oc->getSize();
        if(x < nx)
            nx -= ns;
        if(y < ny)
            ny -= ns;
        ns *= 2;
        this->child = new QtreeNode<T>(nx, ny, ns*2);
        this->child->add(oc, oc->x, oc->y, oc->getSize());
        /* tail call recursion */
        this->add(t, x, y);
    }
}

template <class T> bool Qtree<T>::containsValue(int x, int y) {
    return this->child->containsValue(x, y);
}

template <class T> T Qtree<T>::get(int x, int y) {
    return this->child->get(x, y);
}

template <class T> QtreeNode<T> *Qtree<T>::getChild() {
    return this->child;
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
    if(node.size == 1) {
        this->x = node.x;
        this->y = node.y;
        this->value_set = node.value_set;
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

template <class T> void QtreeNode<T>::add(QtreeNode *node, int x, int y,
        int size) {
    if(!this->contains(x, y))
        throw std::out_of_range("tried to add an out of range QtreeNode");
    int id = get_id(x, y);
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

template <class T> int QtreeNode<T>::getSize() {
    return this->size;
}

template <class T> QtreeNode<T>::~QtreeNode() {}

#endif
