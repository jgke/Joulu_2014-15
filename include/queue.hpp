#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <stdlib.h> //NULL

#include "common.hpp"

template <class T> class QueueNode;

template <class T> class Queue {
    public:
        Queue();
        Queue(const Queue<T> &queue);
        Queue &operator= (const Queue<T> &queue);
        void add(const T &value);
        bool hasNext();
        const T &peek();
        const T &pop();
        ~Queue();
    private:
       QueueNode<T> *root; 
       QueueNode<T> *tail; 
};

template <class T> class QueueNode {
    public:
        QueueNode(QueueNode<T> *prev, const T &value);
        QueueNode<T> *prev;
        QueueNode<T> *next;
        T value;
};

template <class T> Queue<T>::Queue() {
    this->root = NULL;
    this->tail = NULL;
}

template <class T> Queue<T>::Queue(const Queue<T> &queue) {
    this->root = NULL;
    this->tail = NULL;
    QueueNode<T> *cur = queue.root;
    while(cur != NULL) {
        this->add(cur->value);
        cur = cur->next;
    }
}

template <class T> Queue<T> &Queue<T>::operator=(const Queue<T> &queue) {
    this->root = NULL;
    this->tail = NULL;
    QueueNode<T> *cur = queue.root;
    while(cur != NULL) {
        this->add(cur->value);
        cur = cur->next;
    }
    return *this;
}

template <class T> void Queue<T>::add(const T &value) {
    QueueNode<T> *newtail = new QueueNode<T>(this->tail, value);
    if(tail != NULL)
        tail->next = newtail;
    tail = newtail;
    if(root == NULL)
        root = tail;
}

template <class T> bool Queue<T>::hasNext() {
    return root != NULL;
}

template <class T> const T &Queue<T>::peek() {
    return root->value;
}

template <class T> const T &Queue<T>::pop() {
    QueueNode<T> *retnode = root;
    root = root->next;
    if(root == NULL)
        tail = NULL;
    const T &retvalue = retnode->value;
    delete retnode;
    return retvalue;
    
}

template <class T> Queue<T>::~Queue() {
    QueueNode<T> *cur = root;
    while(cur != NULL) {
        QueueNode<T> *next = cur->next;
        delete cur;
        cur = next;
    }
}

template <class T> QueueNode<T>::QueueNode(QueueNode *prev, const T &val): value(val) {
    this->prev = prev;
    this->next = NULL;
}

#endif
