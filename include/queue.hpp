/**
 * \file queue.hpp
 * Queue.
 */

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <stdlib.h> //NULL

#include "common.hpp"

template <class T> class QueueNode;

/**
 * Queue.
 */
template <class T> class Queue {
    public:
        /**
         * Constructor for Queue.
         */
        Queue();
        /**
         * Copy constructor for Queue.
         */
        Queue(const Queue<T> &queue);
        /**
         * Assignment operator for Queue.
         */
        Queue &operator= (const Queue<T> &queue);
        /**
         * Add a value to this queue.
         */
        void add(const T &value);
        /**
         * Returns true if there is a next member.
         */
        bool hasNext() const;
        /**
         * Returns the next member.
         */
        const T &peek() const;
        /**
         * Returns the next member and removes it from the queue.
         */
        T pop();
        /**
         * Returns the amount of members in this queue.
         */
        int size();
        /**
         * Destructor for queue.
         */
        ~Queue();
    private:
       QueueNode<T> *root; 
       QueueNode<T> *tail; 
       int membercount;
};

/**
 * Single node in a queue.
 */
template <class T> class QueueNode {
    public:
        /**
         * Constructor for QueueNode.
         */
        QueueNode(QueueNode<T> *prev, const T &value);
        /**
         * Previous node.
         */
        QueueNode<T> *prev;
        /**
         * Next node.
         */
        QueueNode<T> *next;
        /**
         * Value of this node.
         */
        T value;
};

template <class T> Queue<T>::Queue() {
    this->membercount = 0;
    this->root = NULL;
    this->tail = NULL;
}

template <class T> Queue<T>::Queue(const Queue<T> &queue) {
    this->membercount = 0;
    this->root = NULL;
    this->tail = NULL;
    QueueNode<T> *cur = queue.root;
    while(cur != NULL) {
        this->add(cur->value);
        cur = cur->next;
    }
}

template <class T> Queue<T> &Queue<T>::operator=(const Queue<T> &queue) {
    while(this->hasNext())
        this->pop();
    this->membercount = 0;
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
    this->membercount++;
    QueueNode<T> *newtail = new QueueNode<T>(this->tail, value);
    if(tail != NULL)
        tail->next = newtail;
    tail = newtail;
    if(root == NULL)
        root = tail;
}

template <class T> bool Queue<T>::hasNext() const {
    return root != NULL;
}

template <class T> const T &Queue<T>::peek() const {
    return root->value;
}

template <class T> T Queue<T>::pop() {
    this->membercount--;
    QueueNode<T> *retnode = root;
    root = root->next;
    if(root == NULL)
        tail = NULL;
    T retvalue = retnode->value;
    delete retnode;
    return retvalue;
    
}

template <class T> int Queue<T>::size() {
    return this->membercount;
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
