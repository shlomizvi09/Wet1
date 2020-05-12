//
// Created by Arik on 07/05/2020.
//

#ifndef WET1_LINKEDLIST_H
#define WET1_LINKEDLIST_H

#include <ostream>

template<class T>
class LinkedList {
public:
    class ListNode;

    LinkedList<T>();

    ~LinkedList<T>();

    ListNode *getHead();

    ListNode *getTail();

    ListNode *insertInPlace(ListNode *current, T data);

    ListNode *insertFirst(T data);


    void deleteNode(ListNode *node);

    void printList();

    class ListNode {
        T data;
        ListNode *next;
        ListNode *prev;
    public:
        ListNode(T data);

        ListNode();

        ~ListNode() = default;

        T getData();

        ListNode *getNext() const;

        ListNode *getPrev() const;

        void removeNode();

        void setNext(ListNode *next);

        void setPrev(ListNode *prev);

        void changeData(T data);
    };

private:
    ListNode *head;
    ListNode *tail;
};


template<class T>
LinkedList<T>::LinkedList() {
    this->head = new ListNode();
    this->tail = new ListNode();
    this->head->setNext(tail);
    this->head->setPrev(nullptr);
    this->tail->setNext(nullptr);
    this->tail->setPrev(head);
}

template<class T>
LinkedList<T>::~LinkedList() {
    ListNode *iterator = this->getHead()->getNext();
    ListNode *tmp = iterator;
    while (iterator != this->tail) {
        iterator = iterator->getNext();
        tmp->removeNode();
        tmp = iterator;
    }
    delete this->head;
    delete this->tail;
}

template<class T>
typename LinkedList<T>::ListNode *LinkedList<T>::getHead() {
    return this->head;
}

template<class T>
typename LinkedList<T>::ListNode *LinkedList<T>::getTail() {
    return this->tail;
}

template<class T>
typename LinkedList<T>::ListNode *
LinkedList<T>::insertInPlace(LinkedList::ListNode
                             *current, T
                             data) {
    ListNode *newNode = new ListNode(data);
    newNode->setPrev(current);
    newNode->setNext(current->getNext());
    current->getNext()->setPrev(newNode);
    current->setNext(newNode);
    return newNode;
}

template<class T>
void LinkedList<T>::printList() {
    ListNode *iterator = this->head->getNext();
    while (iterator->getNext()) {
        std::cout << iterator->getData() << std::endl;
        iterator = iterator->getNext();
    }

}

template<class T>
void LinkedList<T>::deleteNode(LinkedList::ListNode *node) {
    node->removeNode();

}

template<class T>
typename LinkedList<T>::ListNode *
LinkedList<T>::insertFirst(T
                           data) {
    ListNode *newNode = new ListNode(data);
    newNode->setPrev(this->head);
    newNode->setNext(this->head->getNext());
    newNode->getNext()->setPrev(newNode);
    newNode->getPrev()->setNext(newNode);
    return newNode;
}


template<class T>
LinkedList<T>::ListNode::ListNode(T data) :data(data) {
    this->next = nullptr;
    this->prev = nullptr;
}

template<class T>
LinkedList<T>::ListNode::ListNode() {
    this->data = T();
    this->next = nullptr;
    this->prev = nullptr;
}

template<class T>
T LinkedList<T>::ListNode::getData() {
    return this->data;
}

template<class T>
typename LinkedList<T>::ListNode *LinkedList<T>::ListNode::getNext() const {
    return this->next;
}

template<class T>
typename LinkedList<T>::ListNode *LinkedList<T>::ListNode::getPrev() const {
    return this->prev;
}

template<class T>
void LinkedList<T>::ListNode::removeNode() {
    this->getPrev()->setNext(this->getNext());
    this->getNext()->setPrev(this->getPrev());
    delete this;
}

template<class T>
void LinkedList<T>::ListNode::setNext(LinkedList::ListNode *next) {
    this->next = next;
}

template<class T>
void LinkedList<T>::ListNode::setPrev(LinkedList::ListNode *prev) {
    this->prev = prev;
}

template<class T>
void LinkedList<T>::ListNode::changeData(T data) {
    delete this->data;
    this->data = data;

}


#endif //WET1_LINKEDLIST_H
