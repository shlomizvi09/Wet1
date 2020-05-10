//
// Created by Arik on 07/05/2020.
//

#ifndef WET1_LINKEDLIST_H
#define WET1_LINKEDLIST_H

#include <ostream>

template<class T>
class LinkedList {
public:
    class Node;

    LinkedList<T>();

    ~LinkedList<T>();

    Node *getHead();

    Node *getTail();

    Node insertInPlace(Node *node, T data);

    class Node {
        T data;
        Node *next;
        Node *prev;
    public:
        Node(T data);

        Node();

        ~Node() = default;

        T getData();

        Node *getNext() const;

        Node *getPrev() const;

        void removeNode();

        void setNext(Node *next);

        void setPrev(Node *prev);

        void changeData(T data);
    };

private:
    Node *head;
    Node *tail;
};


template<class T>
LinkedList<T>::LinkedList() {
    this->head = new Node();
    this->tail = new Node();
    this->head->setNext(tail);
    this->head->setPrev(nullptr);
    this->tail->setNext(nullptr);
    this->tail->setPrev(head);
}

template<class T>
LinkedList<T>::~LinkedList() {
    Node *iterator = this->getHead()->getNext();
    Node *tmp = iterator;
    while (iterator != this->tail) {
        iterator = iterator->getNext();
        tmp->removeNode();
        tmp = iterator;
    }
    delete this->head;
    delete this->tail;
}

template<class T>
typename LinkedList<T>::Node* LinkedList<T>::getHead() {
    return this->head;
}

template<class T>
typename LinkedList<T>::Node* LinkedList<T>::getTail() {
    return this->tail;
}

template<class T>
typename LinkedList<T>::Node
LinkedList<T>::insertInPlace(LinkedList::Node *current, T
data) {
    Node *newNode = new Node(data);
    newNode->setPrev(current);
    newNode->setNext(current->getNext());
    current->getNext()->setPrev(newNode);
    current->setNext(newNode);
    return *newNode;
}


template<class T>
LinkedList<T>::Node::Node(T data) :data(data) {
    this->next = nullptr;
    this->prev = nullptr;
}

template<class T>
LinkedList<T>::Node::Node() {
    this->data = T();
    this->next = nullptr;
    this->prev = nullptr;
}

template<class T>
T LinkedList<T>::Node::getData() {
    return this->data;
}

template<class T>
typename LinkedList<T>::Node *LinkedList<T>::Node::getNext() const {
    return this->next;
}

template<class T>
typename LinkedList<T>::Node *LinkedList<T>::Node::getPrev() const {
    return this->prev;
}

template<class T>
void LinkedList<T>::Node::removeNode() {
    this->getPrev()->setNext(this->getNext());
    this->getNext()->setPrev(this->getPrev());
    delete this;
}

template<class T>
void LinkedList<T>::Node::setNext(LinkedList::Node *next) {
    this->next = next;
}

template<class T>
void LinkedList<T>::Node::setPrev(LinkedList::Node *prev) {
    this->prev = prev;
}

template<class T>
void LinkedList<T>::Node::changeData(T data) {
    delete this->data;
    this->data = data;

}


#endif //WET1_LINKEDLIST_H
